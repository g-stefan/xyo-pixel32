# API reference

Everything is declared in `<XYO/Pixel32.hpp>`, namespace `XYO::Pixel32`
unless noted. `nullptr` / `false` results mean failure.

## Pixel (`Image.hpp`)

```cpp
typedef uint32_t Pixel;   // R | G << 8 | B << 16 | A << 24, straight alpha
```

| Macro | |
|-------|-|
| `XYO_PIXEL32_PIXEL(R, G, B, A)` | build a pixel |
| `XYO_PIXEL32_R(x)` / `_G(x)` / `_B(x)` / `_A(x)` | channel `0..255` |
| `XYO_PIXEL32_RGB(x)` | `x` with alpha `255` |
| `XYO_PIXEL32_CHANGE_R(Color, X)` / `_G` / `_B` / `_A` | assign one channel of the lvalue `Color` |
| `XYO_PIXEL32_CHANGE_RGB(Color, R, G, B)` | assign the color of the lvalue `Color`, keep alpha |

## Image (`Image.hpp`)

```cpp
class Image : public Object {               // not copyable
	long int width;
	long int height;
	Pixel *pixelMap;                         // width * height, top row first
	Pixel **pixel;                           // pixel[y][x]
	Image();                                 // 0 x 0, null pointers: use Process::create
	~Image();                                // delete[] pixelMap, pixel
};
```

## Kernel3X3 (`Kernel3x3.hpp`)

```cpp
class Kernel3X3 : public Object {           // not copyable
	double v[3][3];
	double normalA;
	double normalB;
	Kernel3X3();                             // identity, 1 / 1
	Kernel3X3(const double v_[3][3], const double normalA_, const double normalB_);
	void copy(Kernel3X3 &src);

	static Kernel3X3 filter8X1;              // {1,1,1},{1,8,1},{1,1,1}       1/16
	static Kernel3X3 gaussian;               // {1,2,1},{2,4,2},{1,2,1}       1/16
	static Kernel3X3 blur;                   // all 1                          1/9
	static Kernel3X3 sharpen;                // {0,-1,0},{-1,5,-1},{0,-1,0}   1/1
	static Kernel3X3 edgeDetection;          // {0,-1,0},{-1,4,-1},{0,-1,0}   1/1
	static Kernel3X3 edgeDetectionH;         // {0,0,0},{-1,2,-1},{0,0,0}     1/1
	static Kernel3X3 edgeDetectionV;         // {0,-1,0},{0,2,0},{0,-1,0}     1/1
	static Kernel3X3 gradientDetectionH;     // {-1,-1,-1},{0,0,0},{1,1,1}    1/1
	static Kernel3X3 gradientDetectionV;     // {-1,0,1},{-1,0,1},{-1,0,1}    1/1
};
```

## Process (`Process.hpp`, namespace `XYO::Pixel32::Process`)

### Image creation and pixels

| Function | |
|----------|-|
| `TPointer<Image> create(long int width, long int height)` | zeroed image; `nullptr` if a size `<= 0` or too large |
| `Pixel getPixel(Image *, long int x, long int y)` | `0` outside |
| `void setPixel(Image *, long int x, long int y, Pixel)` | ignored outside |
| `Pixel getPixelX(Image *, long int x, long int y)` | outside clamps to the edge |
| `void clear(Image *, Pixel)` | fill |

### Size and geometry (new image, input unchanged)

| Function | |
|----------|-|
| `TPointer<Image> resize(Image *, long int nx, long int ny)` | any size `> 0`; best quality |
| `TPointer<Image> scaleUp(Image *, long int nx, long int ny)` | `nx >= width`, `ny >= height`; bicubic doubling + smoothing |
| `TPointer<Image> scaleDown(Image *, long int nx, long int ny)` | box halving, then exact size |
| `TPointer<Image> scaleUpBicubic(Image *, long int nx, long int ny)` | `nx >= width`, `ny >= height` |
| `TPointer<Image> scaleUpBilinear(Image *, long int nx, long int ny)` | `nx >= width`, `ny >= height` |
| `TPointer<Image> scaleUpNearestNeighbor(Image *, long int nx, long int ny)` | `nx >= width`, `ny >= height` |
| `TPointer<Image> scaleDownX2(Image *)` | half on both axes, 2×2 average |
| `TPointer<Image> scaleDownX2OnX(Image *)` | half width |
| `TPointer<Image> scaleDownX2OnY(Image *)` | half height |
| `TPointer<Image> cut(Image *, long int sx, long int sy, long int lx, long int ly)` | clipped; `nullptr` if empty |
| `TPointer<Image> wrap(Image *, long int dx, long int dy)` | `out(x, y) = in((x + dx) mod w, (y + dy) mod h)` |
| `TPointer<Image> wrapBox(Image *, long int dx, long int dy)` | `(w + 2dx) × (h + 2dy)`, border from tiling |
| `TPointer<Image> kernel3X3(Image *, Kernel3X3 &)` | 3×3 convolution |

### Compositing and color (in place)

| Function | |
|----------|-|
| `void copy(Image *dst, Image *src, long int dx, long int dy, long int sx, long int sy, long int lx, long int ly)` | replace, clipped, overlap safe |
| `void blend(Image *dst, Image *src, long int dx, long int dy, long int sx, long int sy, long int lx, long int ly)` | `src` over `dst`, clipped |
| `void drawRectangle(Image *, long int sx, long int sy, long int lx, long int ly, Pixel)` | 1 pixel outline, blended |
| `void drawFilledRectangle(Image *, long int sx, long int sy, long int lx, long int ly, Pixel)` | filled, blended |
| `void average(Image *inOut, Image *in2, uint32_t level1, uint32_t level2, uint32_t average)` | `(a·level1 + b·level2) / average`, common area |
| `void colorRescale(Image *)` | stretch each channel (and alpha) to `0..255` |
| `void noise(Image *, RandomMT &)` | random opaque gray |
| `void noise2Bit(Image *, RandomMT &)` | random opaque black / white |
| `void backgroundAlpha(Image *, Pixel background)` | alpha `0` pixels get the background color, alpha stays `0` |
| `void backgroundAlphaLevel(Image *, Pixel background, int level)` | composite over background; alpha `< level` → `0`, else `255` |

### PNG

| Function | |
|----------|-|
| `TPointer<Image> pngLoad(const char *)` | any PNG → RGBA |
| `bool pngSave(Image *, const char *)` | 8-bit RGBA PNG |
| `TPointer<Bitmap> bitmap32LoadPNG(const char *name)` | PNG → 32-bit `Bitmap` |
| `bool bitmap32SavePNG(Bitmap *bmp, const char *name)` | 32-bit `Bitmap` → PNG |

### Image ↔ Bitmap

| Function | |
|----------|-|
| `TPointer<Image> imageFromBitmap(Bitmap *bmp)` | any depth; non 32-bit is opaque |
| `TPointer<Bitmap> toBitmap32(Image *)` | 32 bits with alpha |
| `TPointer<Bitmap> toBitmap24(Image *)` | 24 bits, no alpha |
| `TPointer<Bitmap> alphaToBitmap8(Image *)` | 8 bits, index = alpha |
| `TPointer<Bitmap> alphaToBitmap1(Image *, int level)` | mask, `1` where alpha `< level` |
| `bool bitmap32Alpha1(Bitmap *in32, TPointer<Bitmap> &out1, int level)` | mask from a 32-bit bitmap |
| `bool bitmap32To24Alpha8(Bitmap *in32, TPointer<Bitmap> &out24, TPointer<Bitmap> &out8)` | color + gray alpha |
| `bool bitmap32To8Alpha1(Bitmap *in32, TPointer<Bitmap> &out8, TPointer<Bitmap> &out1, int level, bool &noFreeColorsLeft)` | 256 colors + mask |
| `bool bitmap32To4Alpha1(Bitmap *in32, TPointer<Bitmap> &out4, TPointer<Bitmap> &out1, int level, bool &noFreeColorsLeft)` | 16 colors + mask |

### Icons

| Function | |
|----------|-|
| `bool generateIcon(TDoubleEndedQueue<TPointer<IconItem>> &itemList, const char *fileName)` | write `.ico`, items in push order |
| `bool pngToIcon(const char *pngFile, const char *iconFile, int level, bool useBackgroundAlpha, uint32_t background)` | 16, 24, 32, 48 from one PNG |
| `bool pngToIcon(const char *png48, const char *png32, const char *png24, const char *png16, const char *iconFile, int level, bool useBackgroundAlpha, uint32_t background)` | one PNG per size |
| `bool pngToIcon(TDynamicArray<String> &pngFile, const char *iconFile, int level, bool useBackgroundAlpha, uint32_t background)` | one entry per PNG, own size |

### Inline helpers

| Function | |
|----------|-|
| `double interpolateCubic(double v0, double v1, double v2, double v3, double m)` | between `v1` and `v2` |
| `double interpolateLinear(double v0, double v1, double m)` | |
| `double interpolateNearestNeighbor(double v0, double v1, double m)` | |
| `int pixelClampX(int x)` | clamp `0..255` |
| `int pixelRound(double x)` | round + clamp, NaN → `0` |
| `Pixel alphaBlending(Pixel over, Pixel under)` | "over" operator, straight alpha |
| `bool clipSpan(long int &start, long int &length, long int limit)` | clip to `[0, limit)` |
| `bool clipSpan2(long int &destination, long int &source, long int &length, long int destinationLimit, long int sourceLimit)` | clip two aligned spans |

## Bitmap (`Bitmap.hpp`)

```cpp
class Bitmap : public virtual Object {      // not copyable
	static TPointer<Bitmap> newImage32Bits(uint32_t lx, uint32_t ly);
	static TPointer<Bitmap> newImage24Bits(uint32_t lx, uint32_t ly);
	static TPointer<Bitmap> newImage8Bits(uint32_t lx, uint32_t ly);
	static TPointer<Bitmap> newImage4Bits(uint32_t lx, uint32_t ly);
	static TPointer<Bitmap> newImage1Bit(uint32_t lx, uint32_t ly);
	static TPointer<Bitmap> newImageOwner(BitmapImage *image_);   // takes a new uint8_t[] block
	static TPointer<Bitmap> load(const char *name);
	bool save(const char *name);

	BitmapImage *getBitmapImage();
	static uint32_t scanLine(BitmapInfoHeader &bih);              // bytes per row, 4 aligned
	static void calculateImageSizeNoCompression(BitmapFileHeader &bfh, BitmapInfoHeader &bih);

	// y = 0 is the bottom row; no bounds / depth checks
	void setPixel32(uint32_t x, uint32_t y, BitmapRGBA &c);
	void setPixel24(uint32_t x, uint32_t y, BitmapRGB &c);
	void setPixel8(uint32_t x, uint32_t y, uint8_t &c);
	void setPixel4(uint32_t x, uint32_t y, uint8_t &c);
	void setPixel1(uint32_t x, uint32_t y, uint8_t &c);
	void getPixel32(uint32_t x, uint32_t y, BitmapRGBA &c);
	void getPixel24(uint32_t x, uint32_t y, BitmapRGB &c);
	void getPixel24X(uint32_t x, uint32_t y, BitmapRGBA &c);     // opaque
	void getPixel8(uint32_t x, uint32_t y, uint8_t &c);
	void getPixel4(uint32_t x, uint32_t y, uint8_t &c);
	void getPixel1(uint32_t x, uint32_t y, uint8_t &c);
	void getPixelPal8(uint32_t x, uint32_t y, BitmapRGBA &c);
	void getPixelPal4(uint32_t x, uint32_t y, BitmapRGBA &c);
	void getPixelPal1(uint32_t x, uint32_t y, BitmapRGBA &c);
	void setPixelPal8(uint32_t x, uint32_t y, BitmapRGBA &c);    // exact or nearest entry
	void setPixelPal4(uint32_t x, uint32_t y, BitmapRGBA &c);
	void setPixelPal1(uint32_t x, uint32_t y, BitmapRGBA &c);
	void getPixel32s(long int x, long int y, BitmapRGBA &c);     // 32 bits, outside = 0
	void setPixel32s(long int x, long int y, BitmapRGBA &c);     // 32 bits, outside ignored
	void getPixel32X(uint32_t x, uint32_t y, BitmapRGBA &c);     // any depth

	uint16_t getPaletteSize();
	void getPaletteIndex(uint8_t index, BitmapRGBA &c);
	void setPaletteIndex(uint8_t index, BitmapRGBA &c);
	bool getPaletteColor(uint8_t &index, BitmapRGBA &c);         // true = exact
	uint32_t getWidth();
	uint32_t getHeight();
	uint16_t getPixelWidth();                                     // bits per pixel
	bool isPalette();
	BitmapRGBA *getRow32Bits(uint32_t y, uint32_t scanLine);     // y = 0 is the TOP row
	uint32_t getScanLine();

	TPointer<Bitmap> convertTo32Bits();                          // this if already 32 bits
	void swapRB32();
	void setAlpha32(uint8_t alpha);
};
```

File structures (packed, little endian, sizes checked with `static_assert`):

| Type | Size | |
|------|------|-|
| `BitmapFileHeader` | 14 | `bfType` (`XYO_PIXEL32_BITMAP_FILE_ID` = `0x4D42`, "BM"), `bfSize`, `bfOffBits` |
| `BitmapInfoHeader` | 40 | `BITMAPINFOHEADER` |
| `BitmapInfoHeaderV4` | 108 | `BITMAPV4HEADER`: masks, `biCSType`, endpoints, gamma |
| `BitmapImage` | 54 | `{ fh, ih }`: the start of the in-memory file |
| `BitmapRGBA` | 4 | `rgbBlue, rgbGreen, rgbRed, rgbAlpha` |
| `BitmapRGB` | 3 | `rgbBlue, rgbGreen, rgbRed` |
| `BitmapCIEXYZ`, `BitmapCIEXYZTRIPLE`, `BitmapFXPT2DOT30` | | color space endpoints |
| `BitmapCompression::` | | `RGB`, `RLE8`, `RLE4`, `BITFIELDS`, `JPEG`, `PNG`, `CMYK`, `CMYKRLE8`, `CMYKRLE4` |
| `BitmapLogicalColorSpace::` | | `CALIBRATED_RGB`, `sRGB`, `WINDOWS_COLOR_SPACE` |

## IconItem (`Icon.hpp`)

```cpp
class IconItem : public virtual Object {    // not copyable
	TPointer<Bitmap> bmp;                    // 1, 4, 8, 24 or 32 bits, <= 256 x 256
	TPointer<Bitmap> mask;                   // 1 bit, same size, 1 = transparent
};
```

## Library metadata

| Function | |
|----------|-|
| `Version::version()`, `build()`, `versionWithBuild()`, `datetime()` | from `version.json` |
| `Copyright::copyright()`, `publisher()`, `company()`, `contact()` | |
| `License::license()` | MIT text + the libpng and zlib licenses |
| `License::shortLicense()` | |

## Export macros

| Macro | |
|-------|-|
| `XYO_PIXEL32_EXPORT` | on every exported symbol |
| `XYO_PIXEL32_INTERNAL` | defined while building the DLL: export |
| `XYO_PIXEL32_LIBRARY` | static linking: no import / export |
