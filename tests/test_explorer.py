"""Regression coverage for the file explorer and self-hosted font assets."""
from html.parser import HTMLParser
from io import BytesIO
from pathlib import Path
from unittest.mock import patch
import hashlib

import unittest
import test_build
from test_build import builder, ROOT


class Elements(HTMLParser):
    def __init__(self):
        super().__init__()
        self.elements = []

    def handle_starttag(self, tag, attrs):
        self.elements.append((tag, dict(attrs)))


class ExplorerTests(unittest.TestCase):
    setUp = test_build.GalleryTests.setUp
    tearDown = test_build.GalleryTests.tearDown
    put = test_build.GalleryTests.put

    def test_folders_closed_even_on_nested_active_page(self):
        self.put('outer/inner/main.hs', 'main = pure ()')
        _, output = builder.build(self.root)
        for page in (output / 'index.html', output / 'files/outer/inner/main.hs/index.html'):
            parser = Elements()
            parser.feed(page.read_text())
            folders = [attrs for tag, attrs in parser.elements if tag == 'details']
            self.assertEqual(len(folders), 2)
            self.assertTrue(all('open' not in attrs for attrs in folders))

    def test_readme_links_ignore_case_and_only_use_direct_children(self):
        for folder, name in [('one', 'Readme.md'), ('two', 'README.md'), ('three', 'readme.md')]:
            self.put(f'{folder}/{name}', '# Documentation')
        self.put('parent/child/README.md', '# Nested')
        self.put('without/main.py', 'print(1)')
        files = builder.collect(self.root / 'code', self.config)
        parser = Elements()
        parser.feed(builder.tree_html(files, '../../', 'one/Readme.md'))
        links = [attrs for tag, attrs in parser.elements if attrs.get('class') == 'folder-readme']
        self.assertEqual(len(links), 4)
        self.assertEqual({a['href'] for a in links}, {
            '../../files/one/Readme.md/', '../../files/two/README.md/',
            '../../files/three/readme.md/', '../../files/parent/child/README.md/'})
        self.assertEqual(sum(a.get('aria-current') == 'page' for a in links), 1)

    def test_readme_folder_labels_and_urls_are_escaped(self):
        self.put('a <&> "quoted"/Readme.md', '# Safe')
        files = builder.collect(self.root / 'code', self.config)
        rendered = builder.tree_html(files, './')
        self.assertIn('a &lt;&amp;&gt; &quot;quoted&quot;', rendered)
        self.assertIn('a%20%3C%26%3E%20%22quoted%22/Readme.md/', rendered)
        self.assertNotIn('<&>', rendered)

    def test_every_file_icon_uses_a_nerd_font_glyph(self):
        for extension, icon in builder.ICON_BY_EXTENSION.items():
            with self.subTest(extension=extension):
                self.assertIn(icon, builder.NERD_GLYPHS)
                rendered = builder.file_icon({'name': 'x.' + extension}, '../')
                self.assertIn(f'&#x{builder.NERD_GLYPHS[icon]:x};', rendered)
                self.assertIn('nerd-icon', rendered)
                self.assertIn('aria-hidden="true"', rendered)
                self.assertNotIn('<svg', rendered)
                self.assertNotIn('icons.svg', rendered)
        self.assertIn('&#xf405;', builder.file_icon({'name': 'Readme.md'}, './'))
        self.assertIn('&#xe64e;', builder.file_icon({'name': 'notes', 'language': 'Text only'}, './'))
        self.assertIn('&#xe606;', builder.file_icon({'name': 'script', 'language': 'Python'}, './'))
        self.assertIn('&#xe61f;', builder.file_icon({'name': 'Main.lhs'}, './'))
        self.assertIn('&#xf413;', builder.folder_icon('./'))

    def test_rubik_ui_and_iosevka_code_with_same_origin_assets(self):
        css = (ROOT / 'site/assets/style.css').read_text()
        faces = (ROOT / 'site/assets/fonts.css').read_text()
        self.assertIn("--mono: 'Iosevka', monospace", css)
        self.assertIn("--sans: 'Rubik', sans-serif", css)
        self.assertIn('font:16px/1.6 var(--sans)', css)
        self.assertIn('font:14px/1.9 var(--mono)', css)
        self.assertIn("code {font-family:var(--mono)}", css)
        self.assertIn('font:12px/1.5 var(--sans)', css)  # theme buttons
        self.assertIn('font:500 clamp(22px,3vw,35px)/1.3 var(--mono)', css)  # filename
        self.assertIn("font-family: 'Rubik'", faces)
        self.assertIn('font-weight: 300 900', faces)
        self.assertIn("font-style: italic; font-weight: 300 900", faces)
        for old in ('system-ui', 'Georgia', 'Segoe UI', 'Consolas', 'SFMono'):
            self.assertNotIn(old, css)
        self.assertNotIn('https://', faces)
        for name in (*builder.FONT_FILES, *builder.RUBIK_FONT_FILES):
            self.assertIn(f'fonts/{name}', faces)
        icons = (ROOT / 'site/assets/nerd-icons.css').read_text()
        self.assertNotIn('https://', icons)
        self.assertIn('font-family: "Symbols Nerd Font"', icons)
        self.assertIn(f'fonts/{builder.NERD_FONT_FILE}', icons)
        self.assertIn('font-synthesis: none', icons)

    def test_icon_font_and_stylesheet_are_linked_on_nested_pages(self):
        self.put('one/two/main.py', 'print(1)')
        _, output = builder.build(self.root)
        page = (output / 'files/one/two/main.py/index.html').read_text()
        self.assertIn('href="../../../../assets/nerd-icons.css"', page)
        self.assertNotIn('assets/icons.svg', page)
        self.assertTrue((output / 'assets/nerd-icons.css').is_file())

    def test_font_download_includes_licenses_and_pinned_revisions(self):
        _, output = builder.build(self.root)
        ttf = b'\x00\x01\x00\x00test-font'
        rubik_license = b'Rubik OFL test license'
        blob_sha = hashlib.sha1(b'blob ' + str(len(ttf)).encode() + b'\0' + ttf).hexdigest()
        license_sha = hashlib.sha1(b'blob ' + str(len(rubik_license)).encode() + b'\0' + rubik_license).hexdigest()

        def response(url, timeout):
            self.assertEqual(timeout, 45)
            if url.startswith(builder.RUBIK_FONT_BASE_URL):
                self.assertIn(builder.RUBIK_REVISION, url)
                return BytesIO(rubik_license if url.endswith('/OFL.txt') else ttf)
            if url.startswith(builder.NERD_FONT_BASE_URL):
                self.assertIn('/v3.4.0/', url)
                return BytesIO(b'Nerd Fonts licenses' if url.endswith('/LICENSE') else ttf)
            if url == builder.FONT_LICENSE_URL:
                return BytesIO(b'OFL license')
            self.assertIn(builder.FONT_REVISION, url)
            return BytesIO(b'wOF2test')

        with patch.object(builder, 'urlopen', side_effect=response) as request:
            with patch.object(builder, 'NERD_FONT_BLOB_SHA', blob_sha):
                with patch.object(builder, 'RUBIK_FONT_FILES', {name: (upstream, blob_sha)
                    for name, (upstream, _) in builder.RUBIK_FONT_FILES.items()}):
                    with patch.object(builder, 'RUBIK_LICENSE_BLOB_SHA', license_sha):
                        builder.download_fonts(output)
        self.assertEqual(request.call_count, len(builder.FONT_FILES) + 4 + len(builder.RUBIK_FONT_FILES))
        for name in (*builder.FONT_FILES, 'LICENSE', builder.NERD_FONT_FILE, builder.NERD_FONT_LICENSE,
                     *builder.RUBIK_FONT_FILES, builder.RUBIK_FONT_LICENSE):
            self.assertTrue((output / 'assets/fonts' / name).is_file())

    def test_invalid_fonts_fail_instead_of_publishing_a_fallback(self):
        _, output = builder.build(self.root)
        with patch.object(builder, 'urlopen', side_effect=lambda *a, **kw: BytesIO(b'<html>error</html>')) as request:
            with patch.object(builder.time, 'sleep'):
                with self.assertRaises(ValueError):
                    builder.download_fonts(output)
        self.assertEqual(request.call_count, 3)
        self.assertFalse((output / 'assets/fonts' / builder.FONT_FILES[0]).exists())

    def test_wrong_nerd_font_hash_fails_the_build(self):
        _, output = builder.build(self.root)

        def response(url, timeout):
            if url.endswith(builder.NERD_FONT_FILE):
                return BytesIO(b'\x00\x01\x00\x00wrong-font')
            return BytesIO(b'OFL license' if url == builder.FONT_LICENSE_URL else b'wOF2test')

        with patch.object(builder, 'urlopen', side_effect=response):
            with patch.object(builder.time, 'sleep'):
                with self.assertRaisesRegex(ValueError, 'pinned official font'):
                    builder.download_fonts(output)
        self.assertFalse((output / 'assets/fonts' / builder.NERD_FONT_FILE).exists())

    def test_corrupt_rubik_is_rejected_even_if_it_is_a_valid_ttf_header(self):
        _, output = builder.build(self.root)
        nerd = b"\x00\x01\x00\x00nerd"
        nerd_sha = hashlib.sha1(b"blob " + str(len(nerd)).encode() + b"\0" + nerd).hexdigest()

        def response(url, timeout):
            if url.startswith(builder.RUBIK_FONT_BASE_URL):
                return BytesIO(b"\x00\x01\x00\x00tampered")
            if url.endswith(builder.NERD_FONT_FILE):
                return BytesIO(nerd)
            return BytesIO(b'OFL license' if url.endswith('/LICENSE') or url.endswith('.md') else b'wOF2test')

        with patch.object(builder, 'urlopen', side_effect=response):
            with patch.object(builder, 'NERD_FONT_BLOB_SHA', nerd_sha):
                with patch.object(builder.time, 'sleep'):
                    with self.assertRaisesRegex(ValueError, 'Rubik asset does not match'):
                        builder.download_fonts(output)
        self.assertFalse((output / 'assets/fonts/Rubik-Variable.ttf').exists())
