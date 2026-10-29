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


def tree_html(files: list[dict], prefix: str, active: str = "") -> str:
    tree: dict = {"dirs": {}, "files": []}
    for file in files:
        node = tree
        for part in file["path"].split("/")[:-1]:
            node = node["dirs"].setdefault(part, {"dirs": {}, "files": []})
        node["files"].append(file)

    def render(node: dict, trail: str = "") -> str:
        result = []
        for name, child in sorted(node["dirs"].items(), key=lambda item: item[0].casefold()):
            full = trail + name + "/"
            opened = " open" if not trail or active.startswith(full) else ""
            result.append(f'<details class="tree-folder"{opened}><summary>{esc(name)}</summary>'
                          f'<div class="tree-children">{render(child, full)}</div></details>')
        for file in node["files"]:
            selected = ' aria-current="page"' if file["path"] == active else ""
            search = esc(file["path"] + " " + file["language"], quote=True)
            result.append(f'<a class="tree-file" data-search="{search}" href="{prefix}{file["url"]}"{selected}>'
                          f'<span class="file-dot" aria-hidden="true"></span>{esc(file["name"])}</a>')
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


def layout(config: dict, files: list[dict], body: str, prefix: str, title: str, rev: str, active: str = "") -> str:
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
<link rel="stylesheet" href="{prefix}assets/style.css"><link rel="stylesheet" href="{prefix}assets/syntax.css">
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
<nav class="file-tree" aria-label="Дерево файлов">{tree_html(files, prefix, active)}</nav>
<p class="no-results" id="tree-empty" role="status" hidden>Ничего не найдено.</p>
<div class="sidebar-note"><span class="status-dot"></span> Статическая коллекция<br><span>Без сервера. Без лишнего.</span></div>
</aside><main id="main" class="main-content">{body}
<footer class="footer"><span>{esc(config['repository'])}</span><span>Pygments · {version}</span></footer>
</main></div><div id="toast" class="toast" role="status" hidden></div></body></html>'''


def homepage(config: dict, files: list[dict]) -> str:
    languages = sorted({f["language"] for f in files})
    options = ''.join(f'<option value="{esc(lang, quote=True)}">{esc(lang)}</option>' for lang in languages)
    rows = []
    for file in files:
        badge = Path(file["name"]).suffix.lstrip(".")[:5] or "txt"
        folder = config["source"].strip("/") + "/" + (file["folder"] + "/" if file["folder"] != "." else "")
        rows.append(f'<a class="file-row" data-search="{esc(file["path"] + " " + file["language"], quote=True)}" '
                    f'data-language="{esc(file["language"], quote=True)}" href="{file["url"]}">'
                    f'<span class="file-badge">{esc(badge)}</span><span class="file-label"><strong>{esc(file["name"])}</strong>'
                    f'<small>{esc(folder)}</small></span><span class="language-label">{esc(file["language"])}</span>'
                    f'<span class="row-lines">{file["lines"]} стр.</span><span class="row-arrow" aria-hidden="true">↗</span></a>')
    empty = '<div class="empty-state"><h2>Здесь начинается коллекция.</h2><p>Добавь первый исходник в папку <code>code/</code> и сделай push.</p></div>' if not files else ""
    return f'''<section class="hero"><div class="eyebrow"><span class="status-dot"></span> ЛИЧНАЯ КОЛЛЕКЦИЯ КОДА</div>
<h1>{esc(config['title'])}<span class="accent">.</span></h1><p class="hero-subtitle">{esc(config['subtitle'])}</p>
<div class="stats"><span><strong>{len(files):02d}</strong> {plural(len(files), "файл", "файла", "файлов")}</span><span><strong>{len(languages):02d}</strong> {plural(len(languages), "язык / формат", "языка / формата", "языков / форматов")}</span>
<span><strong>{sum(f['lines'] for f in files)}</strong> {plural(sum(f["lines"] for f in files), "строка", "строки", "строк")}</span></div></section>
<section aria-label="Коллекция файлов"><div class="section-heading"><h2>Все файлы <span id="result-count">{len(files)}</span></h2>
<label class="language-filter js-only" hidden><span class="sr-only">Фильтр по языку</span><select id="language"><option value="">Все языки</option>{options}</select></label></div>
<div class="file-list">{''.join(rows)}{empty}</div><p id="list-empty" class="empty-state" role="status" hidden>Ничего не найдено. Попробуй другой запрос.</p></section>
<div class="usage-note"><span class="note-symbol" aria-hidden="true">↳</span><p>Обычные файлы. Красивое чтение.<br>
<span>Добавляй исходники в <code>code/</code> — сайт обновится после публикации коммита.</span></p></div>'''


def filepage(config: dict, file: dict, prefix: str, rev: str) -> str:
    ref = rev or config["branch"]
    path = config["source"].strip("/") + "/" + file["path"]
    github = "https://github.com/" + config["repository"] + "/blob/" + quote(ref, safe="") + "/" + quote(path, safe="/")
    size = f'{file["size"] / 1024:.1f} КБ' if file["size"] >= 1024 else f'{file["size"]} Б'
    return f'''<div class="breadcrumbs"><a href="{prefix}">Коллекция</a><span>/</span><span>{esc(file['path'])}</span></div>
<section class="file-heading"><div><div class="eyebrow">{esc(file['language'])}</div><h1>{esc(file['name'])}</h1>
<p>{file['lines']} {plural(file['lines'], 'строка', 'строки', 'строк')} <span>·</span> {size} <span>·</span> UTF-8</p></div><a class="source-link" href="{github}">Открыть на GitHub ↗</a></section>
<section class="code-panel" aria-label="Просмотр исходника"><div class="code-toolbar"><span class="code-tab">{esc(file['name'])}</span>
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
    if output.exists():
        shutil.rmtree(output)
    (output / "raw").mkdir(parents=True)
    shutil.copytree(root / "site" / "assets", output / "assets")
    # syntax.css is copied with assets and uses shared Catppuccin CSS variables.
    rev = revision(root)
    (output / "index.html").write_text(layout(config, files, homepage(config, files), "./", config["title"], rev), encoding="utf-8")
    for file in files:
        page = output / "files" / file["path"] / "index.html"
        page.parent.mkdir(parents=True, exist_ok=True)
        prefix = "../" * (len(Path(file["path"]).parts) + 1)
        page.write_text(layout(config, files, filepage(config, file, prefix, rev), prefix,
                               file["name"], rev, file["path"]), encoding="utf-8")
        (output / file["raw_url"]).write_bytes(file["raw"])
    (output / ".nojekyll").write_text("", encoding="utf-8")
    (output / "_headers").write_text(f"/*\n  X-Content-Type-Options: nosniff\n  Referrer-Policy: no-referrer\n  X-Frame-Options: DENY\n  Content-Security-Policy: {CSP}; frame-ancestors 'none'\n", encoding="utf-8")
    print(f"Готово: файлов — {len(files)} → {output}")
    return len(files), output


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.parse_args()
    build()
