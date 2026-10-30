'use strict';
const $ = (selector) => document.querySelector(selector);
const $$ = (selector) => [...document.querySelectorAll(selector)];
$$('.js-only').forEach((element) => { element.hidden = false; });
const search = $('#search');
const language = $('#language');
const folders = $$('.tree-folder');
let beforeSearch = null;
// Links inside summary navigate without toggling the parent details element.
$('.folder-readme, .folder-browse, .folder-direct-link').forEach((link) =>
  link.addEventListener('click', (event) => event.stopPropagation()));
function filterFiles() {
  const query = search.value.trim().toLocaleLowerCase();
  if (query && beforeSearch === null) {
    beforeSearch = new Map(folders.map((folder) => [folder, folder.open]));
  }
  $$('.tree-file').forEach((link) => {
    link.hidden = !link.dataset.search.toLocaleLowerCase().includes(query);
  });
  [...folders].reverse().forEach((folder) => {
    const matches = [...folder.querySelectorAll('.tree-file')].some((link) => !link.hidden)
      || Boolean(query && folder.dataset.folderPath.toLocaleLowerCase().includes(query));
    folder.hidden = Boolean(query) && !matches;
    if (query) folder.open = matches;
    else if (beforeSearch !== null) folder.open = beforeSearch.get(folder);
  });
  if (!query) beforeSearch = null;
  $('#tree-empty').hidden = $('.tree-file').some((link) => !link.hidden)
    || folders.some((folder) => !folder.hidden);
  let count = 0;
  $$('.file-row').forEach((row) => {
    row.hidden = !row.dataset.search.toLocaleLowerCase().includes(query)
      || Boolean(language?.value && row.dataset.language !== language.value);
    if (!row.hidden) count += 1;
  });
  if ($('#result-count')) $('#result-count').textContent = count;
  if ($('#list-empty')) $('#list-empty').hidden = count > 0 || !$$('.file-row').length;
}
filterFiles();
search.addEventListener('input', filterFiles);
language?.addEventListener('change', filterFiles);
document.addEventListener('keydown', (event) => {
  const target = event.target;
  if (event.key === '/' && !event.ctrlKey && !event.metaKey && !event.altKey
      && !target.closest('input, textarea, select, [contenteditable="true"]')) {
    event.preventDefault(); search.focus();
  }
  if (event.key === 'Escape' && document.activeElement === search) {
    search.value = ''; filterFiles(); search.blur();
  }
});
let toastTimer;
function toast(message) {
  const element = $('#toast');
  element.textContent = message; element.hidden = false;
  clearTimeout(toastTimer);
  toastTimer = setTimeout(() => { element.hidden = true; }, 2600);
}
$('#copy-code')?.addEventListener('click', async () => {
  try {
    await navigator.clipboard.writeText($('#raw-source').value);
    toast('Код скопирован');
  } catch (_) {
    const selection = getSelection();
    const range = document.createRange();
    const code = $('.highlight code');
    if (code && selection) { range.selectNodeContents(code); selection.removeAllRanges(); selection.addRange(range); }
    toast('Буфер обмена недоступен. Выдели код или скачай файл.');
  }
});
$('#wrap-toggle')?.addEventListener('click', (event) => {
  const enabled = $('.code-panel').classList.toggle('wrap');
  event.currentTarget.setAttribute('aria-pressed', String(enabled));
});

$('#copy-folder-link')?.addEventListener('click', async () => {
  try {
    await navigator.clipboard.writeText(window.location.href);
    toast('Ссылка на папку скопирована');
  } catch (_) {
    toast('Не удалось скопировать. Скопируй адрес из строки браузера.');
  }
});
