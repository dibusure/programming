# Gallery interface

`build.py` reads the source directory from `site.toml`, highlights source files
without executing them, and writes the static website to `dist/`.

## File explorer

Every folder starts collapsed, including folders containing the current file.
The chevron expands or collapses a folder independently of navigation.

A folder with a direct child named `Readme.md` links its name and folder icon to
that file's page. Matching is case-insensitive: `README.md` and `readme.md` work
too. A README in a nested subfolder is not used for its parent. A folder without a README opens its directory page when its name is clicked.
Every folder also has a separate link icon pointing to the directory page,
so README navigation and folder browsing are independent. The chevron controls
expansion. Native `details` and `summary` preserve keyboard access.

Each visible directory, including an empty one, has a direct static URL at
`/folders/<path>/`. `/folders/` is the root `code/` directory.
Directory pages list immediate subfolders (first) and files, offer clickable
breadcrumbs, a link to the same folder on GitHub, and a copy-URL button.
File-page breadcrumbs also link to parent directory pages. All names are
escaped for safe HTML and valid URLs, supporting Cyrillic and punctuation.
Hidden, excluded, and symlinked directories never get pages.
Folder pages work without JavaScript; the copy button needs JS and HTTPS.

Search temporarily expands matching branches. Clearing the query restores the
expansion state from before searching. Expansion is not persisted between pages.

## Typography and icons

**Rubik** is used for ordinary text, headings, UI labels, controls, and
descriptions. Its self-hosted variable regular and italic fonts include Cyrillic
and Latin. **Iosevka 34.9.1** stays in the code viewer, inline code, file and
directory names, paths, and technical monospace labels. Catppuccin Latte/Mocha
theme switching is unchanged.

`assets/fonts.css` defines both typefaces. The build downloads Rubik
from the pinned `google/fonts` revision, verifies the files (including the
SIL Open Font License) against their upstream Git blob SHA, and copies them into
`dist/assets/fonts/`. Iosevka also comes from its pinned source and includes
its license. Nothing is fetched from a third-party font CDN in the visitor's
browser; failed downloads and mismatches fail the build instead of publishing
a broken website.

File and folder icons use the official **Symbols Nerd Font 3.4.0**, not hand-drawn
SVG approximations. `assets/nerd-icons.css` declares the separate icon typeface;
Iosevka remains the text and code font. `ICON_EXTENSIONS` maps file extensions to
icon names and `NERD_GLYPHS` maps those names to upstream Unicode codepoints.
Language-aware fallbacks also cover extensionless scripts. Icons retain the
active Catppuccin colors and are hidden from assistive technology because the
adjacent filenames provide their accessible labels.

The build downloads `SymbolsNerdFont-Regular.ttf` and its license from
`ryanoasis/nerd-fonts` at `v3.4.0` into `dist/assets/fonts/`. The TTF is checked
against the pinned upstream Git blob hash before publication. Visitors do not
need any Nerd Font installed and make no third-party font requests. The old
`assets/icons.svg` file has been removed.

## Development

```sh
uv sync --locked
uv run --locked python -m unittest discover -s tests -v
node --test tests/theme.test.cjs
uv run --locked python site/build.py
uv run --locked python -m http.server 8000 --directory dist
```

For an offline layout preview only, add `--skip-fonts` to the build command.
That preview uses locally installed fonts or system fallbacks and does not
include the icon font. Use a full build to inspect the Nerd Fonts icons.
Normal GitHub Pages and Cloudflare Pages builds should not use this option.

The bundled demonstration files under `code/examples/` have been removed.
The generator still accepts arbitrary folder names, including `examples`, in
collections that intentionally contain their own examples.
