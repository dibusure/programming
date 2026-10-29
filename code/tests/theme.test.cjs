// Optional theme behavior tests: node --test tests/theme.test.cjs
// No npm dependencies. A small DOM/storage double exercises the actual theme.js.
'use strict';
const { test } = require('node:test');
const assert = require('node:assert/strict');
const fs = require('node:fs');
const path = require('node:path');
const vm = require('node:vm');
const source = fs.readFileSync(path.join(__dirname, '../site/assets/theme.js'), 'utf8');

function harness({ stored = null, dark = false, blocked = false } = {}) {
  const listeners = {};
  const root = { dataset: { theme: 'latte' } };
  const control = { hidden: true };
  const buttons = ['latte', 'mocha'].map((theme) => ({
    dataset: { themeChoice: theme }, attributes: {},
    setAttribute(key, value) { this.attributes[key] = value; },
    addEventListener(type, callback) { this[type] = callback; },
  }));
  let mounted = false;
  let saved = stored;
  const system = { matches: dark, addEventListener(type, fn) { listeners.system = fn; } };
  const document = {
    documentElement: root,
    querySelectorAll() { return mounted ? buttons : []; },
    getElementById() { return control; },
    addEventListener(type, fn) { listeners.dom = fn; },
  };
  const localStorage = {
    getItem() { if (blocked) throw new Error('Blocked storage'); return saved; },
    setItem(key, value) { if (blocked) throw new Error('Blocked storage'); saved = value; },
  };
  const window = {
    matchMedia() { return system; },
    addEventListener(type, fn) { listeners[type] = fn; },
  };
  vm.runInNewContext(source, { window, document, localStorage }, { filename: 'theme.js' });
  return {
    root, control, buttons,
    get stored() { return saved; },
    ready() { mounted = true; listeners.dom(); },
    click(theme) { buttons.find((button) => button.dataset.themeChoice === theme).click(); },
    system(dark) { system.matches = dark; listeners.system(); },
    storage(value, key = 'programming-theme') { listeners.storage({ key, newValue: value }); },
  };
}

test('first visit follows the system, before the DOM is ready', () => {
  for (const [dark, flavor] of [[false, 'latte'], [true, 'mocha']]) {
    const h = harness({ dark });
    assert.equal(h.root.dataset.theme, flavor);
    assert.equal(h.stored, null);
    assert.equal(h.control.hidden, true);
  }
});

test('saved Catppuccin preferences override the system', () => {
  for (const stored of ['latte', 'mocha']) {
    const h = harness({ stored, dark: stored === 'latte' });
    assert.equal(h.root.dataset.theme, stored);
  }
});

test('old light and dark preferences migrate correctly', () => {
  for (const [stored, flavor] of [['light', 'latte'], ['dark', 'mocha']]) {
    assert.equal(harness({ stored }).root.dataset.theme, flavor);
  }
});

test('invalid stored values fall back to the system', () => {
  for (const stored of ['', 'bad', '__proto__', '<script>', 'Mocha']) {
    assert.equal(harness({ stored, dark: true }).root.dataset.theme, 'mocha');
  }
});

test('the two controls have correct accessible pressed states', () => {
  const h = harness({ dark: true });
  h.ready();
  assert.equal(h.control.hidden, false);
  assert.deepEqual(h.buttons.map((button) => button.attributes['aria-pressed']), ['false', 'true']);
});

test('clicking either theme immediately updates and persists the choice', () => {
  const h = harness();
  h.ready();
  for (const theme of ['mocha', 'latte', 'mocha']) {
    h.click(theme);
    assert.equal(h.root.dataset.theme, theme);
    assert.equal(h.stored, theme);
    assert.equal(h.buttons.filter((button) => button.attributes['aria-pressed'] === 'true').length, 1);
  }
});

test('saved selection is restored in a new page instance', () => {
  const h = harness();
  h.ready();
  h.click('mocha');
  assert.equal(harness({ stored: h.stored, dark: false }).root.dataset.theme, 'mocha');
});

test('automatic theme follows system changes without writing storage', () => {
  const h = harness();
  h.system(true);
  assert.equal(h.root.dataset.theme, 'mocha');
  h.system(false);
  assert.equal(h.root.dataset.theme, 'latte');
  assert.equal(h.stored, null);
});

test('a manual selection is not overwritten by system changes', () => {
  const h = harness();
  h.ready();
  h.click('latte');
  h.system(true);
  assert.equal(h.root.dataset.theme, 'latte');
});

test('blocked localStorage does not break initial rendering or switching', () => {
  const h = harness({ blocked: true, dark: true });
  assert.equal(h.root.dataset.theme, 'mocha');
  h.ready();
  h.click('latte');
  assert.equal(h.root.dataset.theme, 'latte');
});

test('storage events synchronize an explicit choice from another tab', () => {
  const h = harness();
  h.ready();
  h.storage('mocha');
  assert.equal(h.root.dataset.theme, 'mocha');
  assert.equal(h.buttons[1].attributes['aria-pressed'], 'true');
});

test('unrelated storage events are ignored', () => {
  const h = harness();
  h.storage('mocha', 'other-app');
  assert.equal(h.root.dataset.theme, 'latte');
});

test('removing or clearing the preference restores automatic selection', () => {
  for (const key of ['programming-theme', null]) {
    const h = harness({ stored: 'latte', dark: true });
    h.storage(null, key);
    assert.equal(h.root.dataset.theme, 'mocha');
    h.system(false);
    assert.equal(h.root.dataset.theme, 'latte');
  }
});
