# Getting started

## 1. Build and install

The library is built with [fabricare](https://github.com/g-stefan/fabricare),
the build tool used by all XYO C++ projects. The XYO layers up to
`xyo-system` and `xyo-cryptography` must be installed to the SDK first; on
Windows also `vendor-libpng` and `vendor-zlib` (they provide `libpng` and
`libz`). On Linux the system `libpng` and `zlib` development packages are
used (`libpng-dev` / `zlib1g-dev` on Debian and Ubuntu). From the
repository root:

```bash
fabricare make       # build into output/
fabricare test       # build and run test/test.*.cpp (run make first)
fabricare install    # copy output/{bin,include,lib} to ~/.fabricare/<platform>
fabricare clean      # remove output/ and temp/
```

`make` first runs `fabricare/make.prepare.js`, which turns
`source/XYO/Pixel32/License/libpng.txt` and `zlib.txt` into the C string
files `License.libpng.Source.cpp` / `License.zlib.Source.cpp` included by
`License.cpp` (so `License::license()` carries the third party notices).

| Project       | Kind                                | Notes                                                    |
|---------------|-------------------------------------|----------------------------------------------------------|
| `xyo-pixel32` | DLL / shared library (`dll-or-lib`) | a static library when the platform is built static       |
| `test.01`     | test executable                     | PNG → `Bitmap` → BMP + PNG with `test/test.0*.input.png` |
| `test.02`     | test executable                     | regression tests for every function (`test.02 <group>` runs one group) |

## 2. Depend on it from another fabricare project

In the consumer's `fabricare.json`:

```json
{
	"name": "my-tool",
	"make": "exe",
	"sourcePath": "XYO/MyTool",
	"dependency": [
		"xyo-pixel32"
	]
}
```

`xyo-system`, `xyo-cryptography`, the layers below them, and `libpng` /
`libz` come in as transitive dependencies.

## 3. Include

```cpp
#include <XYO/Pixel32.hpp>
```

The umbrella header pulls in `<XYO/System.hpp>`, `<XYO/Cryptography.hpp>`
and every public header of this library. It does **not** include `png.h`:
libpng is an implementation detail.

Namespace `XYO::Pixel32` contains:

```cpp
using namespace XYO::System;
using namespace XYO::Cryptography;
```

so `using namespace XYO::Pixel32;` is enough to write `TPointer`, `String`,
`File`, `RandomMT`, `Image`, `Bitmap` unqualified. The processing functions
are in the nested namespace `XYO::Pixel32::Process` — write them as
`Process::resize(...)`. Don't add `using namespace Process`: its `copy` and
`clear` are common names.

The metadata namespaces exist in every XYO layer: write
`XYO::Pixel32::Version::version()` in full.

## 4. First program

Load a PNG, make a half size thumbnail with a soft shadow frame, save it as
PNG and BMP, and write an icon from the original:

```cpp
#include <XYO/Pixel32.hpp>

using namespace XYO::Pixel32;

class Application : public virtual IApplication {
		XYO_PLATFORM_DISALLOW_COPY_ASSIGN_MOVE(Application);

	public:
		inline Application(){};

		int main(int cmdN, char *cmdS[]);
};

int Application::main(int cmdN, char *cmdS[]) {
	if (cmdN < 2) {
		printf("usage: %s image.png\n", cmdS[0]);
		return 1;
	};

	TPointer<Image> image = Process::pngLoad(cmdS[1]);
	if (!image) {
		printf("* Error: can not load %s\n", cmdS[1]);
		return 1;
	};
	printf("%s: %ld x %ld\n", cmdS[1], image->width, image->height);

	// Half size, never smaller than 1 pixel
	long int width = image->width / 2;
	long int height = image->height / 2;
	if (width < 1) {
		width = 1;
	};
	if (height < 1) {
		height = 1;
	};
	TPointer<Image> thumbnail = Process::resize(image, width, height);
	if (!thumbnail) {
		printf("* Error: resize\n");
		return 1;
	};

	// White canvas with a 4 pixel border, a blurred shadow, then the thumbnail
	TPointer<Image> canvas = Process::create(width + 8, height + 8);
	if (!canvas) {
		printf("* Error: create\n");
		return 1;
	};
	Process::clear(canvas, XYO_PIXEL32_PIXEL(255, 255, 255, 255));
	Process::drawFilledRectangle(canvas, 6, 6, width, height, XYO_PIXEL32_PIXEL(0, 0, 0, 96));
	canvas = Process::kernel3X3(canvas, Kernel3X3::gaussian);
	if (!canvas) {
		printf("* Error: kernel3X3\n");
		return 1;
	};
	Process::blend(canvas, thumbnail, 4, 4, 0, 0, width, height);
	Process::drawRectangle(canvas, 4, 4, width, height, XYO_PIXEL32_PIXEL(0, 0, 0, 255));

	if (!Process::pngSave(canvas, "thumbnail.png")) {
		printf("* Error: can not write thumbnail.png\n");
		return 1;
	};

	TPointer<Bitmap> bmp = Process::toBitmap32(canvas);
	if (!bmp || !bmp->save("thumbnail.bmp")) {
		printf("* Error: can not write thumbnail.bmp\n");
		return 1;
	};

	// 16, 24, 32 and 48 pixel icon, pixels with alpha below 128 are transparent
	if (!Process::pngToIcon(cmdS[1], "image.ico", 128, false, 0)) {
		printf("* Error: can not write image.ico\n");
		return 1;
	};

	return 0;
};

XYO_APPLICATION_MAIN(Application);
```

`XYO_APPLICATION_MAIN(Application)` (from `xyo-system`) defines `main`: it
initializes the managed memory registry, then calls `Application::main`.

As a fabricare test project:

```json
{
	"name": "test.03",
	"make": "exe",
	"category": "test",
	"SPDX-License-Identifier": "Unlicense",
	"dependency": [
		"xyo-pixel32"
	]
}
```

with the source in `test/test.03.cpp`.

## 5. Conventions used by the whole library

- **`TPointer` owns, `Image *` borrows.** Functions that create an image or
  bitmap return `TPointer<Image>` / `TPointer<Bitmap>`. Functions that
  only use one take a raw `Image *` / `Bitmap *`; a `TPointer` converts to
  it implicitly, so pass the `TPointer` directly. Keep the `TPointer` alive
  while the raw pointer is used.
- **`nullptr` / `false` means failure.** No function throws on bad input
  or bad files (only `std::bad_alloc` can escape from very large
  allocations outside the PNG loaders). Check every returned pointer
  **before** passing it on: the processing functions do not check their
  `Image *` arguments for null.
- **New image or in place.** Functions that return `TPointer<Image>`
  (`resize`, `scale*`, `cut`, `wrap`, `wrapBox`, `kernel3X3`) leave the
  input unchanged. Functions that return `void` (`clear`, `copy`, `blend`,
  `draw*`, `average`, `colorRescale`, `noise*`, `backgroundAlpha*`) change
  their first argument.
- **Coordinates** are `long int`, `x` to the right, `y` **down**, origin at
  the top left corner. Rectangles are `x, y, width, height` and are clipped
  to the image; a rectangle completely outside does nothing.
- **Straight alpha.** `A = 255` opaque, `A = 0` transparent; colors are not
  multiplied by alpha in memory.
- **One thread per object.** An `Image` or `Bitmap` is used by one thread
  at a time. Different images can be processed on different threads; the
  predefined `Kernel3X3` objects are only read.
- `Image`, `Bitmap`, `Kernel3X3` and `IconItem` are not copyable or
  movable (`XYO_PLATFORM_DISALLOW_COPY_ASSIGN_MOVE`): copy pixels with
  `Process::copy` or `Process::cut`, kernels with `Kernel3X3::copy`.

## 6. Building without fabricare

`xyo-pixel32` has no amalgam file: compile every `.cpp` of
`source/XYO/Pixel32/` and `source/XYO/Pixel32/Process/` with your
sources, together with the amalgams of the XYO layers below (see the
`xyo-cryptography` getting started page for those), and link `libpng` and
`zlib`.

1. Put `source/` of `xyo-platform`, `xyo-managed-memory`,
   `xyo-data-structures`, `xyo-multithreading`, `xyo-encoding`,
   `xyo-system`, `xyo-cryptography` and `xyo-pixel32` on the include path,
   plus the folder of `png.h`.
2. Provide the configuration headers of the lower layers (see the
   `xyo-system` getting started page).
3. Define `XYO_PIXEL32_LIBRARY` and the `..._LIBRARY` macros of every
   layer below everywhere (plain static linking).
4. Link `png` and `z`; `pthread` on Linux.

Example on Linux, with the repositories side by side:

```bash
g++ -std=c++17 \
    -Ixyo-platform/source -Ixyo-managed-memory/source \
    -Ixyo-data-structures/source -Ixyo-multithreading/source \
    -Ixyo-encoding/source -Ixyo-system/source -Ixyo-cryptography/source \
    -Ixyo-pixel32/source \
    -DXYO_PLATFORM_LIBRARY -DXYO_MANAGEDMEMORY_LIBRARY \
    -DXYO_DATASTRUCTURES_LIBRARY -DXYO_MULTITHREADING_LIBRARY \
    -DXYO_ENCODING_LIBRARY -DXYO_SYSTEM_LIBRARY -DXYO_CRYPTOGRAPHY_LIBRARY \
    -DXYO_PIXEL32_LIBRARY \
    xyo-platform/source/XYO/Platform.Amalgam.cpp \
    xyo-managed-memory/source/XYO/ManagedMemory.Amalgam.cpp \
    xyo-data-structures/source/XYO/DataStructures.Amalgam.cpp \
    xyo-multithreading/source/XYO/Multithreading.Amalgam.cpp \
    xyo-encoding/source/XYO/Encoding.Amalgam.cpp \
    xyo-system/source/XYO/System.Amalgam.cpp \
    xyo-cryptography/source/XYO/Cryptography.Amalgam.cpp \
    xyo-pixel32/source/XYO/Pixel32/*.cpp \
    xyo-pixel32/source/XYO/Pixel32/Process/*.cpp \
    main.cpp -o main -lpng -lz -pthread
```

On Windows with MSVC also define `XYO_PLATFORM_COMPILE_STATIC`, add the
`include` folder of libpng / zlib, and link `libpng.lib` and `libz.lib`
(from `vendor-libpng` / `vendor-zlib`, or your own build).
