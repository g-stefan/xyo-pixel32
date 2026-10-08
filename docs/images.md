# Images and pixels

## Pixel

```cpp
typedef uint32_t Pixel;
```

One pixel is a 32-bit value, **red in the low byte**:

```
bits   31..24   23..16   15..8    7..0
       A        B        G        R
```

On little endian machines (x86, x64, ARM) the bytes in memory are
`R, G, B, A` — the same order as a PNG RGBA row, so `pixelMap` can go to
libpng without conversion (on big endian the loaders ask libpng for ABGR,
which gives the same `uint32_t` values).

Alpha is **straight**: `A = 255` opaque, `A = 0` fully transparent, and
`R, G, B` are the real color, not multiplied by alpha.

### Macros

| Macro | Result |
|-------|--------|
| `XYO_PIXEL32_PIXEL(R, G, B, A)` | build a pixel (each argument masked to 8 bits) |
| `XYO_PIXEL32_R(p)`, `_G(p)`, `_B(p)`, `_A(p)` | one channel, `0..255` |
| `XYO_PIXEL32_RGB(p)` | the same color, alpha forced to `255` |
| `XYO_PIXEL32_CHANGE_R(p, v)`, `_G`, `_B`, `_A` | assign one channel of the variable `p` |
| `XYO_PIXEL32_CHANGE_RGB(p, r, g, b)` | assign the color of `p`, keep its alpha |

The `CHANGE` macros assign to their first argument: pass a variable or
`image->pixel[y][x]`, not an expression.

```cpp
Pixel red = XYO_PIXEL32_PIXEL(255, 0, 0, 255);
Pixel glass = XYO_PIXEL32_PIXEL(200, 220, 255, 64);   // mostly transparent

Pixel p = image->pixel[y][x];
uint32_t gray = (XYO_PIXEL32_R(p) * 77 + XYO_PIXEL32_G(p) * 150 + XYO_PIXEL32_B(p) * 29) >> 8;
XYO_PIXEL32_CHANGE_RGB(image->pixel[y][x], gray, gray, gray);   // alpha unchanged
```

Pixels are plain integers: `0` is transparent black, compare with `==`.

## Image

```cpp
class Image : public Object {
	public:
		long int width;
		long int height;
		Pixel *pixelMap;   // width * height pixels, row after row, top row first
		Pixel **pixel;     // height row pointers: pixel[y] == pixelMap + y * width
};
```

- `pixel[y][x]` is the pixel at column `x`, row `y`; `y = 0` is the **top**
  row. There is no padding between rows: `pixelMap[y * width + x]` is the
  same pixel.
- The fields are public for speed. Treat `width`, `height` and the two
  pointers as read only: the destructor frees `pixelMap` and `pixel` with
  `delete[]`.
- `Image` derives from `Object` (`xyo-managed-memory`) and lives in a
  `TPointer<Image>`. It is not copyable.

### Create

```cpp
TPointer<Image> image = Process::create(640, 480);
if (!image) {
	// width or height <= 0, or width * height * 4 does not fit in size_t
};
```

`create` returns an image with every pixel `0` (transparent black). Fill it
with `Process::clear(image, color)`.

Do not use `TPointer<Image> image; image.newMemory();` to make an image: it
gives a `0 × 0` image with null pointers, which the processing functions do
not expect.

### Pixel access

| Call | Out of range |
|------|--------------|
| `image->pixel[y][x]` / `image->pixel[y][x] = p` | **undefined**: no check |
| `Process::getPixel(image, x, y)` | returns `0` |
| `Process::setPixel(image, x, y, p)` | does nothing |
| `Process::getPixelX(image, x, y)` | returns the nearest edge pixel (clamp) |

Use the direct access in loops that stay inside `0 <= x < width`,
`0 <= y < height`; use `getPixel` / `setPixel` for scattered points that
may fall outside; `getPixelX` for filters that sample around a pixel.

A loop over every pixel:

```cpp
long int x, y;
for (y = 0; y < image->height; ++y) {
	Pixel *row = image->pixel[y];
	for (x = 0; x < image->width; ++x) {
		// invert the color, keep alpha
		row[x] = (row[x] & 0xFF000000) | (~row[x] & 0x00FFFFFF);
	};
};
```

or over the whole buffer when the position does not matter:

```cpp
Pixel *p = image->pixelMap;
Pixel *end = p + (size_t)image->width * (size_t)image->height;
for (; p < end; ++p) {
	*p = XYO_PIXEL32_RGB(*p);   // make every pixel opaque
};
```

### Copying an image

`Image` is not copyable. To duplicate one, use `Process::resize` with the
same size (it returns an exact copy) or `Process::cut` with the full
rectangle:

```cpp
TPointer<Image> duplicate = Process::cut(image, 0, 0, image->width, image->height);
```

## Alpha

All the functions that mix pixels treat alpha correctly:

- **Scaling and kernels** multiply each color by its alpha, mix, then
  divide by the mixed alpha (premultiplied math). A transparent pixel
  contributes nothing to the color of its neighbors, whatever its `R, G, B`
  are, so no dark halo appears around shapes on a transparent background.
- **Blending** uses the "source over destination" operator:

```cpp
inline Pixel Process::alphaBlending(Pixel over, Pixel under);
```

```
A = Ao + Au * (255 - Ao) / 255
C = (Co * Ao + Cu * Au * (255 - Ao) / 255) / A        for C in R, G, B
```

in integers (`o` = over, `u` = under). When both pixels are fully
transparent the result is `0`. `Process::blend`, `drawRectangle` and
`drawFilledRectangle` use it; call it yourself for single pixels:

```cpp
image->pixel[y][x] = Process::alphaBlending(XYO_PIXEL32_PIXEL(255, 0, 0, 128), image->pixel[y][x]);
```

- **Replacing** (`Process::copy`, `clear`, `setPixel`, direct writes)
  writes the four channels as they are, including alpha.

Two functions prepare images with transparent areas for formats that
only know "visible / invisible" (icons, masks):

- `Process::backgroundAlpha(image, background)` gives every **fully
  transparent** pixel the color of `background`, still with alpha `0`.
  Nothing changes visually; programs that ignore alpha (BMP viewers, old
  icon renderers) show the background color there instead of black. The
  resampling functions ignore the color of alpha `0` pixels and write
  `0` for pixels that end up fully transparent, so call it **after**
  resizing if the color must survive.
- `Process::backgroundAlphaLevel(image, background, level)` composites
  every pixel over `background`, then sets alpha to `0` where the original
  alpha was below `level` and `255` elsewhere.

## Inline helpers

`Process.hpp` also has small inline helpers used by the implementation and
useful in your own pixel code:

| Helper | Does |
|--------|------|
| `interpolateLinear(v0, v1, m)` | `v0 * (1 - m) + v1 * m` |
| `interpolateCubic(v0, v1, v2, v3, m)` | cubic through 4 samples, between `v1` (`m = 0`) and `v2` (`m = 1`) |
| `interpolateNearestNeighbor(v0, v1, m)` | `v0` if `m <= 0.5`, else `v1` |
| `pixelClampX(int)` | clamp to `0..255` |
| `pixelRound(double)` | round and clamp to `0..255`; NaN gives `0` |
| `clipSpan(start, length, limit)` | clip `[start, start + length)` to `[0, limit)`; `false` if empty |
| `clipSpan2(destination, source, length, destinationLimit, sourceLimit)` | clip a source and a destination span of the same length together |
