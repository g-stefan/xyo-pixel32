# Processing

Every function is in `XYO::Pixel32::Process` (`#include <XYO/Pixel32.hpp>`).
Functions returning `TPointer<Image>` make a **new** image and return
`nullptr` on failure; the input is not changed. Functions returning `void`
change their first argument. No function checks its `Image *` arguments for
null: check what you pass.

## Resize and scale

| Function | Size rule | Method |
|----------|-----------|--------|
| `resize(img, nx, ny)` | any `nx, ny > 0` | picks `scaleUp` / `scaleDown` per axis; same size = exact copy |
| `scaleUp(img, nx, ny)` | `nx >= width`, `ny >= height` | doubles with bicubic + `filter8X1` smoothing while the target is at least 2× larger, then bicubic to the exact size |
| `scaleDown(img, nx, ny)` | `nx, ny > 0` (meant for smaller sizes) | halves with a 2×2 box average while the target is at most half, then bicubic to 2× the target and one more halving |
| `scaleUpBicubic(img, nx, ny)` | `nx >= width`, `ny >= height` | one bicubic pass |
| `scaleUpBilinear(img, nx, ny)` | `nx >= width`, `ny >= height` | one bilinear pass |
| `scaleUpNearestNeighbor(img, nx, ny)` | `nx >= width`, `ny >= height` | nearest pixel, no new colors |
| `scaleDownX2(img)` | — | `width / 2 × height / 2`, 2×2 box average |
| `scaleDownX2OnX(img)` | — | `width / 2 × height`, 1×2 average |
| `scaleDownX2OnY(img)` | — | `width × height / 2`, 2×1 average |

Use **`resize`** unless you need a specific method: it is the only one that
accepts any target size, and it gives the best quality in both directions.

```cpp
TPointer<Image> icon48 = Process::resize(image, 48, 48);     // any size in, 48 x 48 out
TPointer<Image> pixelArt = Process::scaleUpNearestNeighbor(sprite, sprite->width * 4, sprite->height * 4);
```

Details:

- The `scaleUp*` functions return `nullptr` when the target is smaller
  than the source on either axis.
- Bicubic, bilinear and nearest neighbor map the **corners onto the
  corners**: source pixel `(0, 0)` goes to `(0, 0)` and
  `(width - 1, height - 1)` to `(nx - 1, ny - 1)`. When `nx - 1` is a
  multiple of `width - 1` (for example 4 → 7, 4 → 10) the original pixels
  are kept exactly on the grid points.
- Samples outside the image repeat the edge pixels, so a uniform image
  stays uniform, edges included.
- The halving functions drop the last column / row of an odd size, and
  return `nullptr` for a dimension of `1` (half is `0`).
- Colors are mixed weighted by alpha (see [Images and pixels](images.md)).
  A pixel that ends up with alpha `0` gets color `0`.

## Cut, wrap

```cpp
TPointer<Image> Process::cut(Image *img, long int sx, long int sy, long int lx, long int ly);
```

The rectangle `sx, sy, lx, ly` clipped to the image, as a new image.
`nullptr` if nothing is left (empty or completely outside).

```cpp
TPointer<Image> Process::wrap(Image *img, long int dx, long int dy);
```

Same size, scrolled with wrap around: result pixel `(x, y)` is the input
pixel `((x + dx) mod width, (y + dy) mod height)`. Negative and large
offsets work. Use it to check that a texture tiles, or to move the seam to
the middle.

```cpp
TPointer<Image> Process::wrapBox(Image *img, long int dx, long int dy);
```

A larger image, `width + 2 dx × height + 2 dy`, with the original in the
middle and a border of `dx` / `dy` filled **as if the image were tiled**:
result pixel `(x, y)` is input pixel `((x - dx) mod width, (y - dy) mod height)`.
Negative `dx`, `dy` count as `0`. Typical use: run a filter on the larger
image, then `cut` the middle back out, so the filter sees the tiling
neighbors at the edges:

```cpp
TPointer<Image> box = Process::wrapBox(texture, 1, 1);
TPointer<Image> soft = box ? Process::kernel3X3(box, Kernel3X3::gaussian) : nullptr;
TPointer<Image> seamless = soft ? Process::cut(soft, 1, 1, texture->width, texture->height) : nullptr;
```

## Copy, blend, clear

```cpp
void Process::copy (Image *dst, Image *src, long int dx, long int dy, long int sx, long int sy, long int lx, long int ly);
void Process::blend(Image *dst, Image *src, long int dx, long int dy, long int sx, long int sy, long int lx, long int ly);
void Process::clear(Image *img, Pixel pixel);
```

- `copy` **replaces** the rectangle `dx, dy, lx, ly` of `dst` with the
  rectangle `sx, sy, lx, ly` of `src`, alpha included.
- `blend` draws `src` **over** `dst` with `alphaBlending`.
- Both clip the rectangle on the source and on the destination together:
  negative or too large coordinates copy only the overlapping part, with
  source and destination still aligned (a negative `dx` skips the first
  `-dx` source columns; a negative `sx` moves the destination right).
- `copy` works inside one image (`dst == src`) with overlapping
  rectangles. `blend` does not: use a copy of the source.
- `clear` sets every pixel to `pixel` (no blending).

Paste a logo in the bottom right corner with a 10 pixel margin:

```cpp
Process::blend(photo, logo,
               photo->width - logo->width - 10, photo->height - logo->height - 10,
               0, 0, logo->width, logo->height);
```

## Drawing

```cpp
void Process::drawRectangle      (Image *img, long int sx, long int sy, long int lx, long int ly, Pixel pixel);
void Process::drawFilledRectangle(Image *img, long int sx, long int sy, long int lx, long int ly, Pixel pixel);
```

- `drawRectangle` draws the 1 pixel outline of `sx, sy, lx, ly` (the
  rectangle covers `[sx, sx + lx) × [sy, sy + ly)`, so the right edge is
  column `sx + lx - 1`). Each pixel of the outline is blended exactly once,
  also the corners and the one row / one column cases.
- `drawFilledRectangle` fills the rectangle.
- Both **blend** `pixel` over the image (a half transparent color tints)
  and clip to the image. `lx <= 0` or `ly <= 0` draws nothing.
- To set pixels without blending, use `clear` on a `cut` part and `copy`
  it back, or write `img->pixel[y][x]` in a loop.

There are no line, circle or text functions: draw them with
`Process::setPixel` / `alphaBlending`.

## 3×3 kernels

```cpp
TPointer<Image> Process::kernel3X3(Image *img, Kernel3X3 &kernel);
```

Convolution with a 3×3 matrix; returns a new image of the same size.
Samples outside the image repeat the edge pixels.

```cpp
class Kernel3X3 : public Object {
	public:
		double v[3][3];      // v[row][column], row 0 is above the pixel
		double normalA;
		double normalB;      // result is scaled by normalA / normalB
		Kernel3X3();         // identity: v[1][1] = 1, normalA = normalB = 1
		Kernel3X3(const double v_[3][3], const double normalA_, const double normalB_);
		void copy(Kernel3X3 &src);
};
```

| Predefined | Matrix | `normalA / normalB` | Effect |
|------------|--------|---------------------|--------|
| `Kernel3X3::blur` | all `1` | `1 / 9` | box blur |
| `Kernel3X3::gaussian` | `1 2 1 / 2 4 2 / 1 2 1` | `1 / 16` | soft blur |
| `Kernel3X3::filter8X1` | `1 1 1 / 1 8 1 / 1 1 1` | `1 / 16` | light smoothing (used by `scaleUp`) |
| `Kernel3X3::sharpen` | `0 -1 0 / -1 5 -1 / 0 -1 0` | `1 / 1` | sharpen |
| `Kernel3X3::edgeDetection` | `0 -1 0 / -1 4 -1 / 0 -1 0` | `1 / 1` | edges (Laplacian) |
| `Kernel3X3::edgeDetectionH` | `0 0 0 / -1 2 -1 / 0 0 0` | `1 / 1` | horizontal changes |
| `Kernel3X3::edgeDetectionV` | `0 -1 0 / 0 2 0 / 0 -1 0` | `1 / 1` | vertical changes |
| `Kernel3X3::gradientDetectionH` | `-1 -1 -1 / 0 0 0 / 1 1 1` | `1 / 1` | gradient top → bottom |
| `Kernel3X3::gradientDetectionV` | `-1 0 1 / -1 0 1 / -1 0 1` | `1 / 1` | gradient left → right |

How the result is computed depends on the **sum of the matrix**:

- **Positive sum** (blur, smoothing, sharpen): colors are averaged weighted
  by `kernel × alpha`, so the color is independent of `normalA / normalB`;
  the new alpha is `normalA × Σ(v × alpha) / normalB`. Choose
  `normalA / normalB = 1 / Σv` to keep opaque pixels opaque.
- **Zero or negative sum** (edge, gradient): each color channel is
  `normalA × Σ(v × channel) / normalB`, and the **alpha of the center pixel
  is kept**. Negative results become `0`.

All results are rounded and clamped to `0..255`.

A custom kernel:

```cpp
static const double emboss[3][3] = {
	{-2, -1, 0},
	{-1, 1, 1},
	{0, 1, 2}};
Kernel3X3 kernel(emboss, 1, 1);   // sum = 1
TPointer<Image> result = Process::kernel3X3(image, kernel);
```

`Kernel3X3` is not copyable; use `kernel.copy(Kernel3X3::sharpen)` to start
from a predefined one. Don't change the predefined static kernels: they are
shared by the whole process (and `scaleUp` uses `filter8X1`).

## Color

```cpp
void Process::colorRescale(Image *img);
```

Stretches each channel — `R`, `G`, `B` **and** `A` — independently so its
smallest value becomes `0` and its largest `255` (auto levels). A channel
with one value everywhere is left unchanged, so an opaque image stays
opaque.

```cpp
void Process::average(Image *a, Image *b, uint32_t level1, uint32_t level2, uint32_t average);
```

Mixes `b` into `a`, per channel and alpha:
`a = min(255, (a × level1 + b × level2) / average)`. Only the area common to
both images (from the top left corner) changes. `average == 0` does nothing.
A 50 / 50 mix is `average(a, b, 1, 1, 2)`; 75 / 25 is `average(a, b, 3, 1, 4)`.

## Noise

```cpp
void Process::noise(Image *img, RandomMT &rnd);
void Process::noise2Bit(Image *img, RandomMT &rnd);
```

Fill the image with opaque random gray (`noise`) or random black / white
(`noise2Bit`). `RandomMT` comes from `xyo-cryptography`; seed it for a
repeatable picture:

```cpp
RandomMT rnd;
rnd.seed(1234);
TPointer<Image> texture = Process::create(256, 256);
if (texture) {
	Process::noise(texture, rnd);
	texture = Process::kernel3X3(texture, Kernel3X3::gaussian);
};
```
