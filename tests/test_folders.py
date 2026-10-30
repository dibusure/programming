"""Regression coverage for shareable static directory routes."""
from html.parser import HTMLParser
import unittest
from urllib.parse import quote

import test_build
from test_build import builder


class DirectoryParser(HTMLParser):
    def __init__(self):
        super().__init__()
        self.rows = []
        self.links = []
        self.folders = []

    def handle_starttag(self, tag, attrs):
        attrs = dict(attrs)
        if tag == 'a':
            self.links.append(attrs)
            if 'file-row' in attrs.get('class', '').split():
                self.rows.append(attrs)
        if tag == 'details':
            self.folders.append(attrs)


class DirectoryPagesTests(unittest.TestCase):
    setUp = test_build.GalleryTests.setUp
    tearDown = test_build.GalleryTests.tearDown
    put = test_build.GalleryTests.put

    def test_root_and_nested_pages_are_independently_addressable(self):
        self.put('c/aesc informatix/entrance/1598.py', 'print(42)')
        self.put('c/aesc informatix/Readme.md', '# Notes')
        _, output = builder.build(self.root)
        for folder in ('', 'c', 'c/aesc informatix', 'c/aesc informatix/entrance'):
            with self.subTest(folder=folder):
                page = output / builder.folder_url(folder) / 'index.html'
                self.assertTrue(page.is_file(), page)
                html = page.read_text()
                self.assertIn('id="copy-folder-link"', html)
                self.assertIn('data-theme-choice="mocha"', html)
                self.assertIn('data-theme-choice="latte"', html)
        self.assertEqual(builder.folder_url('c/aesc informatix/entrance'),
                         'folders/c/aesc%20informatix/entrance/')

    def test_directory_lists_only_immediate_children(self):
        self.put('one/Readme.md', '# docs')
        self.put('one/child/source.hs', 'main = pure ()')
        self.put('one/child/grandchild/deeper.py', 'print(1)')
        self.put('another/main.py', 'print(2)')
        _, output = builder.build(self.root)
        parser = DirectoryParser()
        parser.feed((output / 'folders/one/index.html').read_text())
        self.assertEqual([a['href'] for a in parser.rows],
                         ['../../folders/one/child/', '../../files/one/Readme.md/'])
        child = DirectoryParser()
        child.feed((output / 'folders/one/child/index.html').read_text())
        self.assertEqual([a['href'] for a in child.rows],
                         ['../../../folders/one/child/grandchild/',
                          '../../../files/one/child/source.hs/'])

    def test_file_and_directory_breadcrumbs(self):
        self.put('русский/имя #1 <&>.hs', 'main = pure ()')
        _, output = builder.build(self.root)
        folder = (output / 'folders/русский/index.html').read_text()
        filepage = (output / 'files/русский/имя #1 <&>.hs/index.html').read_text()
        self.assertIn('href="../../folders/"', folder)  # Parent code/
        self.assertIn('href="../../../folders/русский/"', filepage)
        self.assertIn('имя #1 &lt;&amp;&gt;.hs', filepage)
        self.assertIn('href="folders/русский/"', (output / 'index.html').read_text())

    def test_empty_hidden_excluded_and_symlinked_folders(self):
        self.put('public/main.py', 'print(1)')
        self.put('public/.private/secret.py', 'secret')
        self.put('node_modules/module/index.js', 'not public')
        (self.root / 'code/empty').mkdir()
        (self.root / 'code/external').symlink_to(self.root, target_is_directory=True)
        folders = builder.collect_folders(self.root / 'code', self.config)
        self.assertEqual(set(folders), {'public', 'empty'})
        _, output = builder.build(self.root)
        empty = (output / 'folders/empty/index.html')
        self.assertTrue(empty.is_file())
        self.assertIn('пока нет публикуемых', empty.read_text())
        self.assertIn('folder-browse', empty.read_text())
        for unwanted in ('external', 'node_modules', '.private'):
            self.assertFalse((output / 'folders' / unwanted / 'index.html').exists())

    def test_readme_and_folder_navigation_are_separate(self):
        self.put('docs/Readme.md', '# docs')
        self.put('misc/source.py', 'print(1)')
        files = builder.collect(self.root / 'code', self.config)
        folders = builder.collect_folders(self.root / 'code', self.config)
        parser = DirectoryParser()
        parser.feed(builder.tree_html(files, './', folders=folders))
        readme = [a['href'] for a in parser.links if a.get('class') == 'folder-readme']
        direct = [a['href'] for a in parser.links if a.get('class') == 'folder-direct-link']
        browse = [a['href'] for a in parser.links if a.get('class') == 'folder-browse']
        self.assertEqual(readme, ['./files/docs/Readme.md/'])
        self.assertEqual(set(direct), {'./folders/docs/', './folders/misc/'})
        self.assertEqual(browse, ['./folders/misc/'])
        self.assertTrue(all('open' not in d for d in parser.folders))
        app = (self.root / 'site/assets/app.js').read_text()
        self.assertIn('.folder-browse, .folder-direct-link', app)
        self.assertIn('navigator.clipboard.writeText(window.location.href)', app)
        self.assertIn('folder.hidden = Boolean(query) && !matches', app)
        self.assertIn('folder.dataset.folderPath', app)
        self.assertIn('data-folder-path="docs"', builder.tree_html(files, './', folders=folders))

    def test_encoded_punctuation_folders_and_safe_html(self):
        name = 'a #?&" <кириллица>'
        self.put(f'{name}/main.py', 'print(1)')
        _, output = builder.build(self.root)
        url = builder.folder_url(name)
        self.assertIn(quote(name, safe=''), url)
        self.assertTrue((output / 'folders' / name / 'index.html').is_file())
        home = (output / 'index.html').read_text()
        self.assertIn('href="' + url + '"', home)
        self.assertIn('a #?&amp;&quot; &lt;кириллица&gt;', home)

    def test_rebuild_cleans_up_removed_folders(self):
        file = self.put('old/main.py', 'print(1)')
        _, output = builder.build(self.root)
        self.assertTrue((output / 'folders/old/index.html').exists())
        file.unlink()
        (self.root / 'code/old').rmdir()
        builder.build(self.root)
        self.assertFalse((output / 'folders/old/index.html').exists())


if __name__ == '__main__':
    unittest.main()
