# XYO Pixel32

C++ library
- RGBA image processing for the XYO C++ libraries and applications.
- One image type: `Image`, 32-bit `Pixel` (R, G, B, A, straight alpha), `pixel[y][x]`.
- `Process::` functions: create, resize (bicubic, bilinear, nearest neighbor, box halving),
cut, wrap, copy, alpha blend, rectangles, 3x3 kernels (blur, sharpen, edges), color
rescale, average, noise — all with alpha weighted math and clipping.
- Files: PNG load / save (libpng), `Bitmap` (BMP 1 / 4 / 8 / 24 / 32 bits, palettes),
Windows icons (`generateIcon`, `pngToIcon`).

Built on `xyo-system` and `xyo-cryptography`; used by `quantum-script--pixel32`
and `png-to-icon`.

## Documentation

- [Overview](docs/README.md) - purpose and design
- [Getting started](docs/getting-started.md) - build, depend on it, first program, conventions
- [Images and pixels](docs/images.md) - `Pixel`, macros, `Image`, pixel access, alpha
- [Processing](docs/processing.md) - resize, cut, wrap, copy, blend, draw, kernels, color, noise
- [Files: PNG, BMP, ICO](docs/files.md) - `pngLoad` / `pngSave`, `Bitmap`, conversions, icons
- [API reference](docs/reference.md)

A Claude Code skill for this library is in
[.claude/skills/xyo-pixel32](.claude/skills/xyo-pixel32/SKILL.md).

## License

Copyright (c) 2016-2026 Grigore Stefan
Licensed under the [MIT](LICENSE) license.

PNG support uses [libpng](http://www.libpng.org/pub/png/libpng.html)
([libpng-2.0](LICENSES/libpng-2.0.txt)) and [zlib](https://zlib.net/)
([Zlib](LICENSES/Zlib.txt)).
