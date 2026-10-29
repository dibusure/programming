"""Regression coverage for the file explorer and self-hosted Iosevka assets."""
from html.parser import HTMLParser
from io import BytesIO
from pathlib import Path
from unittest.mock import patch
import xml.etree.ElementTree as ET

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

    def test_every_file_icon_has_a_local_svg_symbol(self):
        sprite = ET.parse(ROOT / 'site/assets/icons.svg')
        symbols = {node.attrib['id'] for node in sprite.getroot()}
        for extension, icon in builder.ICON_BY_EXTENSION.items():
            with self.subTest(extension=extension):
                self.assertIn(icon, symbols)
                rendered = builder.file_icon({'name': 'x.' + extension}, '../')
                self.assertIn(f'assets/icons.svg#{icon}', rendered)
                self.assertIn('aria-hidden="true"', rendered)
        self.assertIn('icons.svg#readme', builder.file_icon({'name': 'Readme.md'}, './'))
        self.assertIn('icons.svg#text', builder.file_icon({'name': 'notes', 'language': 'Text only'}, './'))
        self.assertIn('icons.svg#python', builder.file_icon({'name': 'script', 'language': 'Python'}, './'))
        self.assertIn('folder', symbols)

    def test_all_typefaces_are_iosevka_and_assets_are_same_origin(self):
        css = (ROOT / 'site/assets/style.css').read_text()
        faces = (ROOT / 'site/assets/fonts.css').read_text()
        self.assertIn("--mono: 'Iosevka', monospace", css)
        for old in ('system-ui', 'Georgia', 'Segoe UI', 'Consolas', 'SFMono'):
            self.assertNotIn(old, css)
        self.assertNotIn('https://', faces)
        for name in builder.FONT_FILES:
            self.assertIn(f'fonts/{name}', faces)

    def test_font_download_includes_license_and_pinned_revision(self):
        _, output = builder.build(self.root)
        def response(url, timeout):
            if url == builder.FONT_LICENSE_URL:
                self.assertIn('/be5invis/Iosevka/v34.9.1/LICENSE.md', url)
            else:
                self.assertIn(builder.FONT_REVISION, url)
            self.assertEqual(timeout, 45)
            return BytesIO(b'OFL license' if url == builder.FONT_LICENSE_URL else b'wOF2test')
        with patch.object(builder, 'urlopen', side_effect=response) as request:
            builder.download_fonts(output)
        self.assertEqual(request.call_count, len(builder.FONT_FILES) + 1)
        for name in (*builder.FONT_FILES, 'LICENSE'):
            self.assertTrue((output / 'assets/fonts' / name).is_file())

    def test_invalid_fonts_fail_instead_of_publishing_a_fallback(self):
        _, output = builder.build(self.root)
        with patch.object(builder, 'urlopen', side_effect=lambda *a, **kw: BytesIO(b'<html>error</html>')) as request:
            with patch.object(builder.time, 'sleep'):
                with self.assertRaises(ValueError):
                    builder.download_fonts(output)
        self.assertEqual(request.call_count, 3)
        self.assertFalse((output / 'assets/fonts' / builder.FONT_FILES[0]).exists())

