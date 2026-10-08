---
name: xyo-pixel32
description: >-
  How to use the xyo-pixel32 C++ library (namespace XYO::Pixel32), the RGBA
  image layer of the XYO C++ stack on top of xyo-system and
  xyo-cryptography, with libpng / zlib: the Pixel type (uint32_t, R in the
  low byte, straight alpha) and the XYO_PIXEL32_PIXEL / _R / _G / _B / _A /
  _RGB / _CHANGE_* macros; Image (width, height, pixelMap, pixel[y][x],
  top-down); the Process:: functions create, getPixel / setPixel /
  getPixelX, clear, resize, scaleUp / scaleDown, scaleUpBicubic /
  scaleUpBilinear / scaleUpNearestNeighbor, scaleDownX2 / X2OnX / X2OnY,
  cut, wrap, wrapBox, copy, blend, alphaBlending, drawRectangle /
  drawFilledRectangle, kernel3X3 with Kernel3X3 (blur, gaussian, sharpen,
  edgeDetection, gradientDetection, filter8X1), average, colorRescale,
  noise / noise2Bit, backgroundAlpha / backgroundAlphaLevel; PNG pngLoad /
  pngSave, bitmap32LoadPNG / bitmap32SavePNG; the Bitmap class (BMP file in
  memory, 1 / 4 / 8 / 24 / 32 bits, palettes, bottom-up rows, load / save,
  newImage32Bits ...) and the conversions imageFromBitmap, toBitmap32,
  toBitmap24, alphaToBitmap1 / 8, bitmap32To24Alpha8 / To8Alpha1 /
  To4Alpha1; Windows icons IconItem, generateIcon, pngToIcon. Use when
  writing or reviewing code that includes <XYO/Pixel32.hpp>, depends on
  "xyo-pixel32" in fabricare.json, uses any of these names, or when working
  inside the xyo-pixel32 repository or code built on it
  (quantum-script--pixel32, png-to-icon).
---

# xyo-pixel32

RGBA image layer of the XYO C++ libraries, on top of `xyo-system` and
`xyo-cryptography` (see the `xyo-system`, `xyo-managed-memory` and
`xyo-data-structures` skills; their rules all apply — `TPointer`,
`Object`, `IApplication`). Purpose: **simple 32-bit RGBA images in memory**
with correct alpha handling, PNG / BMP / ICO files, resizing, compositing,
3×3 filters — what the XYO tools need to make icons and process images,
not a general image library.

Full documentation: `docs/` in the xyo-pixel32 repository
(`X:\Storage\XYO\Gitea\CPP\xyo-pixel32\docs` on this machine): README,
getting-started, **images**, **processing**, **files**, reference. Read
the matching page when you need more than this summary. When in doubt read
`source/XYO/Pixel32/Process.hpp` and the one-function-per-file sources in
`source/XYO/Pixel32/Process/`; `test/test.02.cpp` shows real usage of
every function.

## Pick a tool

| Need | Use |
|------|-----|
| New image (transparent black) | `TPointer<Image> img = Process::create(w, h);` |
| Build / split a pixel | `XYO_PIXEL32_PIXEL(r, g, b, a)`, `XYO_PIXEL32_R(p)` ... `_A(p)` |
| Pixel in a loop (in range) | `img->pixel[y][x]` (top-down, no check) |
| Pixel maybe outside | `Process::getPixel` (0 outside) / `setPixel` (ignored) / `getPixelX` (clamped) |
| Fill | `Process::clear(img, pixel)` |
| Load / save PNG | `Process::pngLoad(file)` / `Process::pngSave(img, file)` |
| Resize to any size | `Process::resize(img, w, h)` |
| Pixel art upscale | `Process::scaleUpNearestNeighbor(img, w, h)` |
| Crop / duplicate | `Process::cut(img, x, y, w, h)` / `cut(img, 0, 0, img->width, img->height)` |
| Paste replacing | `Process::copy(dst, src, dx, dy, sx, sy, w, h)` |
| Paste with alpha | `Process::blend(dst, src, dx, dy, sx, sy, w, h)` |
| One blended pixel | `img->pixel[y][x] = Process::alphaBlending(over, img->pixel[y][x])` |
| Rectangle | `Process::drawRectangle` / `drawFilledRectangle` (blended) |
| Blur / sharpen / edges | `Process::kernel3X3(img, Kernel3X3::gaussian)` |
| Tile scroll / tiling border | `Process::wrap(img, dx, dy)` / `wrapBox(img, dx, dy)` |
| Auto levels | `Process::colorRescale(img)` |
| Mix two images | `Process::average(a, b, 1, 1, 2)` |
| Noise texture | `RandomMT rnd; rnd.seed(n); Process::noise(img, rnd);` |
| BMP in / out | `Bitmap::load(file)` + `Process::imageFromBitmap(bmp)`; `Process::toBitmap32(img)->save(file)` |
| Icon from a PNG | `Process::pngToIcon("in.png", "out.ico", 128, false, 0)` |
| Icon with custom sizes | per size: `item->bmp = Process::toBitmap32(img); item->mask = Process::alphaToBitmap1(img, 128);`, push to a `TDoubleEndedQueue<TPointer<IconItem>>` → `Process::generateIcon` |

## Hard rules

1. **Include and namespaces**: `#include <XYO/Pixel32.hpp>`,
   `using namespace XYO::Pixel32;` (it re-exports `XYO::System` and
   `XYO::Cryptography`). Call processing as `Process::name(...)`; do not
   `using namespace Process` (`copy`, `clear` clash). Metadata in full:
   `XYO::Pixel32::Version::version()`.
2. **Check every result.** Creating functions return `nullptr` / `false`
   on bad sizes, bad files, allocation failure; nothing throws on bad
   input. Processing functions **do not check their `Image *` / `Bitmap *`
   arguments for null** — check a result before passing it on.
3. **Ownership**: results are `TPointer<Image>` / `TPointer<Bitmap>`;
   parameters are raw `Image *` / `Bitmap *` and a `TPointer` converts
   implicitly. Never make an image with `TPointer<Image> i; i.newMemory();`
   (0×0, null pointers) or a bitmap with `newMemory()` (no data) — use
   `Process::create` / `Bitmap::newImage*Bits` / loaders. `Image`,
   `Bitmap`, `Kernel3X3`, `IconItem` are not copyable.
4. **Pixel layout**: `uint32_t`, `R | G << 8 | B << 16 | A << 24` (bytes
   R, G, B, A on little endian); **straight** alpha, `255` opaque. Do not
   swap to ARGB / BGRA by habit. `XYO_PIXEL32_CHANGE_*` assign to their
   first argument (pass an lvalue).
5. **Image is top-down**, `pixel[y][x]`, `y = 0` top, rows contiguous in
   `pixelMap` (no padding). Fields are public but treat them as read only
   (the destructor `delete[]`s both pointers).
6. **New image vs in place**: `resize`, `scale*`, `cut`, `wrap*`,
   `kernel3X3` return a new image and never change the input; `clear`,
   `copy`, `blend`, `draw*`, `average`, `colorRescale`, `noise*`,
   `backgroundAlpha*` modify their first argument.
7. **Size rules**: `scaleUp*` need `nx >= width && ny >= height` (else
   `nullptr`); `scaleDownX2*` drop an odd last row / column and fail on a
   dimension of 1; `resize` takes any size `> 0` (same size = exact copy).
   Prefer `resize`. Bicubic / bilinear map corner to corner.
8. **Alpha math**: scaling and positive-sum kernels weight colors by alpha
   (no dark fringes); a result pixel with alpha 0 gets color 0. `blend` /
   `draw*` / `alphaBlending` are "over"; `copy` / `clear` / `setPixel`
   replace including alpha. `blend` is not safe for overlapping areas of
   the same image; `copy` is.
9. **Rectangles** are `x, y, width, height` (`[x, x + w)`), clipped on
   both images; partly or fully outside is fine.
10. **Kernel3X3**: positive matrix sum → alpha weighted average, new alpha
    = `normalA · Σ(v·a) / normalB` (make `normalA / normalB = 1 / Σv`);
    zero / negative sum → `normalA · Σ(v·c) / normalB` per channel, center
    alpha kept, negatives clamp to 0. Edges repeat. Do not modify the
    static predefined kernels (shared; `scaleUp` uses `filter8X1`); copy
    with `k.copy(Kernel3X3::sharpen)`.
11. **Bitmap is bottom-up**: in `get/setPixel*` `y = 0` is the **bottom**
    row; only `getRow32Bits(y, scanLine)` counts from the top. Pixel
    methods have no bounds or depth checks (use the ones for
    `getPixelWidth()`; `getPixel32s` / `setPixel32s` are checked).
    `BitmapRGBA` is `{B, G, R, A}`. `newImage8/4/1Bit(s)` start with an
    all-black palette: `setPaletteIndex` first. `convertTo32Bits` returns
    the same object when already 32 bits.
12. **Bitmap::load** accepts 1/4/8/24/32-bit uncompressed and 32-bit
    standard bit fields, top-down or bottom-up, headers 40..124; RLE /
    16-bit / odd masks → `nullptr`. 32-bit BMPs often have alpha 0 meaning
    "unused": `bmp->setAlpha32(255)` before `imageFromBitmap` or the image
    is fully transparent. Palette / 24-bit pixels convert as opaque.
13. **PNG**: `pngLoad` takes any PNG (gray, palette, tRNS, 16-bit,
    interlaced) to 8-bit RGBA; `pngSave` always writes RGBA, no options.
    `bitmap32SavePNG` only for 32-bit bitmaps.
14. **Icons**: each `IconItem` = color `bmp` (1/4/8/24/32 bits, ≤ 256×256)
    + 1-bit `mask` of the same size where `1` = transparent
    (`alphaToBitmap1(img, level)`: alpha `< level`). `generateIcon` writes
    in push order. `pngToIcon(file, ...)` makes 16/24/32/48 squares (aspect
    not kept); the list variant uses each PNG at its own size.
    `level` 128 is the usual threshold; pass `false, 0` for
    `useBackgroundAlpha, background` unless targeting a known background.
15. **Threads**: one thread per image / bitmap; separate images on
    separate threads are fine.

## Recipes

Load, thumbnail, save:

```cpp
TPointer<Image> image = Process::pngLoad("photo.png");
if (!image) {
	return false;
};
long int height = 128 * image->height / image->width;   // keep the aspect ratio
if (height < 1) {
	height = 1;
};
TPointer<Image> thumb = Process::resize(image, 128, height);
return thumb && Process::pngSave(thumb, "thumb.png");
```

Watermark (blend with clipping, bottom right):

```cpp
Process::blend(photo, logo, photo->width - logo->width - 8, photo->height - logo->height - 8,
               0, 0, logo->width, logo->height);
```

Per-pixel edit (grayscale, keep alpha):

```cpp
for (long int y = 0; y < img->height; ++y) {
	Pixel *row = img->pixel[y];
	for (long int x = 0; x < img->width; ++x) {
		uint32_t g = (XYO_PIXEL32_R(row[x]) * 77 + XYO_PIXEL32_G(row[x]) * 150 + XYO_PIXEL32_B(row[x]) * 29) >> 8;
		XYO_PIXEL32_CHANGE_RGB(row[x], g, g, g);
	};
};
```

Seamless filter on a tiling texture:

```cpp
TPointer<Image> box = Process::wrapBox(tex, 1, 1);
TPointer<Image> soft = box ? Process::kernel3X3(box, Kernel3X3::gaussian) : nullptr;
TPointer<Image> out = soft ? Process::cut(soft, 1, 1, tex->width, tex->height) : nullptr;
```

Icon with chosen sizes:

```cpp
TDoubleEndedQueue<TPointer<IconItem>> list;
static const long int size[] = {16, 32, 48, 256};
for (int k = 0; k < 4; ++k) {
	TPointer<Image> img = Process::resize(src, size[k], size[k]);
	if (!img) {
		return false;
	};
	TPointer<IconItem> item;
	item.newMemory();
	item->bmp = Process::toBitmap32(img);
	item->mask = Process::alphaToBitmap1(img, 128);
	if (!item->bmp || !item->mask) {
		return false;
	};
	list.push(item);
};
return Process::generateIcon(list, "app.ico");
```

## Build and dependency

fabricare project, `make: dll-or-lib`; dependencies `xyo-system`,
`xyo-cryptography`, plus `libpng` / `libz` (Windows: `vendor-libpng`,
`vendor-zlib` from the SDK; Linux: system libraries). Consumers add
`"xyo-pixel32"` to `dependency` in `fabricare.json`. Tests: `test/test.01`
(PNG / BMP round trip of the sample images), `test/test.02` (regressions,
`test.02 <group>` runs one group: create, macro, copy, blend, cut,
drawRectangle, wrap, scale, kernel, color, bitmapPalette, bitmapFile, png,
icon). See the `fabricare` skill for build commands.

When changing the library: one `Process::` function per file in
`source/XYO/Pixel32/Process/`, declared in `Process.hpp` with
`XYO_PIXEL32_EXPORT`; keep the clipping (`clipSpan` / `clipSpan2`),
the `nullptr` returns and the alpha weighted math; add a check to
`test/test.02.cpp`; update `docs/`.
