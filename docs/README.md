# XYO Pixel32 — Documentation

`xyo-pixel32` is the image layer of the XYO C++ library stack: a small
library for **32-bit RGBA images in memory**, with PNG, BMP and ICO files
on the way in and out. It sits on top of `xyo-system` (files, streams) and
`xyo-cryptography` (the `RandomMT` generator used for noise), and uses
`libpng` + `zlib` for PNG.

It is built for the jobs the XYO tools need — make application icons,
resize and compose images in build scripts, generate test pictures — and
keeps the image model simple enough to touch every pixel directly:

- **One image type, one pixel type.** `Image` is a width × height array of
  `Pixel` (`uint32_t`, red in the low byte, then green, blue, alpha:
  `R | G << 8 | B << 16 | A << 24`), stored row after row from the top.
  `image->pixel[y][x]` is a plain lvalue; `image->pixelMap` is the whole
  buffer. The `XYO_PIXEL32_*` macros build and take apart pixels.
- **Processing as free functions.** Everything that works on images is in
  the `Process::` namespace: create, get / set pixels, resize (bicubic,
  bilinear, nearest neighbor, box halving), cut, wrap, copy, alpha blend,
  draw rectangles, 3×3 convolution kernels, color stretch, average, noise.
  Functions that change the size **return a new image**; the input is
  never changed.
- **Alpha done right.** Pixels hold *straight* (not premultiplied) alpha.
  Every function that mixes pixels (scaling, kernels, blending) weights the
  colors by alpha, so transparent pixels never bleed black into edges.
- **Files.** `Process::pngLoad` / `pngSave` read any PNG (every color type,
  bit depth, palette, transparency chunk, interlacing) into RGBA and write
  RGBA PNG. `Bitmap` is a BMP file in memory (1, 4, 8, 24 and 32 bits,
  palettes) with `load` / `save`. `Process::generateIcon` and
  `Process::pngToIcon` write Windows `.ico` files.

```
quantum-script--pixel32, png-to-icon, applications ...
xyo-pixel32           <-- this library (+ libpng, zlib)
xyo-cryptography      (RandomMT, hashes)
xyo-system            (File, Shell, IApplication)
xyo-encoding          (String)
xyo-multithreading
xyo-data-structures   (TDoubleEndedQueue, TDynamicArray)
xyo-managed-memory    (Object, TPointer)
xyo-platform
```

## Why it exists

Full image libraries are large, have many pixel formats and need a lot of
glue to fit the XYO memory model (`TPointer`, `Object`). The XYO tools need
much less: load a PNG, resize it to 16 / 24 / 32 / 48 pixels, write an icon,
draw or compose a few rectangles, save a PNG. `xyo-pixel32` does that with
one pixel format and a handful of functions, managed by `TPointer`, and with
the edge cases handled:

| Problem | What `xyo-pixel32` does |
|---------|-------------------------|
| Scaling an image with transparent areas gives dark fringes | scaling, kernels and blending weight colors by alpha (premultiplied math, straight alpha storage) |
| Upscaling by a large factor in one step is blurry / blocky | `scaleUp` doubles with bicubic + smoothing until close, then interpolates to the exact size |
| Downscaling by interpolation skips pixels (aliasing) | `scaleDown` halves with a 2×2 box average until close, then reaches the exact size |
| A malformed PNG makes libpng `longjmp` / abort | the libpng simplified API is used; every error is a `nullptr` / `false` return |
| BMP files come top-down or bottom-up, with 40 to 124 byte headers | `Bitmap::load` normalizes to bottom-up, keeps the header, rejects compressed / unknown files |
| Copy / blend / cut / draw with rectangles partly outside the images | every rectangle is clipped on both the source and the destination |
| Copy inside the same image with overlapping areas | `Process::copy` picks the direction that keeps the source intact |
| An icon needs a color image and a 1-bit transparency mask per size | `pngToIcon` builds both from one or several PNG files |

## Concepts at a glance

| Need | Use | Notes |
|------|-----|-------|
| New image | `TPointer<Image> img = Process::create(w, h);` | all pixels `0` (transparent black); `nullptr` for bad sizes |
| Make a pixel | `XYO_PIXEL32_PIXEL(r, g, b, a)` | `XYO_PIXEL32_R(p)` ... `_A(p)` to take it apart |
| Read / write a pixel | `img->pixel[y][x]` | no bounds check; `Process::getPixel` / `setPixel` check bounds |
| Fill | `Process::clear(img, pixel)` | |
| Load / save PNG | `Process::pngLoad(file)` / `Process::pngSave(img, file)` | any PNG in, 8-bit RGBA out |
| Resize | `Process::resize(img, w, h)` | new image; picks scale up / down per axis |
| Crop | `Process::cut(img, x, y, w, h)` | new image, clipped |
| Paste (replace) | `Process::copy(dst, src, dx, dy, sx, sy, w, h)` | clipped, overlap safe |
| Paste (alpha over) | `Process::blend(dst, src, dx, dy, sx, sy, w, h)` | clipped |
| Rectangles | `Process::drawRectangle` / `drawFilledRectangle` | blended, clipped |
| Blur, sharpen, edges | `Process::kernel3X3(img, Kernel3X3::gaussian)` | new image |
| BMP file | `Bitmap::load(file)`, `bmp->save(file)` | `Process::imageFromBitmap`, `toBitmap32`, `toBitmap24` |
| Windows icon | `Process::pngToIcon("in.png", "out.ico", 128, false, 0)` | 16, 24, 32, 48 pixels |

## Contents

| Document | What it covers |
|----------|----------------|
| [Getting started](getting-started.md) | Build it, depend on it, include and namespaces, first program, conventions, building without fabricare |
| [Images and pixels](images.md) | `Pixel` layout and macros, `Image` memory layout, `create`, pixel access, alpha model, `alphaBlending` |
| [Processing](processing.md) | Resize and scale, cut, wrap, copy, blend, draw, `Kernel3X3` convolution, color and noise functions |
| [Files: PNG, BMP, ICO](files.md) | PNG load / save, the `Bitmap` class, converting between `Image` and `Bitmap`, palettes and masks, icons |
| [API reference](reference.md) | Every public symbol on one page |

The types used everywhere here come from the layers below: `TPointer` and
`Object` from `xyo-managed-memory`, `TDynamicArray` / `TDoubleEndedQueue`
from `xyo-data-structures`, `String` from `xyo-encoding`, `File` from
`xyo-system`, `RandomMT` from `xyo-cryptography`. Each repository has its
own `docs/`.

## Source map

```
source/XYO/Pixel32.hpp                       umbrella header, include this
source/XYO/Pixel32/
    Dependency.hpp                           xyo-system + xyo-cryptography, export macro, namespaces
    Image[.cpp]                              Pixel, XYO_PIXEL32_* macros, Image
    Bitmap[.cpp]                             BMP file structures, Bitmap (BMP in memory, load / save)
    Icon.hpp                                 IconItem (color bitmap + mask)
    Kernel3x3[.cpp]                          Kernel3X3 and the predefined kernels
    Process.hpp                              every Process:: function, inline helpers
    Process/*.cpp                            one file per Process:: function
        png.cpp                              pngLoad / pngSave, bitmap32LoadPNG / SavePNG, pngToIcon
        bmp.cpp                              Image <-> Bitmap conversions, palettes, masks
        icon.cpp                             generateIcon (.ico writer)
    License/libpng.txt, License/zlib.txt     third party license texts, embedded in License::license()
    License.*.Source.cpp                     generated from License/*.txt (fabricare/make.prepare.js)
    Copyright / License / Version            library metadata
    Library.rc / *.rh                        Windows DLL version resource
test/test.01.cpp                             PNG -> Bitmap -> BMP + PNG round trip of the sample images
test/test.02.cpp                             regression tests: every Process function, Bitmap, PNG, ICO
test/test.0*.input.png                       sample images
```

## AI assistant skill

A Claude Code skill describing how to use this library lives in
[`.claude/skills/xyo-pixel32/`](../.claude/skills/xyo-pixel32/SKILL.md).
It is picked up automatically inside this repository; copy the folder to
`~/.claude/skills/` to have it available in the projects that depend on
`xyo-pixel32`.
