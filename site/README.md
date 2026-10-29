# Gallery interface

`build.py` reads the source directory from `site.toml`, highlights source files
without executing them, and writes the static website to `dist/`.

## File explorer

Every folder starts collapsed, including folders containing the current file.
The chevron expands or collapses a folder independently of navigation.

A folder with a direct child named `Readme.md` links its name and folder icon to
that file's page. Matching is case-insensitive: `README.md` and `readme.md` work
too. A README in a nested subfolder is not used for its parent. A folder without
a README toggles when its name is clicked. Native `details` and `summary`
elements preserve keyboard access and navigation without JavaScript.

Search temporarily expands matching branches. Clearing the query restores the
expansion state from before searching. Expansion is not persisted between pages.

## Typography and icons

All interface text and source code use Iosevka. `assets/fonts.css` declares the
regular, medium, semibold, bold, italic and bold-italic faces. The CLI build
downloads Iosevka 34.9.1 from a pinned revision of `iosevka-webfonts/iosevka`
and its SIL Open Font License from the upstream `be5invis/Iosevka` v34.9.1
release into `dist/assets/fonts/`. No font files are committed,
and visitors load fonts from the same origin as the website, not an external CDN.
A failed font download fails the deployment instead of silently publishing an
incomplete build. Local Iosevka or a generic monospace font is the loading fallback.

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
That preview uses locally installed Iosevka or a monospace fallback and does not
include the icon font. Use a full build to inspect the Nerd Fonts icons.
Normal GitHub Pages and Cloudflare Pages builds should not use this option.

The bundled demonstration files under `code/examples/` have been removed.
The generator still accepts arbitrary folder names, including `examples`, in
collections that intentionally contain their own examples.
