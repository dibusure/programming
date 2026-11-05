"""Build a static gallery. Source files are read as text, never imported or run."""
from __future__ import annotations

import argparse
import fnmatch
import hashlib
import html
import os
from pathlib import Path
import shutil
import subprocess
import tomllib
from urllib.parse import quote
from urllib.request import urlopen
import time

from pygments import highlight
from pygments.formatters import HtmlFormatter
from pygments.lexers import TextLexer, get_lexer_by_name, get_lexer_for_filename, guess_lexer
from pygments.util import ClassNotFound

ROOT = Path(__file__).resolve().parents[1]
CSP = "default-src 'self'; script-src 'self'; style-src 'self'; img-src 'self' data:; object-src 'none'; base-uri 'none'; form-action 'none'"
esc = html.escape


def plural(number: int, one: str, few: str, many: str) -> str:
    if 11 <= number % 100 <= 14:
        return many
    return one if number % 10 == 1 else few if 2 <= number % 10 <= 4 else many


def lexer_for(path: str, text: str, overrides: dict | None = None):
    options = dict(stripnl=False, ensurenl=False, tabsize=0)
    for pattern, alias in (overrides or {}).items():
        if fnmatch.fnmatchcase(path, pattern):
            return get_lexer_by_name(alias, **options)
    try:
        return get_lexer_for_filename(path, text, **options)
    except ClassNotFound:
        if text.startswith("#!"):
            try:
                return guess_lexer(text, **options)
            except ClassNotFound:
                pass
        return TextLexer(**options)


def excluded(relative: Path, patterns: list[str]) -> bool:
    return any(part.startswith(".") for part in relative.parts) or any(
        fnmatch.fnmatchcase(relative.as_posix(), pattern)
        or any(fnmatch.fnmatchcase(part, pattern) for part in relative.parts)
        for pattern in patterns
    )


def collect(source: Path, config: dict) -> list[dict]:
    if source.is_symlink() or not source.is_dir():
        raise ValueError("Папка с исходниками должна существовать и не быть символьной ссылкой.")
    files = []
    for directory, dirs, names in os.walk(source, followlinks=False):
        folder = Path(directory)
        dirs[:] = sorted(d for d in dirs if not (folder / d).is_symlink()
                         and not excluded((folder / d).relative_to(source), config["exclude"]))
        for name in sorted(names):
            path = folder / name
            relative = path.relative_to(source)
            if path.is_symlink() or not path.is_file() or excluded(relative, config["exclude"]):
                continue
            if path.stat().st_size > config["max_file_bytes"]:
                print(f"Пропущен большой файл: {relative}")
                continue
            raw = path.read_bytes()
            try:
                text = raw.decode("utf-8-sig")
            except UnicodeDecodeError:
                print(f"Пропущен файл не в UTF-8: {relative}")
                continue
            if any(ord(c) < 32 and c not in "\n\r\t" for c in text):
                print(f"Пропущен бинарный файл: {relative}")
                continue
            text = text.replace("\r\n", "\n").replace("\r", "\n")
            rel = relative.as_posix()
            lexer = lexer_for(rel, text, config.get("lexers"))
            digest = hashlib.sha256(rel.encode("utf-8")).hexdigest()[:24]
            files.append(dict(path=rel, name=name, folder=relative.parent.as_posix(),
                              text=text, raw=raw, lexer=lexer, language=lexer.name,
                              lines=text.count("\n") + int(bool(text) and not text.endswith("\n")), size=len(raw),
                              url="files/" + quote(rel, safe="/") + "/",
                              raw_url=f"raw/{digest}.txt"))
    return sorted(files, key=lambda f: f["path"].casefold())



def collect_folders(source: Path, config: dict) -> list[str]:
    """Directories visible on the public site, including empty directories."""
    if source.is_symlink() or not source.is_dir():
        raise ValueError("Исходная папка отсутствует или является символьной ссылкой.")
    folders = []
    for directory, dirs, _ in os.walk(source, followlinks=False):
        parent = Path(directory)
        dirs[:] = sorted(d for d in dirs if not (parent / d).is_symlink()
                         and not excluded((parent / d).relative_to(source), config["exclude"]))
        folders.extend((parent / d).relative_to(source).as_posix() for d in dirs)
    return sorted(folders, key=str.casefold)


def folder_url(folder: str) -> str:
    return "folders/" + (quote(folder, safe="/") + "/" if folder else "")


def breadcrumbs(path: str, prefix: str) -> str:
    """Link every parent in a file or directory path."""
    parts = path.split("/") if path else []
    items = [f'<a href="{prefix}">Коллекция</a>', '<span>/</span>',
             f'<a href="{prefix}folders/">code</a>' if parts else '<span aria-current="page">code</span>']
    for i, name in enumerate(parts):
        items.append('<span>/</span>')
        items.append(f'<a href="{prefix}{folder_url("/".join(parts[:i+1]))}">{esc(name)}</a>'
                     if i < len(parts) - 1 else
                     f'<span aria-current="page">{esc(name)}</span>')
    return '<nav class="breadcrumbs" aria-label="Путь к файлу или папке">' + "".join(items) + '</nav>'


def code_html(text: str, lexer) -> str:
    rendered = highlight(text, lexer, HtmlFormatter(nowrap=True)).split("\n")
    count = text.count("\n") + int(bool(text) and not text.endswith("\n"))
    if count == 0:
        return '<p class="empty-code">Файл пока пуст.</p>'
    # HtmlFormatter closes token spans at line boundaries, including multiline strings.
    rows = []
    for number, line in enumerate(rendered[:count], 1):
        rows.append(f'<span class="code-line" id="L{number}"><a class="line-number" href="#L{number}" '
                    f'aria-label="Строка {number}">{number}</a><span class="line-content">{line}</span></span>')
    return '<pre class="highlight" tabindex="0" aria-label="Исходный код"><code>' + "\n".join(rows) + '</code></pre>'



# File types use the official Nerd Fonts v3.4.0 glyphs, self-hosted at build time.
ICON_EXTENSIONS = {
    "python": "py pyw pyi pyx ipynb", "haskell": "hs lhs hsc cabal",
    "javascript": "js mjs cjs", "typescript": "ts mts cts", "react": "jsx tsx",
    "c": "c h", "cpp": "cpp cc cxx hpp hh hxx", "csharp": "cs csx",
    "rust": "rs", "go": "go", "java": "java class jar", "kotlin": "kt kts",
    "swift": "swift", "ruby": "rb rake gemspec", "php": "php phtml",
    "lua": "lua", "shell": "sh bash zsh fish ps1 bat cmd", "database": "sql sqlite db",
    "markdown": "md markdown mdx", "text": "txt rst org log", "json": "json jsonc jsonl",
    "config": "toml yaml yml ini conf cfg lock", "html": "html htm xml svg",
    "css": "css scss sass less", "functional": "ml mli fs fsx clj cljs cljc ex exs erl hrl lisp el scm rkt",
    "code": "dart scala pl pm r jl zig nim v asm s vue svelte",
}
ICON_BY_EXTENSION = {ext: icon for icon, extensions in ICON_EXTENSIONS.items() for ext in extensions.split()}
ICON_BY_LANGUAGE = {"Python": "python", "Haskell": "haskell", "Literate Haskell": "haskell",
                    "Bash": "shell", "Fish": "shell", "PowerShell": "shell", "Docker": "config"}


# Codepoints from ryanoasis/nerd-fonts v3.4.0/glyphnames.json.
# Seti UI language icons, Custom C/C++, Octicons for documents and folders.
NERD_GLYPHS = {
    "python": 0xE606, "haskell": 0xE61F, "javascript": 0xE60C,
    "typescript": 0xE628, "react": 0xE625, "c": 0xE61E, "cpp": 0xE61D,
    "csharp": 0xE648, "rust": 0xE68B, "go": 0xE627, "java": 0xE66D,
    "kotlin": 0xE634, "swift": 0xE655, "ruby": 0xE605, "php": 0xE608,
    "lua": 0xE620, "shell": 0xF489, "database": 0xE64D,
    "markdown": 0xE609, "text": 0xE64E, "json": 0xE60B,
    "config": 0xE615, "html": 0xE60E, "css": 0xE614,
    "functional": 0xF0627, "code": 0xF40D, "readme": 0xF405, "folder": 0xF413,
}


def file_icon(file: dict, prefix: str) -> str:
    name = file["name"].casefold()
    extension = Path(name).suffix.lstrip(".")
    icon = ICON_BY_EXTENSION.get(extension, ICON_BY_LANGUAGE.get(file.get("language"),
                                "text" if file.get("language") == "Text only" else "code"))
    if name in ("makefile", "dockerfile", "justfile", "cmakelists.txt"):
        icon = "config"
    if name in ("readme", "readme.md", "readme.markdown"):
        icon = "readme"
    return (f'<span class="file-icon nerd-icon icon-{icon}" aria-hidden="true">'
            f'&#x{NERD_GLYPHS[icon]:x};</span>')


def folder_icon(prefix: str) -> str:
    return (f'<span class="file-icon nerd-icon folder-icon" aria-hidden="true">'
            f'&#x{NERD_GLYPHS["folder"]:x};</span>')


def tree_html(files: list[dict], prefix: str, active: str = "",
              folders: list[str] | None = None, active_folder: str = "") -> str:
    tree: dict = {"dirs": {}, "files": []}
    if folders is None:
        folders = sorted({"/".join(f["path"].split("/")[:i])
                          for f in files for i in range(1, len(f["path"].split("/")))}, key=str.casefold)
    for folder in folders:
        node = tree
        for part in folder.split("/"):
            node = node["dirs"].setdefault(part, {"dirs": {}, "files": []})
    for file in files:
        node = tree
        for part in file["path"].split("/")[:-1]:
            node = node["dirs"].setdefault(part, {"dirs": {}, "files": []})
        node["files"].append(file)

    def render(node: dict, trail: str = "") -> str:
        result = []
        for name, child in sorted(node["dirs"].items(), key=lambda item: item[0].casefold()):
            full = trail + name + "/"
            # All folders start closed, including ancestors of the current file.
            # An anchor inside summary navigates; the independent chevron toggles details.
            readme = next((f for f in sorted(child["files"], key=lambda f: f["name"])
                           if f["name"].casefold() == "readme.md"), None)
            label = f'{folder_icon(prefix)}<span class="folder-name">{esc(name)}</span>'
            href = prefix + folder_url(full[:-1])
            current_folder = ' aria-current="page"' if full[:-1] == active_folder else ""
            if readme:
                current = ' aria-current="page"' if readme["path"] == active else ""
                label = (f'<a class="folder-readme" href="{prefix}{readme["url"]}"{current} '
                         f'title="Открыть {esc(readme["path"], quote=True)}">{label}</a>')
            else:
                label = f'<a class="folder-browse" href="{href}"{current_folder}>{label}</a>'
            direct_link = (f'<a class="folder-direct-link" href="{href}"{current_folder} '
                           f'aria-label="Открыть страницу папки {esc(full[:-1], quote=True)}" '
                           f'title="Открыть страницу папки">'
                           f'<span class="nerd-icon" aria-hidden="true">&#xf0c1;</span></a>')
            result.append(f'<details class="tree-folder" data-folder-path="{esc(full[:-1], quote=True)}">'
                          f'<summary title="Раскрыть или свернуть папку">'
                          f'<svg class="folder-chevron" viewBox="0 0 24 24" aria-hidden="true" focusable="false">'
                          f'<path d="m9 5 7 7-7 7"/></svg>{label}{direct_link}</summary>'
                          f'<div class="tree-children">{render(child, full)}</div></details>')
        for file in node["files"]:
            selected = ' aria-current="page"' if file["path"] == active else ""
            search = esc(file["path"] + " " + file["language"], quote=True)
            result.append(f'<a class="tree-file" data-search="{search}" href="{prefix}{file["url"]}"{selected}>'
                          f'{file_icon(file, prefix)}<span class="file-name">{esc(file["name"])}</span></a>')
        return "".join(result)
    return render(tree)


def revision(root: Path) -> str:
    supplied = os.environ.get("GITHUB_SHA") or os.environ.get("CF_PAGES_COMMIT_SHA")
    if supplied and all(c in "0123456789abcdef" for c in supplied.lower()) and len(supplied) == 40:
        return supplied
    try:
        return subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=root,
                                       stderr=subprocess.DEVNULL, text=True).strip()
    except (subprocess.CalledProcessError, FileNotFoundError):
        return ""


def layout(config: dict, files: list[dict], body: str, prefix: str, title: str, rev: str,
           active: str = "", folders: list[str] | None = None, active_folder: str = "") -> str:
    repo = "https://github.com/" + config["repository"]
    count = len(files)
    version = f'<a href="{repo}/commit/{rev}">{rev[:7]}</a>' if rev else 'локальная сборка'
    return f'''<!doctype html>
<html lang="ru" data-theme="latte"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width, initial-scale=1">
<meta http-equiv="Content-Security-Policy" content="{esc(CSP, quote=True)}">
<meta name="color-scheme" content="light dark"><meta name="description" content="{esc(config['subtitle'], quote=True)}">
<title>{esc(title)} · {esc(config['repository'])}</title>
<script src="{prefix}assets/theme.js"></script>
<link rel="icon" href="{prefix}assets/favicon.svg" type="image/svg+xml">
<link rel="stylesheet" href="{prefix}assets/fonts.css"><link rel="stylesheet" href="{prefix}assets/style.css"><link rel="stylesheet" href="{prefix}assets/syntax.css">
<link rel="stylesheet" href="{prefix}assets/nerd-icons.css">
<script src="{prefix}assets/app.js" defer></script></head>
<body><a class="skip-link" href="#main">Перейти к содержимому</a>
<header class="topbar"><a class="brand" href="{prefix}"><span class="brand-mark" aria-hidden="true">λ</span>
<span>dibusure<span class="brand-slash"> / </span><strong>{esc(config['title'])}</strong></span></a>
<div class="top-actions"><a class="github-link" href="{repo}">GitHub ↗</a>
<div id="theme-switch" class="theme-switch" role="group" aria-label="Catppuccin: цветовая тема" hidden>
<button class="theme-choice" data-theme-choice="latte" type="button" aria-pressed="true" title="Catppuccin Latte — светлая тема">
<svg class="theme-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" aria-hidden="true"><circle cx="12" cy="12" r="4"/><path d="M12 2v2m0 16v2M2 12h2m16 0h2M5 5l1.5 1.5m11 11L19 19M5 19l1.5-1.5m11-11L19 5"/></svg>Latte</button>
<button class="theme-choice" data-theme-choice="mocha" type="button" aria-pressed="false" title="Catppuccin Mocha — тёмная тема">
<svg class="theme-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" aria-hidden="true"><path d="M20.5 13.5A8.5 8.5 0 0 1 10.5 3a8.5 8.5 0 1 0 10 10.5Z"/></svg>Mocha</button></div></div></header>
<div class="workspace"><aside class="sidebar" aria-label="Навигация по файлам">
<div class="sidebar-title"><span>ИСХОДНИКИ</span><span class="count">{count:02d}</span></div>
<label class="search-box js-only" hidden><span class="sr-only">Поиск файлов</span>
<input id="search" type="search" placeholder="Найти файл…" autocomplete="off" spellcheck="false"><kbd>/</kbd></label>
<a class="overview-link" href="{prefix}">Все файлы <span>↗</span></a>
<a class="folders-overview-link" href="{prefix}folders/">Обзор папок <span aria-hidden="true">↗</span></a>
<nav class="file-tree" aria-label="Дерево файлов">{tree_html(files, prefix, active, folders, active_folder)}</nav>
<p class="no-results" id="tree-empty" role="status" hidden>Ничего не найдено.</p>
<div class="sidebar-note"><span class="status-dot"></span> Статическая коллекция<br><span>Без сервера. Без лишнего.</span></div>
</aside><main id="main" class="main-content">{body}
<footer class="footer"><span>{esc(config['repository'])}</span><span>Pygments · {version}</span></footer>
</main></div><div id="toast" class="toast" role="status" hidden></div></body></html>'''


def homepage(config: dict, files: list[dict], folders: list[str] | None = None) -> str:
    roots = [f for f in (folders or []) if "/" not in f]
    tiles = "".join(f'<a class="home-folder-link" href="{folder_url(name)}">'
                    f'{folder_icon("./")}<span class="folder-name">{esc(name)}</span>'
                    f'<span class="home-folder-arrow" aria-hidden="true">↗</span></a>'
                    for name in roots)
    root_section = ('<section aria-label="Папки"><div class="section-heading">'
                    f'<h2>Папки <span>{len(roots)}</span></h2>'
                    '<a class="source-link" href="folders/">Открыть файловый менеджер ↗</a></div>'
                    f'<div class="home-folder-grid">{tiles}</div></section>') if roots else (
                    '<p class="browse-root-link"><a href="folders/">Открыть папку code/ ↗</a></p>')
    languages = sorted({f["language"] for f in files})
    options = ''.join(f'<option value="{esc(lang, quote=True)}">{esc(lang)}</option>' for lang in languages)
    rows = []
    for file in files:
        folder = config["source"].strip("/") + "/" + (file["folder"] + "/" if file["folder"] != "." else "")
        rows.append(f'<a class="file-row" data-search="{esc(file["path"] + " " + file["language"], quote=True)}" '
                    f'data-language="{esc(file["language"], quote=True)}" href="{file["url"]}">'
                    f'<span class="file-badge">{file_icon(file, "./")}</span><span class="file-label"><strong>{esc(file["name"])}</strong>'
                    f'<small>{esc(folder)}</small></span><span class="language-label">{esc(file["language"])}</span>'
                    f'<span class="row-lines">{file["lines"]} стр.</span><span class="row-arrow" aria-hidden="true">↗</span></a>')
    empty = '<div class="empty-state"><h2>Здесь начинается коллекция.</h2><p>Добавь первый исходник в папку <code>code/</code> и сделай push.</p></div>' if not files else ""
    return f'''<section class="hero"><div class="eyebrow"><span class="status-dot"></span> ЛИЧНАЯ КОЛЛЕКЦИЯ КОДА</div>
<h1>{esc(config['title'])}<span class="accent">.</span></h1><p class="hero-subtitle">{esc(config['subtitle'])}</p>
<div class="stats"><span><strong>{len(files):02d}</strong> {plural(len(files), "файл", "файла", "файлов")}</span><span><strong>{len(languages):02d}</strong> {plural(len(languages), "язык / формат", "языка / формата", "языков / форматов")}</span>
<span><strong>{sum(f['lines'] for f in files)}</strong> {plural(sum(f["lines"] for f in files), "строка", "строки", "строк")}</span></div></section>
{root_section}
<section aria-label="Коллекция файлов"><div class="section-heading"><h2>Все файлы <span id="result-count">{len(files)}</span></h2>
<label class="language-filter js-only" hidden><span class="sr-only">Фильтр по языку</span><select id="language"><option value="">Все языки</option>{options}</select></label></div>
<div class="file-list">{''.join(rows)}{empty}</div><p id="list-empty" class="empty-state" role="status" hidden>Ничего не найдено. Попробуй другой запрос.</p></section>
<div class="usage-note"><span class="note-symbol" aria-hidden="true">↳</span><p>Обычные файлы. Красивое чтение.<br>
<span>Добавляй исходники в <code>code/</code> — сайт обновится после публикации коммита.</span></p></div>'''


def folderpage(config: dict, files: list[dict], folders: list[str], folder: str, prefix: str, rev: str) -> str:
    """Static folder page with direct children only, like a file manager."""
    children = [f for f in folders if f.rpartition("/")[0] == folder]
    direct_files = [f for f in files if f["folder"] == (folder or ".")]
    rows = []
    for child in children:
        name = child.rsplit("/", 1)[-1]
        rows.append(f'<a class="file-row folder-row" href="{prefix}{folder_url(child)}" '
                    f'data-search="{esc(child, quote=True)}" data-language="folder">'
                    f'<span class="file-badge">{folder_icon(prefix)}</span><span class="file-label">'
                    f'<strong>{esc(name)}</strong><small>Папка</small></span>'
                    f'<span class="language-label">Каталог</span><span class="row-lines"></span>'
                    '<span class="row-arrow" aria-hidden="true">↗</span></a>')
    for file in direct_files:
        rows.append(f'<a class="file-row" href="{prefix}{file["url"]}" '
                    f'data-search="{esc(file["path"] + " " + file["language"], quote=True)}" '
                    f'data-language="{esc(file["language"], quote=True)}">'
                    f'<span class="file-badge">{file_icon(file, prefix)}</span><span class="file-label">'
                    f'<strong>{esc(file["name"])}</strong><small>{esc(file["language"])}</small></span>'
                    f'<span class="language-label">{esc(file["language"])}</span>'
                    f'<span class="row-lines">{file["lines"]} стр.</span>'
                    '<span class="row-arrow" aria-hidden="true">↗</span></a>')
    ref = rev or config["branch"]
    source_path = config["source"].strip("/") + ("/" + folder if folder else "")
    github = ("https://github.com/" + config["repository"] + "/tree/" +
              quote(ref, safe="") + "/" + quote(source_path, safe="/"))
    name = folder.rsplit("/", 1)[-1] if folder else config["source"].strip("/")
    empty = '<p class="directory-empty">В этой папке пока нет публикуемых файлов и подпапок.</p>' if not rows else ""
    return (f'{breadcrumbs(folder, prefix)}'
            f'<section class="directory-heading"><div><div class="eyebrow">ПАПКА · {esc(source_path)}</div>'
            f'<h1>{esc(name)}<span class="accent">/</span></h1>'
            f'<p>{len(children)} {plural(len(children), "папка", "папки", "папок")} · '
            f'{len(direct_files)} {plural(len(direct_files), "файл", "файла", "файлов")}</p></div>'
            f'<div class="directory-actions"><button id="copy-folder-link" '
            f'class="toolbar-button copy-folder-link js-only" type="button" hidden>'
            f'Скопировать ссылку</button>'
            f'<a class="source-link" href="{github}">Открыть на GitHub ↗</a></div></section>'
            f'<section aria-label="Содержимое папки">'
            f'<div class="section-heading"><h2>Содержимое <span id="result-count">{len(rows)}</span></h2></div>'
            f'<div class="file-list directory-list">{"".join(rows)}{empty}</div>'
            '<p id="list-empty" class="empty-state" role="status" hidden>'
            'В этой папке ничего не найдено.</p></section>')


def filepage(config: dict, file: dict, prefix: str, rev: str) -> str:
    ref = rev or config["branch"]
    path = config["source"].strip("/") + "/" + file["path"]
    github = "https://github.com/" + config["repository"] + "/blob/" + quote(ref, safe="") + "/" + quote(path, safe="/")
    size = f'{file["size"] / 1024:.1f} КБ' if file["size"] >= 1024 else f'{file["size"]} Б'
    return f'''{breadcrumbs(file["path"], prefix)}
<section class="file-heading"><div><div class="eyebrow">{esc(file['language'])}</div><h1>{esc(file['name'])}</h1>
<p>{file['lines']} {plural(file['lines'], 'строка', 'строки', 'строк')} <span>·</span> {size} <span>·</span> UTF-8</p></div><a class="source-link" href="{github}">Открыть на GitHub ↗</a></section>
<section class="code-panel" aria-label="Просмотр исходника"><div class="code-toolbar"><span class="code-tab">{file_icon(file, prefix)}{esc(file['name'])}</span>
<div class="code-actions"><button id="wrap-toggle" class="toolbar-button js-only" type="button" aria-pressed="false" hidden>Перенос</button>
<button id="copy-code" class="toolbar-button js-only" type="button" hidden>Копировать</button>
<a class="toolbar-button" href="{prefix}{file['raw_url']}" download="{esc(file['name'], quote=True)}">Скачать</a></div></div>
<div class="code-scroll">{code_html(file['text'], file['lexer'])}</div></section>
<p class="code-hint">Номер строки — прямая ссылка на неё. Код показан как текст и не выполняется.</p>
<textarea id="raw-source" hidden>\n{esc(file['text'])}</textarea>'''


def build(root: Path = ROOT) -> tuple[int, Path]:
    config = tomllib.loads((root / "site.toml").read_text(encoding="utf-8"))
    source = root / config["source"]
    if not source.resolve().is_relative_to(root.resolve()) or source.resolve() == root.resolve():
        raise ValueError("source должен быть отдельной папкой внутри репозитория.")
    # Collect before deleting dist; source and output must never overlap.
    output = root / "dist"
    if source.resolve().is_relative_to(output.resolve()) or output.resolve().is_relative_to(source.resolve()):
        raise ValueError("Папки исходников и результата сборки не должны пересекаться.")
    if output.is_symlink():
        raise ValueError("dist не должен быть символьной ссылкой.")
    files = collect(source, config)
    folders = collect_folders(source, config)
    if output.exists():
        shutil.rmtree(output)
    (output / "raw").mkdir(parents=True)
    shutil.copytree(root / "site" / "assets", output / "assets")
    # syntax.css is copied with assets and uses shared Catppuccin CSS variables.
    rev = revision(root)
    (output / "index.html").write_text(layout(config, files, homepage(config, files, folders), "./", config["title"], rev, folders=folders), encoding="utf-8")
    for file in files:
        page = output / "files" / file["path"] / "index.html"
        page.parent.mkdir(parents=True, exist_ok=True)
        prefix = "../" * (len(Path(file["path"]).parts) + 1)
        page.write_text(layout(config, files, filepage(config, file, prefix, rev), prefix,
                               file["name"], rev, file["path"], folders=folders), encoding="utf-8")
        (output / file["raw_url"]).write_bytes(file["raw"])
    for folder in ["", *folders]:
        page = output / "folders" / folder / "index.html"
        page.parent.mkdir(parents=True, exist_ok=True)
        prefix = "../" * (len(Path(folder).parts) + 1)
        page.write_text(layout(config, files, folderpage(config, files, folders, folder, prefix, rev),
                               prefix, folder.rsplit("/", 1)[-1] if folder else config["source"],
                               rev, folders=folders, active_folder=folder), encoding="utf-8")
    (output / ".nojekyll").write_text("", encoding="utf-8")
    (output / "_headers").write_text(f"/*\n  X-Content-Type-Options: nosniff\n  Referrer-Policy: no-referrer\n  X-Frame-Options: DENY\n  Content-Security-Policy: {CSP}; frame-ancestors 'none'\n", encoding="utf-8")
    print(f"Готово: файлов — {len(files)} → {output}")
    return len(files), output


FONT_REVISION = "9c6fe7fbf1f00b90eb2ee09a98739c9e0853ac6e"  # Iosevka 34.9.1
FONT_BASE_URL = f"https://raw.githubusercontent.com/iosevka-webfonts/iosevka/{FONT_REVISION}"
FONT_LICENSE_URL = "https://raw.githubusercontent.com/be5invis/Iosevka/v34.9.1/LICENSE.md"
FONT_FILES = ("Iosevka-Regular.woff2", "Iosevka-Medium.woff2", "Iosevka-SemiBold.woff2",
              "Iosevka-Bold.woff2", "Iosevka-Italic.woff2", "Iosevka-BoldItalic.woff2")

NERD_FONT_VERSION = "v3.4.0"
NERD_FONT_FILE = "SymbolsNerdFont-Regular.ttf"
NERD_FONT_BLOB_SHA = "38c24fbbac296e834655a2888017d027684ff6d8"
NERD_FONT_BASE_URL = f"https://raw.githubusercontent.com/ryanoasis/nerd-fonts/{NERD_FONT_VERSION}/patched-fonts/NerdFontsSymbolsOnly"
NERD_FONT_LICENSE = "LICENSE-Nerd-Fonts.txt"

# Rubik variable fonts, including Cyrillic, from immutable Google Fonts sources.
RUBIK_REVISION = "8b0a1d0f5983c89bc2b93f1b5fb55f9e252744b5"
RUBIK_FONT_BASE_URL = f"https://raw.githubusercontent.com/google/fonts/{RUBIK_REVISION}/ofl/rubik"
RUBIK_FONT_FILES = {
    "Rubik-Variable.ttf": ("Rubik%5Bwght%5D.ttf", "a59aeb632df494345a542697c357f608875481b0"),
    "Rubik-Italic-Variable.ttf": ("Rubik-Italic%5Bwght%5D.ttf", "2d9fcc4cf00e21f231277467b50eb80a2779a356"),
}
RUBIK_FONT_LICENSE = "LICENSE-Rubik.txt"
RUBIK_LICENSE_BLOB_SHA = "03af63b533942ef3bb9919f81138fde8824d4554"


def download_fonts(output: Path) -> None:
    """Self-host pinned Iosevka, Rubik and Nerd Fonts with their licenses."""
    destination = output / "assets" / "fonts"
    destination.mkdir(parents=True, exist_ok=True)
    for name in (*FONT_FILES, "LICENSE", NERD_FONT_FILE, NERD_FONT_LICENSE, *RUBIK_FONT_FILES, RUBIK_FONT_LICENSE):
        if name in RUBIK_FONT_FILES:
            url = f"{RUBIK_FONT_BASE_URL}/{RUBIK_FONT_FILES[name][0]}"
        elif name == RUBIK_FONT_LICENSE:
            url = f"{RUBIK_FONT_BASE_URL}/OFL.txt"
        elif name == NERD_FONT_FILE:
            url = f"{NERD_FONT_BASE_URL}/{name}"
        elif name == NERD_FONT_LICENSE:
            url = f"{NERD_FONT_BASE_URL}/LICENSE"
        else:
            url = FONT_LICENSE_URL if name == "LICENSE" else f"{FONT_BASE_URL}/WOFF2/{name}"
        for attempt in range(3):
            try:
                with urlopen(url, timeout=45) as response:
                    data = response.read(4 * 1024 * 1024 + 1)
                if len(data) > 4 * 1024 * 1024 or not data:
                    raise ValueError(f"Invalid font asset size: {name}")
                if name.endswith(".woff2") and not data.startswith(b"wOF2"):
                    raise ValueError(f"Invalid WOFF2 font: {name}")
                if name == NERD_FONT_FILE:
                    blob_sha = hashlib.sha1(b"blob " + str(len(data)).encode() + b"\0" + data).hexdigest()
                    if not data.startswith(b"\x00\x01\x00\x00") or blob_sha != NERD_FONT_BLOB_SHA:
                        raise ValueError("Nerd Fonts asset does not match the pinned official font")
                if name in RUBIK_FONT_FILES or name == RUBIK_FONT_LICENSE:
                    expected_sha = RUBIK_FONT_FILES[name][1] if name in RUBIK_FONT_FILES else RUBIK_LICENSE_BLOB_SHA
                    blob_sha = hashlib.sha1(b"blob " + str(len(data)).encode() + b"\0" + data).hexdigest()
                    if (name in RUBIK_FONT_FILES and not data.startswith(b"\x00\x01\x00\x00")) or blob_sha != expected_sha:
                        raise ValueError(f"Rubik asset does not match the pinned official source: {name}")
                (destination / name).write_bytes(data)
                break
            except (OSError, ValueError):
                if attempt == 2:
                    raise
                time.sleep(attempt + 1)
    print("Iosevka 34.9.1 + Rubik variable + Nerd Fonts 3.4.0: self-hosted fonts and licenses included")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--skip-fonts", action="store_true",
                        help="Offline preview only: skip downloading webfonts (uses locally installed fonts or system fallbacks).")
    args = parser.parse_args()
    _, output = build()
    if not args.skip_fonts:
        download_fonts(output)
