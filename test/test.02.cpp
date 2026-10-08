// Created by Grigore Stefan <g_stefan@yahoo.com>
// Public domain (Unlicense) <http://unlicense.org>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: Unlicense

#include <XYO/Pixel32.hpp>
#include <vector>

using namespace XYO::Pixel32;

// Regression tests for Image processing, Bitmap, PNG and ICO

// PNG files, one per color type / special case
static const uint8_t pngGrayAlpha[] = {
	0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A,0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52,
	0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x01,0x08,0x04,0x00,0x00,0x00,0x5E,0x2B,0xB7,
	0x01,0x00,0x00,0x00,0x0D,0x49,0x44,0x41,0x54,0x78,0x9C,0x63,0xE0,0x6A,0x38,0xF1,
	0x1F,0x00,0x04,0x3C,0x02,0x52,0x8F,0xAD,0xC8,0xEE,0x00,0x00,0x00,0x00,0x49,0x45,
	0x4E,0x44,0xAE,0x42,0x60,0x82,
};

static const uint8_t pngPaletteTRNS[] = {
	0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A,0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52,
	0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x01,0x08,0x03,0x00,0x00,0x00,0xC3,0xFC,0x8F,
	0xB8,0x00,0x00,0x00,0x06,0x50,0x4C,0x54,0x45,0xFF,0x00,0x00,0x00,0x00,0xFF,0x6C,
	0xA1,0xFD,0x8E,0x00,0x00,0x00,0x02,0x74,0x52,0x4E,0x53,0x80,0xFF,0x60,0x12,0xBA,
	0xFE,0x00,0x00,0x00,0x0B,0x49,0x44,0x41,0x54,0x78,0x9C,0x63,0x60,0x60,0x04,0x00,
	0x00,0x04,0x00,0x02,0xBF,0x7A,0x3F,0x4A,0x00,0x00,0x00,0x00,0x49,0x45,0x4E,0x44,
	0xAE,0x42,0x60,0x82,
};

static const uint8_t pngRGBTRNS[] = {
	0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A,0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52,
	0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x01,0x08,0x02,0x00,0x00,0x00,0x7B,0x40,0xE8,
	0xDD,0x00,0x00,0x00,0x06,0x74,0x52,0x4E,0x53,0x00,0x00,0x00,0xFF,0x00,0x00,0xD0,
	0x3E,0x33,0x7C,0x00,0x00,0x00,0x0F,0x49,0x44,0x41,0x54,0x78,0x9C,0x63,0x60,0xF8,
	0xCF,0xC0,0xC8,0xC4,0x0C,0x00,0x05,0x0C,0x01,0x06,0x89,0x78,0xD1,0xB6,0x00,0x00,
	0x00,0x00,0x49,0x45,0x4E,0x44,0xAE,0x42,0x60,0x82,
};

static const uint8_t pngGray1[] = {
	0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A,0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52,
	0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0xCB,0x7B,0xD2,
	0xEE,0x00,0x00,0x00,0x0A,0x49,0x44,0x41,0x54,0x78,0x9C,0x63,0xD8,0x00,0x00,0x00,
	0xB2,0x00,0xB1,0x55,0x0A,0xE8,0x2A,0x00,0x00,0x00,0x00,0x49,0x45,0x4E,0x44,0xAE,
	0x42,0x60,0x82,
};

static const uint8_t pngGrayTRNS[] = {
	0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A,0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52,
	0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x01,0x08,0x00,0x00,0x00,0x00,0xD1,0x49,0x20,
	0x56,0x00,0x00,0x00,0x02,0x74,0x52,0x4E,0x53,0x00,0x32,0xBE,0x44,0x9C,0xB8,0x00,
	0x00,0x00,0x0B,0x49,0x44,0x41,0x54,0x78,0x9C,0x63,0x30,0x4A,0x01,0x00,0x00,0xCB,
	0x00,0x97,0xCB,0xCA,0x8D,0x5B,0x00,0x00,0x00,0x00,0x49,0x45,0x4E,0x44,0xAE,0x42,
	0x60,0x82,
};

static const uint8_t pngRGB[] = {
	0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A,0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52,
	0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x01,0x08,0x02,0x00,0x00,0x00,0x7B,0x40,0xE8,
	0xDD,0x00,0x00,0x00,0x0F,0x49,0x44,0x41,0x54,0x78,0x9C,0x63,0x60,0x64,0x62,0xFE,
	0xF5,0xFB,0x0F,0x00,0x06,0x03,0x02,0xF8,0x4E,0x96,0xAD,0xB6,0x00,0x00,0x00,0x00,
	0x49,0x45,0x4E,0x44,0xAE,0x42,0x60,0x82,
};

static const uint8_t pngRGBA16[] = {
	0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A,0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52,
	0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x10,0x06,0x00,0x00,0x00,0x4F,0x85,0x18,
	0xCA,0x00,0x00,0x00,0x11,0x49,0x44,0x41,0x54,0x78,0x9C,0x63,0xF8,0xFF,0x9F,0x81,
	0x81,0x81,0xE1,0xFF,0x7F,0x00,0x11,0xF7,0x03,0xFD,0x9D,0xFA,0x67,0x26,0x00,0x00,
	0x00,0x00,0x49,0x45,0x4E,0x44,0xAE,0x42,0x60,0x82,
};

static const uint8_t pngInterlaced[] = {
	0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A,0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52,
	0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x03,0x08,0x06,0x00,0x00,0x01,0x21,0x2F,0x85,
	0x29,0x00,0x00,0x00,0x25,0x49,0x44,0x41,0x54,0x78,0x9C,0x15,0xC7,0xB1,0x0D,0x00,
	0x00,0x0C,0x83,0x30,0x36,0xDE,0xCB,0x89,0xF9,0x34,0x55,0x17,0x64,0x00,0x47,0x3F,
	0xD4,0xB5,0x8E,0xFC,0xE5,0x45,0x5C,0xE2,0x1A,0x77,0x1B,0x9A,0x0E,0xD7,0x34,0xC2,
	0xDE,0x0E,0x00,0x00,0x00,0x00,0x49,0x45,0x4E,0x44,0xAE,0x42,0x60,0x82,
};

static const uint8_t pngTooLarge[] = {
	0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A,0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52,
	0x00,0x1E,0x84,0x80,0x00,0x00,0x00,0x01,0x08,0x00,0x00,0x00,0x00,0x11,0xA8,0x81,
	0x95,0x00,0x00,0x00,0x0B,0x49,0x44,0x41,0x54,0x78,0x9C,0x63,0x60,0x40,0x03,0x00,
	0x00,0x11,0x00,0x01,0xEE,0x26,0x06,0x4F,0x00,0x00,0x00,0x00,0x49,0x45,0x4E,0x44,
	0xAE,0x42,0x60,0x82,
};

static const uint8_t pngTruncated[] = {
	0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A,0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52,
	0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x10,0x08,0x06,0x00,0x00,0x00,0x1F,0xF3,0xFF,
	0x61,0x00,0x00,0x00,0x54,0x49,0x44,0x41,0x54,0x78,0x9C,0x63,0x60,0x60,0x64,0x62,
	0x66,0x61,0x65,0x63,0xE7,0xE0,0xE4,0xE2,0xE6,0xE1,0xE5,0xE3,0x17,0x10,0x14,0x12,
	0x16,0x11,0x15,0x13,0x97,0x90,
};

class Application : public virtual IApplication {
		XYO_PLATFORM_DISALLOW_COPY_ASSIGN_MOVE(Application);

	public:
		int failed;

		inline Application() {
			failed = 0;
		};

		int main(int cmdN, char *cmdS[]);

		void check(bool condition, const char *name);

		void testCreate();
		void testMacro();
		void testCopy();
		void testBlend();
		void testCut();
		void testDrawRectangle();
		void testWrap();
		void testScale();
		void testKernel();
		void testColor();
		void testBitmapPalette();
		void testBitmapFile();
		void testPNG();
		void testIcon();
};

void Application::check(bool condition, const char *name) {
	printf("%s %s\r\n", condition ? "[ok]  " : "[FAIL]", name);
	// Keep the output if a later test crashes
	fflush(stdout);
	if (!condition) {
		++failed;
	};
};

static bool writeFile(const char *name, const void *data, size_t size) {
	File out;
	if (!out.openWrite(name)) {
		return false;
	};
	bool retV = (out.write(data, size) == size);
	out.close();
	return retV;
};

static bool readFile(const char *name, std::vector<uint8_t> &data) {
	int64_t size;
	data.clear();
	if (!Shell::getFileSize(name, size)) {
		return false;
	};
	data.resize((size_t)size);
	if (size == 0) {
		return true;
	};
	File in;
	if (!in.openRead(name)) {
		return false;
	};
	return in.read(data.data(), (size_t)size) == (size_t)size;
};

static uint16_t read16(const std::vector<uint8_t> &data, size_t offset) {
	return (uint16_t)(data[offset] | (data[offset + 1] << 8));
};

static uint32_t read32(const std::vector<uint8_t> &data, size_t offset) {
	return (uint32_t)data[offset] | ((uint32_t)data[offset + 1] << 8) | ((uint32_t)data[offset + 2] << 16) | ((uint32_t)data[offset + 3] << 24);
};

static void put16(std::vector<uint8_t> &data, uint16_t value) {
	data.push_back(value & 0xFF);
	data.push_back((value >> 8) & 0xFF);
};

static void put32(std::vector<uint8_t> &data, uint32_t value) {
	put16(data, value & 0xFFFF);
	put16(data, (value >> 16) & 0xFFFF);
};

// BMP file with BITMAPINFOHEADER, rows given in file order, already padded
static std::vector<uint8_t> makeBMP(int32_t width, int32_t height, uint16_t bits, uint32_t compression, const std::vector<uint8_t> &palette, uint32_t clrUsed, const std::vector<uint8_t> &pixels) {
	std::vector<uint8_t> data;
	uint32_t offBits = 14 + 40 + (uint32_t)palette.size();
	put16(data, 0x4D42);
	put32(data, offBits + (uint32_t)pixels.size());
	put16(data, 0);
	put16(data, 0);
	put32(data, offBits);
	put32(data, 40);
	put32(data, (uint32_t)width);
	put32(data, (uint32_t)height);
	put16(data, 1);
	put16(data, bits);
	put32(data, compression);
	put32(data, 0);
	put32(data, 3778);
	put32(data, 3778);
	put32(data, clrUsed);
	put32(data, 0);
	data.insert(data.end(), palette.begin(), palette.end());
	data.insert(data.end(), pixels.begin(), pixels.end());
	return data;
};

static TPointer<Image> makeImage(long int width, long int height, Pixel color) {
	TPointer<Image> image = Process::create(width, height);
	if (image) {
		Process::clear(image, color);
	};
	return image;
};

// Pixel (x, y) = index + 1, opaque
static TPointer<Image> makeIndexImage(long int width, long int height) {
	TPointer<Image> image = Process::create(width, height);
	long int x, y;
	for (y = 0; y < height; ++y) {
		for (x = 0; x < width; ++x) {
			image->pixel[y][x] = (Pixel)(y * width + x + 1);
		};
	};
	return image;
};

static bool isUniform(Image *image, Pixel color) {
	long int x, y;
	for (y = 0; y < image->height; ++y) {
		for (x = 0; x < image->width; ++x) {
			if (image->pixel[y][x] != color) {
				return false;
			};
		};
	};
	return true;
};

static bool isSameImage(Image *a, Image *b) {
	if (!a || !b) {
		return false;
	};
	if ((a->width != b->width) || (a->height != b->height)) {
		return false;
	};
	return memcmp(a->pixelMap, b->pixelMap, sizeof(Pixel) * a->width * a->height) == 0;
};

static bool isNear(uint32_t a, uint32_t b, uint32_t tolerance) {
	return (a > b) ? (a - b <= tolerance) : (b - a <= tolerance);
};

static bool isNearPixel(Pixel a, Pixel b, uint32_t tolerance) {
	return isNear(XYO_PIXEL32_R(a), XYO_PIXEL32_R(b), tolerance) &&
	       isNear(XYO_PIXEL32_G(a), XYO_PIXEL32_G(b), tolerance) &&
	       isNear(XYO_PIXEL32_B(a), XYO_PIXEL32_B(b), tolerance) &&
	       isNear(XYO_PIXEL32_A(a), XYO_PIXEL32_A(b), tolerance);
};

static long int countNotEqual(Image *image, Pixel color) {
	long int count = 0;
	long int x, y;
	for (y = 0; y < image->height; ++y) {
		for (x = 0; x < image->width; ++x) {
			if (image->pixel[y][x] != color) {
				++count;
			};
		};
	};
	return count;
};

static TPointer<Image> loadPNG(const char *name, const uint8_t *data, size_t size) {
	if (!writeFile(name, data, size)) {
		return nullptr;
	};
	return Process::pngLoad(name);
};

void Application::testCreate() {
	check(!Process::create(0, 5), "create: zero width");
	check(!Process::create(5, -1), "create: negative height");
	TPointer<Image> image = Process::create(3, 2);
	check(image && isUniform(image, 0), "create: zero initialized");
};

void Application::testMacro() {
	Pixel color = XYO_PIXEL32_PIXEL(9, 9, 9, 0x80);
	XYO_PIXEL32_CHANGE_RGB(color, 1, 2, 3);
	check(color == XYO_PIXEL32_PIXEL(1, 2, 3, 0x80), "XYO_PIXEL32_CHANGE_RGB");
};

void Application::testCopy() {
	TPointer<Image> source = makeIndexImage(4, 4);
	TPointer<Image> image = Process::create(4, 4);

	// Negative destination skips the first source column
	Process::copy(image, source, -1, 0, 0, 0, 4, 4);
	check(image->pixel[0][0] == source->pixel[0][1] && image->pixel[3][2] == source->pixel[3][3] && image->pixel[0][3] == 0, "copy: negative destination");

	// Source offset near the edge copies only what exists
	Process::clear(image, 0);
	Process::copy(image, source, 0, 0, 3, 3, 4, 4);
	check(image->pixel[0][0] == source->pixel[3][3] && countNotEqual(image, 0) == 1, "copy: source offset clipped");

	// Negative source offset moves the destination
	Process::clear(image, 0);
	Process::copy(image, source, 0, 0, -2, 0, 4, 1);
	check(image->pixel[0][2] == source->pixel[0][0] && image->pixel[0][3] == source->pixel[0][1] && image->pixel[0][0] == 0, "copy: negative source");

	// Outside
	Process::clear(image, 0);
	Process::copy(image, source, 4, 0, 0, 0, 4, 4);
	Process::copy(image, source, 0, 0, 0, 4, 4, 4);
	check(countNotEqual(image, 0) == 0, "copy: outside");

	// Overlapping copy on the same image
	TPointer<Image> row = makeIndexImage(4, 1);
	Process::copy(row, row, 1, 0, 0, 0, 3, 1);
	check(row->pixel[0][0] == 1 && row->pixel[0][1] == 1 && row->pixel[0][2] == 2 && row->pixel[0][3] == 3, "copy: overlap on x");
	TPointer<Image> column = makeIndexImage(1, 4);
	Process::copy(column, column, 0, 1, 0, 0, 1, 3);
	check(column->pixel[0][0] == 1 && column->pixel[1][0] == 1 && column->pixel[2][0] == 2 && column->pixel[3][0] == 3, "copy: overlap on y");
};

void Application::testBlend() {
	Pixel black = XYO_PIXEL32_PIXEL(0, 0, 0, 255);
	Pixel white = XYO_PIXEL32_PIXEL(255, 255, 255, 255);
	TPointer<Image> image = makeImage(4, 4, black);
	TPointer<Image> source = makeImage(2, 2, white);

	Process::blend(image, source, 0, 0, 1, 1, 4, 4);
	check(image->pixel[0][0] == white && countNotEqual(image, black) == 1, "blend: source offset clipped");

	Process::clear(image, black);
	Process::blend(image, source, -1, -1, 0, 0, 2, 2);
	check(image->pixel[0][0] == white && countNotEqual(image, black) == 1, "blend: negative destination");

	Process::clear(image, black);
	Process::blend(image, source, 3, 3, 0, 0, 2, 2);
	check(image->pixel[3][3] == white && countNotEqual(image, black) == 1, "blend: destination clipped");
};

void Application::testCut() {
	TPointer<Image> image = makeIndexImage(4, 4);
	TPointer<Image> part = Process::cut(image, -2, -2, 4, 4);
	check(part && part->width == 2 && part->height == 2 && part->pixel[1][1] == image->pixel[1][1], "cut: negative start");
	part = Process::cut(image, 3, 1, 4, 2);
	check(part && part->width == 1 && part->height == 2 && part->pixel[0][0] == image->pixel[1][3], "cut: clipped at the end");
	check(!Process::cut(image, 10, 0, 2, 2), "cut: outside");
	check(!Process::cut(image, 0, 0, 0, 5), "cut: empty");
};

void Application::testDrawRectangle() {
	// Blending once on a transparent pixel keeps the alpha
	Pixel color = XYO_PIXEL32_PIXEL(255, 0, 0, 128);
	TPointer<Image> image = Process::create(4, 4);

	Process::drawRectangle(image, 0, 0, 4, 0, color);
	Process::drawRectangle(image, 0, 3, 4, 0, color);
	Process::drawRectangle(image, 10, 10, 3, 3, color);
	Process::drawRectangle(image, 5, 0, 3, 3, color);
	Process::drawRectangle(image, 0, 5, 3, 3, color);
	Process::drawRectangle(image, -5, -5, 3, 3, color);
	check(countNotEqual(image, 0) == 0, "drawRectangle: empty or outside");

	Process::drawRectangle(image, 1, 1, 1, 1, color);
	check(image->pixel[1][1] == color && countNotEqual(image, 0) == 1, "drawRectangle: 1x1 blended once");

	Process::clear(image, 0);
	Process::drawRectangle(image, 0, 0, 4, 4, color);
	check(countNotEqual(image, 0) == 12 && image->pixel[0][0] == color && image->pixel[3][3] == color && image->pixel[1][1] == 0, "drawRectangle: outline");

	Process::clear(image, 0);
	Process::drawRectangle(image, 2, 2, 4, 4, color);
	check(countNotEqual(image, 0) == 3 && image->pixel[2][2] == color && image->pixel[2][3] == color && image->pixel[3][2] == color, "drawRectangle: clipped");

	Process::clear(image, 0);
	Process::drawRectangle(image, 0, 1, 4, 1, color);
	check(countNotEqual(image, 0) == 4 && image->pixel[1][0] == color && image->pixel[1][3] == color, "drawRectangle: one row");

	Process::clear(image, 0);
	Process::drawFilledRectangle(image, -2, -2, 3, 3, color);
	check(countNotEqual(image, 0) == 1 && image->pixel[0][0] == color, "drawFilledRectangle: negative start");

	Process::clear(image, 0);
	Process::drawFilledRectangle(image, 2, 1, 10, 2, color);
	check(countNotEqual(image, 0) == 4 && image->pixel[2][3] == color, "drawFilledRectangle: clipped");
};

void Application::testWrap() {
	TPointer<Image> image = makeIndexImage(5, 3);
	long int x, y;
	bool isOk;

	TPointer<Image> wrapped = Process::wrap(image, 2, 1);
	isOk = wrapped && wrapped->width == 5 && wrapped->height == 3;
	for (y = 0; isOk && (y < 3); ++y) {
		for (x = 0; x < 5; ++x) {
			isOk = isOk && (wrapped->pixel[y][x] == image->pixel[(y + 1) % 3][(x + 2) % 5]);
		};
	};
	check(isOk, "wrap: offset 2, 1");

	wrapped = Process::wrap(image, -1, 4);
	isOk = wrapped && wrapped->width == 5 && wrapped->height == 3;
	for (y = 0; isOk && (y < 3); ++y) {
		for (x = 0; x < 5; ++x) {
			isOk = isOk && (wrapped->pixel[y][x] == image->pixel[(y + 4) % 3][(x + 4) % 5]);
		};
	};
	check(isOk, "wrap: negative and large offset");

	TPointer<Image> box = Process::wrapBox(image, 2, 1);
	isOk = box && box->width == 9 && box->height == 5;
	for (y = 0; isOk && (y < 5); ++y) {
		for (x = 0; x < 9; ++x) {
			isOk = isOk && (box->pixel[y][x] == image->pixel[(y - 1 + 3) % 3][(x - 2 + 5) % 5]);
		};
	};
	check(isOk, "wrapBox: border 2, 1");

	box = Process::wrapBox(image, 7, 4);
	isOk = box && box->width == 19 && box->height == 11;
	for (y = 0; isOk && (y < 11); ++y) {
		for (x = 0; x < 19; ++x) {
			isOk = isOk && (box->pixel[y][x] == image->pixel[(y - 4 + 6) % 3][(x - 7 + 10) % 5]);
		};
	};
	check(isOk, "wrapBox: border larger than the image");
};

void Application::testScale() {
	Pixel color = XYO_PIXEL32_PIXEL(10, 100, 200, 255);
	TPointer<Image> image = makeImage(10, 10, color);
	TPointer<Image> result;

	// Only the height grows, used to recurse forever for heights below 16
	result = Process::resize(image, 10, 40);
	check(result && result->width == 10 && result->height == 40 && isUniform(result, color), "resize: 10x10 to 10x40");
	result = Process::scaleUp(image, 10, 40);
	check(result && result->width == 10 && result->height == 40, "scaleUp: height only");

	TPointer<Image> wide = makeImage(64, 8, color);
	result = Process::resize(wide, 48, 48);
	check(result && result->width == 48 && result->height == 48 && isUniform(result, color), "resize: 64x8 to 48x48");

	check(!Process::resize(image, 0, 5), "resize: zero size");
	check(!Process::scaleDown(image, 0, 0), "scaleDown: zero size");
	check(!Process::scaleUpBicubic(image, 5, 20), "scaleUpBicubic: smaller");

	// Edges must not fade to transparent
	TPointer<Image> small = makeImage(7, 5, color);
	result = Process::scaleUpBicubic(small, 23, 17);
	check(result && isUniform(result, color), "scaleUpBicubic: uniform stays uniform");
	result = Process::scaleUpBilinear(small, 23, 17);
	check(result && isUniform(result, color), "scaleUpBilinear: uniform stays uniform");
	result = Process::scaleUpNearestNeighbor(small, 23, 17);
	check(result && isUniform(result, color), "scaleUpNearestNeighbor: uniform stays uniform");
	result = Process::resize(small, 37, 29);
	check(result && isUniform(result, color), "resize: up, uniform stays uniform");
	TPointer<Image> large = makeImage(40, 40, color);
	result = Process::resize(large, 13, 7);
	check(result && result->width == 13 && result->height == 7 && isUniform(result, color), "resize: down, uniform stays uniform");

	// Width 1 used to divide 0 by 0
	TPointer<Image> line = makeImage(1, 3, color);
	result = Process::scaleUpBicubic(line, 1, 9);
	check(result && isUniform(result, color), "scaleUpBicubic: width 1");
	result = Process::scaleUpBilinear(line, 1, 9);
	check(result && isUniform(result, color), "scaleUpBilinear: width 1");

	// Grid points keep the source pixels
	TPointer<Image> grid = Process::create(4, 4);
	long int x, y;
	for (y = 0; y < 4; ++y) {
		for (x = 0; x < 4; ++x) {
			grid->pixel[y][x] = XYO_PIXEL32_PIXEL(x * 60, y * 60, (x + y) * 30, 255);
		};
	};
	bool isOk = true;
	result = Process::scaleUpBicubic(grid, 7, 7);
	for (y = 0; result && (y < 4); ++y) {
		for (x = 0; x < 4; ++x) {
			isOk = isOk && (result->pixel[y * 2][x * 2] == grid->pixel[y][x]);
		};
	};
	check(result && isOk, "scaleUpBicubic: grid points");
	isOk = true;
	result = Process::scaleUpBilinear(grid, 7, 7);
	for (y = 0; result && (y < 4); ++y) {
		for (x = 0; x < 4; ++x) {
			isOk = isOk && (result->pixel[y * 2][x * 2] == grid->pixel[y][x]);
		};
	};
	check(result && isOk, "scaleUpBilinear: grid points");
	result = Process::scaleUpNearestNeighbor(grid, 8, 8);
	check(result && result->pixel[0][0] == grid->pixel[0][0] && result->pixel[7][7] == grid->pixel[3][3], "scaleUpNearestNeighbor: corners");
};

void Application::testKernel() {
	Pixel color = XYO_PIXEL32_PIXEL(10, 100, 200, 255);
	TPointer<Image> image = makeImage(5, 5, color);
	TPointer<Image> result;

	result = Process::kernel3X3(image, Kernel3X3::blur);
	check(result && isUniform(result, color), "kernel3X3: blur uniform");
	result = Process::kernel3X3(image, Kernel3X3::gaussian);
	check(result && isUniform(result, color), "kernel3X3: gaussian uniform");
	result = Process::kernel3X3(image, Kernel3X3::sharpen);
	check(result && isUniform(result, color), "kernel3X3: sharpen uniform");

	// Zero sum kernels used to give alpha 0
	result = Process::kernel3X3(image, Kernel3X3::edgeDetection);
	check(result && isUniform(result, XYO_PIXEL32_PIXEL(0, 0, 0, 255)), "kernel3X3: edge detection keeps alpha");
	result = Process::kernel3X3(image, Kernel3X3::gradientDetectionV);
	check(result && isUniform(result, XYO_PIXEL32_PIXEL(0, 0, 0, 255)), "kernel3X3: gradient keeps alpha");

	TPointer<Image> step = makeImage(6, 3, XYO_PIXEL32_PIXEL(0, 0, 0, 255));
	Process::drawFilledRectangle(step, 3, 0, 3, 3, XYO_PIXEL32_PIXEL(255, 255, 255, 255));
	result = Process::kernel3X3(step, Kernel3X3::edgeDetection);
	check(result && result->pixel[1][3] == XYO_PIXEL32_PIXEL(255, 255, 255, 255) && result->pixel[1][0] == XYO_PIXEL32_PIXEL(0, 0, 0, 255), "kernel3X3: edge found");

	TPointer<Image> transparent = Process::create(4, 4);
	result = Process::kernel3X3(transparent, Kernel3X3::blur);
	check(result && isUniform(result, 0), "kernel3X3: transparent");
};

void Application::testColor() {
	TPointer<Image> image = Process::create(2, 1);
	image->pixel[0][0] = XYO_PIXEL32_PIXEL(0, 50, 10, 255);
	image->pixel[0][1] = XYO_PIXEL32_PIXEL(0, 50, 20, 255);
	Process::colorRescale(image);
	check(image->pixel[0][0] == XYO_PIXEL32_PIXEL(0, 50, 0, 255) && image->pixel[0][1] == XYO_PIXEL32_PIXEL(0, 50, 255, 255), "colorRescale: blue channel, constant channels kept");

	TPointer<Image> a = makeImage(4, 4, XYO_PIXEL32_PIXEL(100, 100, 100, 255));
	TPointer<Image> b = makeImage(2, 2, XYO_PIXEL32_PIXEL(200, 200, 200, 255));
	Process::average(a, b, 1, 1, 0);
	check(isUniform(a, XYO_PIXEL32_PIXEL(100, 100, 100, 255)), "average: zero divisor");
	Process::average(a, b, 1, 1, 2);
	check(a->pixel[1][1] == XYO_PIXEL32_PIXEL(150, 150, 150, 255) && a->pixel[2][2] == XYO_PIXEL32_PIXEL(100, 100, 100, 255), "average: smaller second image");

	TPointer<Image> c = Process::create(2, 1);
	c->pixel[0][1] = XYO_PIXEL32_PIXEL(9, 9, 9, 255);
	Process::backgroundAlpha(c, XYO_PIXEL32_PIXEL(1, 2, 3, 255));
	check(c->pixel[0][0] == XYO_PIXEL32_PIXEL(1, 2, 3, 0) && c->pixel[0][1] == XYO_PIXEL32_PIXEL(9, 9, 9, 255), "backgroundAlpha");
};

void Application::testBitmapPalette() {
	TPointer<Bitmap> bmp8 = Bitmap::newImage8Bits(2, 2);
	check(bmp8, "Bitmap: new 8 bits");
	if (!bmp8) {
		return;
	};
	BitmapRGBA color = {3, 2, 1, 0};
	uint8_t index = 0;
	check(!bmp8->getPaletteColor(index, color), "Bitmap: getPaletteColor missing color on 256 entries");
	bmp8->setPaletteIndex(5, color);
	check(bmp8->getPaletteColor(index, color) && index == 5, "Bitmap: getPaletteColor found");
	bmp8->setPixelPal8(1, 1, color);
	uint8_t c8 = 0;
	bmp8->getPixel8(1, 1, c8);
	check(c8 == 5, "Bitmap: setPixelPal8");

	TPointer<Bitmap> bmp4 = Bitmap::newImage4Bits(3, 1);
	BitmapRGBA entry;
	int k;
	for (k = 0; k < 16; ++k) {
		entry.rgbBlue = (uint8_t)(k * 16);
		entry.rgbGreen = (uint8_t)(k * 16);
		entry.rgbRed = (uint8_t)(k * 16);
		entry.rgbAlpha = 0;
		bmp4->setPaletteIndex((uint8_t)k, entry);
	};
	entry.rgbBlue = 50;
	entry.rgbGreen = 50;
	entry.rgbRed = 50;
	bmp4->setPixelPal4(2, 0, entry);
	bmp4->getPixel4(2, 0, c8);
	check(c8 == 3, "Bitmap: setPixelPal4 nearest color");

	TPointer<Bitmap> bmp1 = Bitmap::newImage1Bit(17, 2);
	bool isOk = true;
	uint32_t x;
	for (x = 0; x < 17; ++x) {
		c8 = (x % 3 == 0) ? 1 : 0;
		bmp1->setPixel1(x, 1, c8);
	};
	for (x = 0; x < 17; ++x) {
		bmp1->getPixel1(x, 1, c8);
		isOk = isOk && (c8 == ((x % 3 == 0) ? 1 : 0));
		bmp1->getPixel1(x, 0, c8);
		isOk = isOk && (c8 == 0);
	};
	check(isOk, "Bitmap: 1 bit pixels");

	check(!Bitmap::newImage32Bits(0x7FFFFFFF, 0x7FFFFFFF), "Bitmap: too large");
	check(!Bitmap::newImage8Bits(0, 3), "Bitmap: zero width");

	// 20 colors in 16 entries
	TPointer<Bitmap> bmp32 = Bitmap::newImage32Bits(20, 1);
	for (x = 0; x < 20; ++x) {
		entry.rgbBlue = (uint8_t)(x * 10);
		entry.rgbGreen = (uint8_t)(x * 10);
		entry.rgbRed = (uint8_t)(x * 10);
		entry.rgbAlpha = 255;
		bmp32->setPixel32(x, 0, entry);
	};
	TPointer<Bitmap> out4;
	TPointer<Bitmap> out1;
	bool noFreeColorsLeft = false;
	check(Process::bitmap32To4Alpha1(bmp32, out4, out1, 128, noFreeColorsLeft) && noFreeColorsLeft, "bitmap32To4Alpha1: palette full");
	isOk = true;
	for (x = 0; x < 20; ++x) {
		out4->getPixelPal4(x, 0, entry);
		if (x < 16) {
			isOk = isOk && (entry.rgbRed == x * 10);
		} else {
			isOk = isOk && (entry.rgbRed == 150);
		};
	};
	check(isOk, "bitmap32To4Alpha1: nearest color when full");
	check(Process::bitmap32To8Alpha1(bmp32, out4, out1, 128, noFreeColorsLeft) && !noFreeColorsLeft, "bitmap32To8Alpha1");

	// Palette images are opaque when converted
	TPointer<Image> image = Process::imageFromBitmap(bmp8);
	check(image && image->pixel[0][1] == XYO_PIXEL32_PIXEL(1, 2, 3, 255), "imageFromBitmap: 8 bits opaque");
	TPointer<Bitmap> converted = bmp8->convertTo32Bits();
	converted->getPixel32(1, 1, entry);
	check(entry.rgbRed == 1 && entry.rgbGreen == 2 && entry.rgbBlue == 3 && entry.rgbAlpha == 255, "convertTo32Bits: 8 bits opaque");
};

void Application::testBitmapFile() {
	TPointer<Image> image = Process::create(3, 2);
	image->pixel[0][0] = XYO_PIXEL32_PIXEL(255, 0, 0, 255);
	image->pixel[0][1] = XYO_PIXEL32_PIXEL(0, 255, 0, 128);
	image->pixel[0][2] = XYO_PIXEL32_PIXEL(0, 0, 255, 0);
	image->pixel[1][0] = XYO_PIXEL32_PIXEL(1, 2, 3, 255);
	image->pixel[1][1] = XYO_PIXEL32_PIXEL(4, 5, 6, 255);
	image->pixel[1][2] = XYO_PIXEL32_PIXEL(7, 8, 9, 255);

	TPointer<Bitmap> bmp;
	TPointer<Image> loaded;

	bmp = Process::toBitmap32(image);
	check(bmp && bmp->save("test.02.32.bmp"), "Bitmap: save 32 bits");
	bmp = Bitmap::load("test.02.32.bmp");
	loaded = Process::imageFromBitmap(bmp);
	check(isSameImage(loaded, image), "Bitmap: load 32 bits");

	bmp = Process::toBitmap24(image);
	check(bmp && bmp->save("test.02.24.bmp"), "Bitmap: save 24 bits");
	bmp = Bitmap::load("test.02.24.bmp");
	loaded = Process::imageFromBitmap(bmp);
	bool isOk = loaded && loaded->width == 3 && loaded->height == 2;
	long int x, y;
	for (y = 0; isOk && (y < 2); ++y) {
		for (x = 0; x < 3; ++x) {
			isOk = isOk && (loaded->pixel[y][x] == XYO_PIXEL32_RGB(image->pixel[y][x]));
		};
	};
	check(isOk, "Bitmap: load 24 bits, opaque");

	std::vector<uint8_t> data;
	std::vector<uint8_t> palette;
	std::vector<uint8_t> pixels;

	// Top-down 24 bits 2x2: red, blue / green, white
	pixels = {0, 0, 255, 255, 0, 0, 0, 0, 0, 255, 0, 255, 255, 255, 0, 0};
	data = makeBMP(2, -2, 24, 0, palette, 0, pixels);
	writeFile("test.02.topdown.bmp", data.data(), data.size());
	bmp = Bitmap::load("test.02.topdown.bmp");
	loaded = Process::imageFromBitmap(bmp);
	check(loaded && loaded->pixel[0][0] == XYO_PIXEL32_PIXEL(255, 0, 0, 255) && loaded->pixel[0][1] == XYO_PIXEL32_PIXEL(0, 0, 255, 255) && loaded->pixel[1][0] == XYO_PIXEL32_PIXEL(0, 255, 0, 255) && loaded->pixel[1][1] == XYO_PIXEL32_PIXEL(255, 255, 255, 255), "Bitmap: load top-down");
	check(bmp && bmp->save("test.02.topdown.saved.bmp") && isSameImage(Process::imageFromBitmap(Bitmap::load("test.02.topdown.saved.bmp")), loaded), "Bitmap: save loaded top-down");

	// 8 bits with a 2 entries palette, bottom-up: row 0 (bottom) = 1, 0
	palette = {10, 20, 30, 0, 40, 50, 60, 0};
	pixels = {1, 0, 0, 0, 0, 1, 0, 0};
	data = makeBMP(2, 2, 8, 0, palette, 2, pixels);
	writeFile("test.02.8.bmp", data.data(), data.size());
	bmp = Bitmap::load("test.02.8.bmp");
	loaded = Process::imageFromBitmap(bmp);
	check(loaded && loaded->pixel[1][0] == XYO_PIXEL32_PIXEL(60, 50, 40, 255) && loaded->pixel[1][1] == XYO_PIXEL32_PIXEL(30, 20, 10, 255) && loaded->pixel[0][1] == XYO_PIXEL32_PIXEL(60, 50, 40, 255), "Bitmap: load 8 bits, short palette");

	// Invalid files
	palette.clear();
	pixels = {0, 0, 0};
	data = makeBMP(100, 100, 24, 0, palette, 0, pixels);
	writeFile("test.02.short.bmp", data.data(), data.size());
	check(!Bitmap::load("test.02.short.bmp"), "Bitmap: truncated file");
	data = makeBMP(0x7FFFFFFF, 0x7FFFFFFF, 32, 0, palette, 0, pixels);
	writeFile("test.02.large.bmp", data.data(), data.size());
	check(!Bitmap::load("test.02.large.bmp"), "Bitmap: too large");
	data = makeBMP(2, 2, 8, 1, palette, 0, pixels);
	writeFile("test.02.rle.bmp", data.data(), data.size());
	check(!Bitmap::load("test.02.rle.bmp"), "Bitmap: compressed not supported");
	data.resize(20);
	writeFile("test.02.header.bmp", data.data(), data.size());
	check(!Bitmap::load("test.02.header.bmp"), "Bitmap: header only");
	check(!Bitmap::load("test.02.missing.bmp"), "Bitmap: missing file");
};

void Application::testPNG() {
	TPointer<Image> image = Process::create(3, 2);
	image->pixel[0][0] = XYO_PIXEL32_PIXEL(255, 0, 0, 255);
	image->pixel[0][1] = XYO_PIXEL32_PIXEL(0, 255, 0, 128);
	image->pixel[0][2] = XYO_PIXEL32_PIXEL(0, 0, 255, 1);
	image->pixel[1][0] = XYO_PIXEL32_PIXEL(1, 2, 3, 255);
	image->pixel[1][1] = XYO_PIXEL32_PIXEL(4, 5, 6, 200);
	image->pixel[1][2] = XYO_PIXEL32_PIXEL(7, 8, 9, 255);

	check(Process::pngSave(image, "test.02.png"), "PNG: save");
	TPointer<Image> loaded = Process::pngLoad("test.02.png");
	check(isSameImage(loaded, image), "PNG: load");

	TPointer<Bitmap> bmp = Process::bitmap32LoadPNG("test.02.png");
	check(isSameImage(Process::imageFromBitmap(bmp), image), "PNG: bitmap32LoadPNG");
	check(Process::bitmap32SavePNG(bmp, "test.02.bitmap.png"), "PNG: bitmap32SavePNG");
	check(isSameImage(Process::pngLoad("test.02.bitmap.png"), image), "PNG: bitmap32SavePNG content");
	check(isSameImage(Process::imageFromBitmap(bmp), image), "PNG: bitmap32SavePNG keeps the bitmap");

	loaded = loadPNG("test.02.ga.png", pngGrayAlpha, sizeof(pngGrayAlpha));
	check(loaded && loaded->width == 2 && isNearPixel(loaded->pixel[0][0], XYO_PIXEL32_PIXEL(10, 10, 10, 128), 1) && loaded->pixel[0][1] == XYO_PIXEL32_PIXEL(200, 200, 200, 255), "PNG: gray alpha");

	loaded = loadPNG("test.02.palette.png", pngPaletteTRNS, sizeof(pngPaletteTRNS));
	check(loaded && isNearPixel(loaded->pixel[0][0], XYO_PIXEL32_PIXEL(255, 0, 0, 128), 1) && loaded->pixel[0][1] == XYO_PIXEL32_PIXEL(0, 0, 255, 255), "PNG: palette with transparency");

	loaded = loadPNG("test.02.rgbtrns.png", pngRGBTRNS, sizeof(pngRGBTRNS));
	check(loaded && XYO_PIXEL32_A(loaded->pixel[0][0]) == 0 && loaded->pixel[0][1] == XYO_PIXEL32_PIXEL(1, 2, 3, 255), "PNG: rgb with transparency");

	loaded = loadPNG("test.02.gray1.png", pngGray1, sizeof(pngGray1));
	Pixel white = XYO_PIXEL32_PIXEL(255, 255, 255, 255);
	Pixel black = XYO_PIXEL32_PIXEL(0, 0, 0, 255);
	check(loaded && loaded->width == 8 && loaded->pixel[0][0] == white && loaded->pixel[0][1] == black && loaded->pixel[0][2] == white && loaded->pixel[0][3] == white && loaded->pixel[0][4] == black && loaded->pixel[0][7] == black, "PNG: gray 1 bit");

	loaded = loadPNG("test.02.graytrns.png", pngGrayTRNS, sizeof(pngGrayTRNS));
	check(loaded && XYO_PIXEL32_A(loaded->pixel[0][0]) == 0 && loaded->pixel[0][1] == XYO_PIXEL32_PIXEL(100, 100, 100, 255), "PNG: gray with transparency");

	loaded = loadPNG("test.02.rgb.png", pngRGB, sizeof(pngRGB));
	check(loaded && loaded->pixel[0][0] == XYO_PIXEL32_PIXEL(1, 2, 3, 255) && loaded->pixel[0][1] == XYO_PIXEL32_PIXEL(250, 251, 252, 255), "PNG: rgb");

	loaded = loadPNG("test.02.rgba16.png", pngRGBA16, sizeof(pngRGBA16));
	check(loaded && loaded->pixel[0][0] == XYO_PIXEL32_PIXEL(255, 0, 0, 255), "PNG: 16 bits");

	loaded = loadPNG("test.02.interlaced.png", pngInterlaced, sizeof(pngInterlaced));
	bool isOk = loaded && loaded->width == 3 && loaded->height == 3;
	long int x, y;
	for (y = 0; isOk && (y < 3); ++y) {
		for (x = 0; x < 3; ++x) {
			isOk = isOk && (loaded->pixel[y][x] == XYO_PIXEL32_PIXEL(x * 80, y * 80, 7, 255));
		};
	};
	check(isOk, "PNG: interlaced");

	// These used to abort the process
	check(!loadPNG("test.02.truncated.png", pngTruncated, sizeof(pngTruncated)), "PNG: truncated file");
	check(!loadPNG("test.02.large.png", pngTooLarge, sizeof(pngTooLarge)), "PNG: too large");
	check(!Process::bitmap32LoadPNG("test.02.truncated.png"), "PNG: bitmap32LoadPNG truncated file");
	check(!Process::pngLoad("test.02.missing.png"), "PNG: missing file");
};

void Application::testIcon() {
	std::vector<uint8_t> data;
	size_t k;
	bool isOk;

	// Top row red, the rest green
	TPointer<Image> image = makeImage(16, 16, XYO_PIXEL32_PIXEL(0, 255, 0, 255));
	Process::drawFilledRectangle(image, 0, 0, 16, 1, XYO_PIXEL32_PIXEL(255, 0, 0, 255));

	TDoubleEndedQueue<TPointer<IconItem>> iconList;
	TPointer<IconItem> iconItem;
	iconItem.newMemory();
	iconItem->bmp = Process::toBitmap32(image);
	iconItem->mask = Process::alphaToBitmap1(image, 128);
	iconList.push(iconItem);
	check(Process::generateIcon(iconList, "test.02.ico"), "ICO: generateIcon");
	isOk = readFile("test.02.ico", data) && data.size() == 6 + 16 + 40 + 16 * 16 * 4 + 4 * 16;
	isOk = isOk && read16(data, 0) == 0 && read16(data, 2) == 1 && read16(data, 4) == 1;
	isOk = isOk && data[6] == 16 && data[7] == 16 && read16(data, 12) == 32 && read32(data, 14) == 40 + 16 * 16 * 4 + 4 * 16 && read32(data, 18) == 22;
	check(isOk, "ICO: directory");
	isOk = isOk && read32(data, 22) == 40 && read32(data, 22 + 8) == 32 && read16(data, 22 + 14) == 32;
	check(isOk, "ICO: BITMAPINFOHEADER");
	// Rows are bottom-up: the last row is the top one, BGRA
	size_t pixels = 22 + 40;
	isOk = isOk && data[pixels + 0] == 0 && data[pixels + 1] == 255 && data[pixels + 2] == 0 && data[pixels + 3] == 255;
	size_t top = pixels + 15 * 16 * 4 + 15 * 4;
	isOk = isOk && data[top + 0] == 0 && data[top + 1] == 0 && data[top + 2] == 255 && data[top + 3] == 255;
	for (k = pixels + 16 * 16 * 4; isOk && (k < data.size()); ++k) {
		isOk = (data[k] == 0);
	};
	check(isOk, "ICO: pixels and mask");

	TPointer<Image> big = makeImage(300, 300, 0);
	iconItem.newMemory();
	iconItem->bmp = Process::toBitmap32(big);
	iconItem->mask = Process::alphaToBitmap1(big, 128);
	iconList.push(iconItem);
	check(!Process::generateIcon(iconList, "test.02.big.ico"), "ICO: larger than 256");

	// Wide image used to recurse forever
	TPointer<Image> wide = makeImage(64, 8, XYO_PIXEL32_PIXEL(0, 0, 255, 255));
	Process::pngSave(wide, "test.02.wide.png");
	check(Process::pngToIcon("test.02.wide.png", "test.02.wide.ico", 128, false, 0), "ICO: pngToIcon wide image");
	isOk = readFile("test.02.wide.ico", data) && read16(data, 4) == 4;
	uint32_t offset = 6 + 4 * 16;
	static const uint8_t size[4] = {16, 24, 32, 48};
	for (k = 0; isOk && (k < 4); ++k) {
		uint32_t entrySize = read32(data, 6 + k * 16 + 8);
		uint32_t maskScan = ((size[k] + 31) / 32) * 4;
		isOk = data[6 + k * 16] == size[k] && data[6 + k * 16 + 1] == size[k];
		isOk = isOk && entrySize == 40 + size[k] * size[k] * 4 + maskScan * size[k];
		isOk = isOk && read32(data, 6 + k * 16 + 12) == offset;
		isOk = isOk && read32(data, offset) == 40 && read32(data, offset + 8) == (uint32_t)size[k] * 2;
		offset += entrySize;
	};
	check(isOk && offset == data.size(), "ICO: pngToIcon entries");

	// The color bitmap keeps the smooth alpha
	TPointer<Image> soft = makeImage(16, 16, XYO_PIXEL32_PIXEL(10, 20, 30, 200));
	Process::pngSave(soft, "test.02.soft.png");
	TDynamicArray<String> fileList;
	fileList[0] = "test.02.soft.png";
	check(Process::pngToIcon(fileList, "test.02.soft.ico", 128, true, 0), "ICO: pngToIcon list");
	isOk = readFile("test.02.soft.ico", data) && data.size() == 6 + 16 + 40 + 16 * 16 * 4 + 4 * 16;
	check(isOk && data[22 + 40 + 3] == 200 && data[22 + 40 + 2] == 10, "ICO: pngToIcon list keeps alpha");
};

struct TestGroup {
		const char *name;
		void (Application::*test)();
};

static const TestGroup testGroup[] = {
    {"create", &Application::testCreate},
    {"macro", &Application::testMacro},
    {"copy", &Application::testCopy},
    {"blend", &Application::testBlend},
    {"cut", &Application::testCut},
    {"drawRectangle", &Application::testDrawRectangle},
    {"wrap", &Application::testWrap},
    {"scale", &Application::testScale},
    {"kernel", &Application::testKernel},
    {"color", &Application::testColor},
    {"bitmapPalette", &Application::testBitmapPalette},
    {"bitmapFile", &Application::testBitmapFile},
    {"png", &Application::testPNG},
    {"icon", &Application::testIcon}};

// Optional argument: run only the named test group
int Application::main(int cmdN, char *cmdS[]) {
	try {
		size_t k;
		for (k = 0; k < sizeof(testGroup) / sizeof(testGroup[0]); ++k) {
			if ((cmdN > 1) && (strcmp(cmdS[1], testGroup[k].name) != 0)) {
				continue;
			};
			(this->*(testGroup[k].test))();
		};

		printf("%s\r\n", failed ? "Failed." : "Done.");
		return failed ? 1 : 0;
	} catch (const std::exception &e) {
		printf("* Error: %s\n", e.what());
	} catch (...) {
		printf("* Error: Unknown\n");
	};

	return 1;
};

XYO_APPLICATION_MAIN(Application);
