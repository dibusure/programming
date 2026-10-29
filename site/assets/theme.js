// Apply the theme before stylesheets load, without a flash of the wrong palette.
(() => {
  'use strict';
  const storageKey = 'programming-theme';
  const systemTheme = window.matchMedia('(prefers-color-scheme: dark)');
  const normalize = (value) => {
    if (value === 'light') return 'latte'; // Preserve preferences from version 1.
    if (value === 'dark') return 'mocha';
    return value === 'latte' || value === 'mocha' ? value : null;
  };
  let selected = null;
  try { selected = normalize(localStorage.getItem(storageKey)); } catch (_) {}

  function applyTheme() {
    const theme = selected ?? (systemTheme.matches ? 'mocha' : 'latte');
    document.documentElement.dataset.theme = theme;
    document.querySelectorAll('[data-theme-choice]').forEach((button) => {
      button.setAttribute('aria-pressed', String(button.dataset.themeChoice === theme));
    });
  }

  applyTheme();
  document.addEventListener('DOMContentLoaded', () => {
    document.querySelectorAll('[data-theme-choice]').forEach((button) => {
      button.addEventListener('click', () => {
        const theme = normalize(button.dataset.themeChoice);
        if (!theme) return;
        selected = theme;
        // Switching still works in this page when browser storage is blocked.
        try { localStorage.setItem(storageKey, selected); } catch (_) {}
        applyTheme();
      });
    });
    const control = document.getElementById('theme-switch');
    if (control) control.hidden = false;
    applyTheme();
  });

  // Follow OS changes only until the visitor makes an explicit choice.
  systemTheme.addEventListener('change', () => {
    if (selected === null) applyTheme();
  });
  // Keep tabs in sync, including removal of the preference or cleared storage.
  window.addEventListener('storage', (event) => {
    if (event.key === storageKey || event.key === null) {
      selected = normalize(event.newValue);
      applyTheme();
    }
  });
})();
