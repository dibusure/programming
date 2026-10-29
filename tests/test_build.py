"""Regression tests for the gallery; they never execute the displayed sources."""
import importlib.util
from html.parser import HTMLParser
from pathlib import Path
import shutil
import tempfile
import tomllib
import unittest
from urllib.parse import unquote, urlsplit

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("gallery_build", ROOT / "site" / "build.py")
builder = importlib.util.module_from_spec(spec)
spec.loader.exec_module(builder)


class Links(HTMLParser):
    def __init__(self):
        super().__init__()
        self.links = []
        self.scripts = []

    def handle_starttag(self, tag, attrs):
        values = dict(attrs)
        self.links.extend(values[key] for key in ("href", "src") if key in values)
        if tag == "script":
            self.scripts.append(values.get("src"))


class GalleryTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        (self.root / "code").mkdir()
        shutil.copytree(ROOT / "site", self.root / "site")
        shutil.copy(ROOT / "site.toml", self.root / "site.toml")
        self.config = tomllib.loads((self.root / "site.toml").read_text())

    def tearDown(self):
        self.temp.cleanup()

    def put(self, name, text):
        path = self.root / "code" / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text if isinstance(text, bytes) else text.encode("utf-8"))
        return path

    def test_mainstream_languages(self):
        samples = {
            "x.hs": "main :: IO ()\nmain = putStrLn \"hi\"\n",
            "x.lhs": "> main = putStrLn \"hi\"\n",
            "x.py": "print('hi')", "x.cpp": "#include <iostream>\nint main() {}",
            "x.c": "int main(void) {return 0;}", "x.rs": "fn main() {}",
            "x.go": "package main\nfunc main() {}", "X.java": "class X {}",
            "x.js": "const x = 1;", "x.ts": "const x: number = 1;",
            "x.tsx": "const x = <div>Hello</div>;", "x.jsx": "const x = <div />;",
            "x.kt": "fun main() {}", "x.swift": "print(1)", "X.cs": "class X {}",
            "x.rb": "puts 1", "x.php": "<?php echo 1;", "x.lua": "print(1)",
            "x.sh": "#!/bin/sh\necho hi", "x.sql": "SELECT 1;", "x.r": "x <- 1",
            "x.scala": "object X {}", "x.ex": "IO.puts(1)", "x.clj": "(println 1)",
            "x.ml": "let x = 1", "x.dart": "void main() {}", "x.pl": "print 1;",
            "x.html": "<p>hi</p>", "x.css": "p {color: red}", "x.json": '{"x": 1}',
            "x.yaml": "x: 1", "x.toml": 'x = 1', "x.md": "# Hi",
        }
        for name, text in samples.items():
            with self.subTest(name=name):
                lexer = builder.lexer_for(name, text, self.config["lexers"])
                self.assertNotEqual(lexer.name, "Text only")
                self.assertIn('class="code-line"', builder.code_html(text, lexer))
        self.assertEqual(builder.lexer_for("x.hs", samples["x.hs"], self.config["lexers"]).name, "Haskell")
        self.assertEqual(builder.lexer_for("x.lhs", samples["x.lhs"], self.config["lexers"]).name, "Literate Haskell")

    def test_unknown_and_shebang(self):
        self.assertEqual(builder.lexer_for("note.unknownextension", "hello").name, "Text only")
        self.assertEqual(builder.lexer_for("runner", "#!/usr/bin/env python3\nprint(1)").name, "Python")

    def test_overrides(self):
        self.assertEqual(builder.lexer_for("source.custom", "print(1)", {"*.custom": "python"}).name, "Python")

    def test_hidden_binary_large_and_symlinks(self):
        self.put("keep.py", "print(1)")
        self.put(".env", "PASSWORD=secret")
        self.put("key.pem", "private")
        self.put("nested/node_modules/x.js", "not published")
        self.put("bad.bin", b"\x00\x01")
        self.put("bad.encoding", b"\xff\xfe")
        self.put("huge.py", "#" * (self.config["max_file_bytes"] + 1))
        secret = self.root / "private.py"
        secret.write_text("secret")
        (self.root / "code" / "link.py").symlink_to(secret)
        (self.root / "code" / "linked-folder").symlink_to(self.root, target_is_directory=True)
        files = builder.collect(self.root / "code", self.config)
        self.assertEqual([f["path"] for f in files], ["keep.py"])

    def test_raw_preserves_original_bytes(self):
        original = b"\xef\xbb\xbf# hello\r\nprint(1)\r\n"
        self.put("file.py", original)
        _, output = builder.build(self.root)
        files = builder.collect(self.root / "code", self.config)
        self.assertEqual((output / files[0]["raw_url"]).read_bytes(), original)
        self.assertEqual(files[0]["lines"], 2)

    def test_content_is_escaped_not_executed(self):
        self.put("payload.html", '<script>window.HACKED = true</script>\n</textarea><img src=x onerror=alert(1)>')
        marker = self.root / "executed"
        self.put("payload.py", f'from pathlib import Path\nPath({str(marker)!r}).write_text("bad")')
        _, output = builder.build(self.root)
        text = (output / "files/payload.html/index.html").read_text()
        parser = Links()
        parser.feed(text)
        self.assertEqual(len(parser.scripts), 2)
        self.assertTrue(all(src and src.endswith(("theme.js", "app.js")) for src in parser.scripts))
        self.assertNotIn('<img src=x', text)
        self.assertFalse(marker.exists())

    def test_nested_unicode_and_unusual_paths_have_valid_links(self):
        for name in ("папка/решение #1 <&>.py", 'quotes/"hello".hs', "foo", "foo.html/test.js", "folder/url"):
            self.put(name, "hello\n")
        _, output = builder.build(self.root)
        for page in output.rglob("*.html"):
            if not page.is_file():
                continue
            parser = Links()
            parser.feed(page.read_text())
            for link in parser.links:
                url = urlsplit(link)
                if url.scheme or not url.path:
                    continue
                target = (page.parent / unquote(url.path)).resolve()
                self.assertTrue(target.is_relative_to(output.resolve()), (page, link))
                self.assertTrue(target.exists(), (page, link))

    def test_empty_gallery_and_empty_file(self):
        count, output = builder.build(self.root)
        self.assertEqual(count, 0)
        self.assertIn("Здесь начинается коллекция", (output / "index.html").read_text())
        self.put("empty.hs", "")
        count, output = builder.build(self.root)
        self.assertEqual(count, 1)
        self.assertIn("Файл пока пуст", (output / "files/empty.hs/index.html").read_text())

    def test_line_numbers_and_whitespace(self):
        for text, count in [("a\nb", 2), ("\na\n\n", 3), ("", 0), ("\n", 1), ("\tfoo\n", 1), ("a\u2028b", 1)]:
            with self.subTest(text=text):
                rendered = builder.code_html(text, builder.lexer_for("x.txt", text))
                self.assertEqual(rendered.count('class="code-line"'), count)
                for number in range(1, count + 1):
                    self.assertIn(f'id="L{number}"', rendered)

    def test_multiline_token_spans_stay_balanced(self):
        text = 'value = """line 1\nline 2\nline 3"""\n'
        rendered = builder.code_html(text, builder.lexer_for("x.py", text))
        for line in rendered.split('\n'):
            self.assertEqual(line.count('<span'), line.count('</span>'))

    def test_source_cannot_overlap_output(self):
        config = (self.root / "site.toml").read_text().replace('source = "code"', 'source = "dist"')
        (self.root / "site.toml").write_text(config)
        with self.assertRaises(ValueError):
            builder.build(self.root)

    def test_catppuccin_assets_and_controls(self):
        self.put("hello.hs", 'main = putStrLn "hello"\n')
        _, output = builder.build(self.root)
        for page in (output / "index.html", output / "files/hello.hs/index.html"):
            html = page.read_text()
            self.assertIn('data-theme="latte"', html)
            self.assertIn('data-theme-choice="latte"', html)
            self.assertIn('data-theme-choice="mocha"', html)
            self.assertIn('id="theme-switch"', html)
            self.assertNotIn('id="theme-toggle"', html)
            self.assertLess(html.index('assets/theme.js'), html.index('assets/style.css'))
        for name in ("style.css", "syntax.css", "theme.js"):
            self.assertEqual((output / "assets" / name).read_bytes(),
                             (self.root / "site/assets" / name).read_bytes())

    def test_catppuccin_palette_and_syntax_share_variables(self):
        assets = self.root / "site/assets"
        css = (assets / "style.css").read_text()
        syntax = (assets / "syntax.css").read_text()
        for color in ("#eff1f5", "#4c4f69", "#8839ef", "#1e1e2e", "#cdd6f4", "#cba6f7"):
            self.assertIn(color, css)
        self.assertIn('data-theme="mocha"', css)
        for token in ("--ctp-mauve", "--ctp-blue", "--ctp-yellow", "--ctp-green", "--ctp-peach"):
            self.assertIn(f"var({token})", syntax)
        self.assertNotIn("friendly", syntax)
        self.assertNotIn("github-dark", syntax)

    def test_rebuild_removes_stale_pages(self):
        source = self.put("old.hs", "main = pure ()")
        _, output = builder.build(self.root)
        self.assertTrue((output / "files/old.hs/index.html").exists())
        source.unlink()
        builder.build(self.root)
        self.assertFalse((output / "files/old.hs/index.html").exists())


if __name__ == "__main__":
    unittest.main()
