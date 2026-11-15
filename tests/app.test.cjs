'use strict';
const { test } = require('node:test');
const assert = require('node:assert/strict');
const fs = require('node:fs');
const path = require('node:path');
const vm = require('node:vm');

const source = fs.readFileSync(path.join(__dirname, '../site/assets/app.js'), 'utf8');

function harness() {
  const listeners = {};
  const search = { value: '', hidden: false, addEventListener(type, fn) { listeners['search:' + type] = fn; } };
  const language = { value: '', addEventListener(type, fn) { listeners['language:' + type] = fn; } };
  const treeFile = { hidden: false, dataset: { search: 'src/hello.py Python' } };
  const folder = {
    open: false, hidden: false, dataset: { folderPath: 'src' },
    querySelectorAll(selector) { return selector === '.tree-file' ? [treeFile] : []; },
  };
  const row = { hidden: false, dataset: { search: 'src/hello.py Python', language: 'Python' } };
  const treeEmpty = { hidden: true };
  const listEmpty = { hidden: true };
  const resultCount = { textContent: '' };
  const folderLink = { addEventListener(type, fn) { this[type] = fn; } };
  const singles = { '#search': search, '#language': language, '#tree-empty': treeEmpty,
    '#list-empty': listEmpty, '#result-count': resultCount };
  const groups = { '.js-only': [], '.tree-folder': [folder],
    '.folder-readme, .folder-browse, .folder-direct-link': [folderLink],
    '.tree-file': [treeFile], '.file-row': [row] };
  const document = {
    querySelector(selector) { return singles[selector] ?? (groups[selector] ?? [])[0] ?? null; },
    querySelectorAll(selector) { return groups[selector] ?? []; },
    addEventListener(type, fn) { listeners[type] = fn; },
  };
  vm.runInNewContext(source, { document }, { filename: 'app.js' });
  return { search, language, treeFile, folder, row, treeEmpty, listEmpty, resultCount,
    input(value) { search.value = value; listeners['search:input'](); },
    filter(value) { language.value = value; listeners['language:change'](); } };
}

test('the app initializes and attaches folder links without querySelector collection errors', () => {
  const ui = harness();
  assert.equal(ui.treeEmpty.hidden, true);
  assert.equal(ui.listEmpty.hidden, true);
  assert.equal(ui.resultCount.textContent, 1);
});

test('search expands matching directories and restores their state when cleared', () => {
  const ui = harness();
  ui.input('hello');
  assert.equal(ui.folder.open, true);
  assert.equal(ui.row.hidden, false);
  ui.input('absent');
  assert.equal(ui.folder.hidden, true);
  assert.equal(ui.treeEmpty.hidden, false);
  assert.equal(ui.listEmpty.hidden, false);
  assert.equal(ui.resultCount.textContent, 0);
  ui.input('');
  assert.equal(ui.folder.open, false);
  assert.equal(ui.folder.hidden, false);
  assert.equal(ui.treeEmpty.hidden, true);
  assert.equal(ui.resultCount.textContent, 1);
});

test('language filter hides only nonmatching file rows', () => {
  const ui = harness();
  ui.filter('Haskell');
  assert.equal(ui.row.hidden, true);
  assert.equal(ui.resultCount.textContent, 0);
  ui.filter('Python');
  assert.equal(ui.row.hidden, false);
  assert.equal(ui.resultCount.textContent, 1);
});
