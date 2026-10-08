# Files: PNG, BMP, ICO

## PNG

```cpp
TPointer<Image> Process::pngLoad(const char *fileName);
bool            Process::pngSave(Image *image, const char *fileName);
```

`pngLoad` reads **any** PNG — gray, gray + alpha, RGB, RGBA, palette, 1 to
16 bits per channel, `tRNS` transparency, interlaced — and converts it to
8-bit RGBA with libpng's simplified API. It returns `nullptr` for a
missing, truncated, corrupt or too large file (width over `0x1FFFFFFF`),
and never aborts the process.

`pngSave` always writes 8-bit RGBA, with the default compression. It
returns `false` if the image is empty or the file can not be written.

```cpp
TPointer<Image> image = Process::pngLoad("in.png");
if (!image) {
	return false;
};
TPointer<Image> small = Process::resize(image, 64, 64);
return small && Process::pngSave(small, "out.png");
```

There are no other PNG options (palette output, compression level, text
chunks); the image is always written as RGBA.

## BMP: the `Bitmap` class

`Bitmap` is a BMP file held in memory, exactly as it is on disk: file
header, info header, palette, pixel rows. It exists for the formats an
`Image` can not represent — palettes, 1 / 4 / 8 / 24 bits — which are what
`.bmp` and `.ico` files need.

```cpp
TPointer<Bitmap> bmp = Bitmap::load("in.bmp");           // nullptr on error
TPointer<Image> image = Process::imageFromBitmap(bmp);   // any depth -> RGBA
// ... process ...
TPointer<Bitmap> out = Process::toBitmap32(image);       // RGBA -> 32 bits with alpha
if (!out || !out->save("out.bmp")) {
	// error
};
```

### Create

| Factory | Header | Pixels |
|---------|--------|--------|
| `Bitmap::newImage32Bits(w, h)` | V4 (108 bytes), `BITFIELDS`, alpha mask, sRGB | `BitmapRGBA` (B, G, R, A in memory) |
| `Bitmap::newImage24Bits(w, h)` | `BITMAPINFOHEADER` (40 bytes) | `BitmapRGB` (B, G, R) |
| `Bitmap::newImage8Bits(w, h)` | 40 bytes + 256 entry palette | palette index |
| `Bitmap::newImage4Bits(w, h)` | 40 bytes + 16 entry palette | palette index, 2 per byte |
| `Bitmap::newImage1Bit(w, h)` | 40 bytes + 2 entry palette | palette index, 8 per byte |

They return `nullptr` for a zero size or a file larger than 4 GB. Pixels
**and palette** start zeroed: set the palette of a 1 / 4 / 8 bit bitmap
with `setPaletteIndex` before using it. Never create a `Bitmap` with
`newMemory()`: it has no image and every method would crash.

### Load and save

`Bitmap::load(name)` accepts:

- 1, 4, 8, 24 and 32 bits per pixel, uncompressed (`BI_RGB`);
- 32 bits `BI_BITFIELDS` with the standard masks (R `0x00FF0000`,
  G `0x0000FF00`, B `0x000000FF`, alpha `0xFF000000` or none);
- info headers from 40 (`BITMAPINFOHEADER`) to 124 bytes (`BITMAPV5HEADER`),
  kept as they are;
- top-down files (negative height), converted to bottom-up;
- palettes shorter than the maximum (`biClrUsed`), stored full size.

Everything else — RLE, JPEG / PNG inside BMP, 16 bits, unusual masks,
truncated files — returns `nullptr`.

`bmp->save(name)` writes the memory image to the file and returns `false`
on error.

> **32-bit BMP and alpha.** Many programs write 32-bit BMP files with the
> fourth byte set to `0` meaning "unused". `imageFromBitmap` takes it as
> alpha, which gives a fully transparent image. For such files call
> `bmp->setAlpha32(255)` before converting.

### Coordinates

**`Bitmap` rows are bottom-up**, like the BMP format: in the pixel methods
`y = 0` is the **bottom** row. (`Image` is top-down; the conversion
functions flip for you.) The one exception is `getRow32Bits(y, scanLine)`,
which counts from the top.

```cpp
uint32_t scanLine = bmp->getScanLine();          // bytes per row, multiple of 4
for (uint32_t y = 0; y < bmp->getHeight(); ++y) {
	BitmapRGBA *row = bmp->getRow32Bits(y, scanLine);   // y = 0 is the top row
	for (uint32_t x = 0; x < bmp->getWidth(); ++x) {
		row[x].rgbAlpha = 255;
	};
};
```

### Pixel methods

The pixel methods do **no bounds or depth checks**: call the ones matching
`bmp->getPixelWidth()` (1, 4, 8, 24, 32) with `x < getWidth()`,
`y < getHeight()`. The only checked ones are `getPixel32s` / `setPixel32s`
(32 bits, signed coordinates, outside = transparent / ignored).

| Depth | Raw value | Through the palette |
|-------|-----------|---------------------|
| 32 | `getPixel32` / `setPixel32` (`BitmapRGBA`) | — |
| 24 | `getPixel24` / `setPixel24` (`BitmapRGB`), `getPixel24X` → `BitmapRGBA` opaque | — |
| 8 | `getPixel8` / `setPixel8` (index) | `getPixelPal8` / `setPixelPal8` (`BitmapRGBA`) |
| 4 | `getPixel4` / `setPixel4` | `getPixelPal4` / `setPixelPal4` |
| 1 | `getPixel1` / `setPixel1` | `getPixelPal1` / `setPixelPal1` |
| any | `getPixel32X` → `BitmapRGBA`; palette and 24-bit pixels are opaque | |

`setPixelPalN` stores the index of the exact color if the palette has it,
otherwise of the **nearest** color (squared distance on B, G, R and the
fourth byte).

`BitmapRGBA` is `{ rgbBlue, rgbGreen, rgbRed, rgbAlpha }` — note the B, G, R
order, as in the file. In palette entries the fourth byte is reserved by
the BMP format; the library writes `0` there and treats palette colors as
opaque.

Palette and whole image helpers:

| Method | Does |
|--------|------|
| `getPaletteSize()` | 2, 16, 256, or 0 for 24 / 32 bits |
| `getPaletteIndex(i, c)` / `setPaletteIndex(i, c)` | read / write palette entry `i` |
| `getPaletteColor(index, c)` | `true` and the index if `c` is in the palette, else `false` and the nearest index |
| `isPalette()` | depth below 16 |
| `convertTo32Bits()` | 32-bit copy (palette and 24-bit pixels opaque); returns **the same bitmap** if it is already 32 bits |
| `swapRB32()` | swap red and blue of every pixel (32 bits only) |
| `setAlpha32(a)` | set alpha of every pixel (32 bits only) |
| `getBitmapImage()` | the raw `BitmapImage *` (headers + data), for direct access |

### Converting between `Image` and `Bitmap`

| Function | Result |
|----------|--------|
| `Process::imageFromBitmap(bmp)` | `Image` from any depth; 32 bits keeps alpha, others opaque |
| `Process::toBitmap32(image)` | 32-bit bitmap with alpha |
| `Process::toBitmap24(image)` | 24-bit bitmap, alpha dropped |
| `Process::alphaToBitmap8(image)` | 8 bits, pixel = alpha; palette entry `i` is black with `i` in the reserved byte |
| `Process::alphaToBitmap1(image, level)` | 1 bit **mask**: `1` (white) where alpha `< level`, `0` (black) elsewhere |
| `Process::bitmap32LoadPNG(name)` | PNG file straight to a 32-bit bitmap |
| `Process::bitmap32SavePNG(bmp, name)` | 32-bit bitmap to PNG (`false` for other depths) |

From a 32-bit `Bitmap` to the palette formats (all return `false` if the
input is not 32 bits):

| Function | Outputs |
|----------|---------|
| `bitmap32Alpha1(in32, out1, level)` | 1-bit mask, `1` where alpha `< level` |
| `bitmap32To24Alpha8(in32, out24, out8)` | 24-bit color + 8-bit alpha with a gray palette |
| `bitmap32To8Alpha1(in32, out8, out1, level, noFreeColorsLeft)` | 256 color palette image + 1-bit mask |
| `bitmap32To4Alpha1(in32, out4, out1, level, noFreeColorsLeft)` | 16 color palette image + 1-bit mask |

The palette converters take the first distinct colors they meet (bottom row
first) until the palette is full; later colors use the nearest entry and
set `noFreeColorsLeft = true`. This is exact for images with few colors
(icons, pixel art), not a quantizer for photos.

## ICO: Windows icons

An icon file holds several images of different sizes. Each one is an
`IconItem`: a color bitmap plus a 1-bit transparency mask of the same size.

```cpp
class IconItem : public virtual Object {
	public:
		TPointer<Bitmap> bmp;    // 1, 4, 8, 24 or 32 bits, at most 256 x 256
		TPointer<Bitmap> mask;   // 1 bit, same size; 1 = transparent
};

bool Process::generateIcon(TDoubleEndedQueue<TPointer<IconItem>> &itemList, const char *fileName);
```

`generateIcon` writes the items **in the order they were pushed**, each as
a `BITMAPINFOHEADER` image (no PNG compressed entries). It returns `false`
for an empty list, an item larger than 256 × 256, a mask that is not 1 bit
or not the same size, or a write error.

```cpp
TDoubleEndedQueue<TPointer<IconItem>> iconList;
static const long int size[] = {16, 32, 48, 256};
for (int k = 0; k < 4; ++k) {
	TPointer<Image> image = Process::resize(source, size[k], size[k]);
	if (!image) {
		return false;
	};
	TPointer<IconItem> item;
	item.newMemory();
	item->bmp = Process::toBitmap32(image);            // smooth alpha for modern Windows
	item->mask = Process::alphaToBitmap1(image, 128);  // hard mask for old renderers
	if (!item->bmp || !item->mask) {
		return false;
	};
	iconList.push(item);
};
return Process::generateIcon(iconList, "app.ico");
```

### PNG to ICO in one call

```cpp
bool Process::pngToIcon(const char *pngFile, const char *iconFile,
                        int level, bool useBackgroundAlpha, uint32_t background);
bool Process::pngToIcon(const char *png48, const char *png32, const char *png24, const char *png16,
                        const char *iconFile, int level, bool useBackgroundAlpha, uint32_t background);
bool Process::pngToIcon(TDynamicArray<String> &pngFile, const char *iconFile,
                        int level, bool useBackgroundAlpha, uint32_t background);
```

| Variant | Icon sizes |
|---------|------------|
| one PNG | 16, 24, 32 and 48, all resized from the one file (square: the aspect ratio is not kept) |
| four PNG | 16, 24, 32 and 48, one file per size (each still resized to its size, so they may be any size) |
| list | one entry per file, at the file's own size (each at most 256 × 256), in list order |

Each entry gets a 32-bit color bitmap with the **smooth alpha** of the PNG
and a 1-bit mask where alpha `< level` is transparent (`128` is the usual
level).

With `useBackgroundAlpha = true`, `background` (a `Pixel`) is taken as the
color behind the icon: the mask is computed after compositing over it
(`backgroundAlphaLevel`), and fully transparent pixels of the loaded PNG
get its color (`backgroundAlpha`) — this color only reaches the color
bitmap when the entry is not resampled (list variant, or a file already at
its size), because resampling writes `0` for fully transparent pixels. Use
it when the icon will be shown on a known background by programs that
ignore alpha. Pass `false, 0` otherwise.

The `png-to-icon` command line tool is a thin wrapper over these three
functions.
