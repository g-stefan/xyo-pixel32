// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Bitmap.hpp>

namespace XYO::Pixel32 {

	// Largest header accepted on load (BITMAPV5HEADER)
	static const uint32_t bitmapMaxInfoHeaderSize = 124;

	static inline uint32_t paletteEntries(uint32_t bits) {
		if (bits == 1) {
			return 2;
		};
		if (bits == 4) {
			return 16;
		};
		if (bits == 8) {
			return 256;
		};
		return 0;
	};

	static inline uint64_t scanLine64(uint64_t width, uint64_t bits) {
		return ((width * bits + 31) / 32) * 4;
	};

	// Palette follows the info header
	static inline BitmapRGBA *bitmapPalette(BitmapImage *image) {
		return (BitmapRGBA *)(((uint8_t *)image) + sizeof(BitmapFileHeader) + image->ih.biSize);
	};

	// Rows are stored bottom-up, starting at bfOffBits
	static inline uint8_t *bitmapRow(BitmapImage *image, uint32_t y, uint32_t scanLine) {
		return ((uint8_t *)image) + image->fh.bfOffBits + (size_t)y * scanLine;
	};

	static inline bool isSameColor(const BitmapRGBA &a, const BitmapRGBA &b) {
		return (a.rgbBlue == b.rgbBlue) && (a.rgbGreen == b.rgbGreen) && (a.rgbRed == b.rgbRed) && (a.rgbAlpha == b.rgbAlpha);
	};

	// Exact match if present, else the nearest color
	static uint8_t findPaletteIndex(const BitmapRGBA *palette, uint32_t count, const BitmapRGBA &c, bool &found) {
		uint32_t index;
		uint32_t best = 0;
		uint32_t bestDistance = 0xFFFFFFFF;
		int32_t dr, dg, db, da;
		uint32_t distance;
		found = false;
		for (index = 0; index < count; ++index) {
			if (isSameColor(palette[index], c)) {
				found = true;
				return (uint8_t)index;
			};
			dr = (int32_t)palette[index].rgbRed - (int32_t)c.rgbRed;
			dg = (int32_t)palette[index].rgbGreen - (int32_t)c.rgbGreen;
			db = (int32_t)palette[index].rgbBlue - (int32_t)c.rgbBlue;
			da = (int32_t)palette[index].rgbAlpha - (int32_t)c.rgbAlpha;
			distance = (uint32_t)(dr * dr + dg * dg + db * db + da * da);
			if (distance < bestDistance) {
				bestDistance = distance;
				best = index;
			};
		};
		return (uint8_t)best;
	};

	// New zeroed image: file header, info header, full palette, pixels.
	// NULL if the size does not fit in a bitmap file.
	static BitmapImage *newBitmapImage(BitmapInfoHeaderV4 &ih) {
		uint64_t bits = (uint64_t)ih.biPlanes * ih.biBitCount;
		if ((ih.biWidth == 0) || (ih.biHeight == 0) || (ih.biWidth > 0x7FFFFFFF) || (ih.biHeight > 0x7FFFFFFF)) {
			return NULL;
		};
		uint64_t pixelSize = scanLine64(ih.biWidth, bits) * ih.biHeight;
		uint64_t offBits = sizeof(BitmapFileHeader) + ih.biSize + paletteEntries((uint32_t)bits) * sizeof(BitmapRGBA);
		uint64_t fileSize = offBits + pixelSize;
		if (fileSize > 0xFFFFFFFF) {
			return NULL;
		};

		ih.biSizeImage = (uint32_t)pixelSize;

		BitmapFileHeader fh;
		fh.bfType = XYO_PIXEL32_BITMAP_FILE_ID;
		fh.bfSize = (uint32_t)fileSize;
		fh.bfReserved1 = 0;
		fh.bfReserved2 = 0;
		fh.bfOffBits = (uint32_t)offBits;

		uint8_t *data = new uint8_t[(size_t)fileSize]();
		memcpy(data, &fh, sizeof(BitmapFileHeader));
		memcpy(data + sizeof(BitmapFileHeader), &ih, (ih.biSize < sizeof(ih)) ? ih.biSize : sizeof(ih));
		return (BitmapImage *)data;
	};

	static void initInfoHeader(BitmapInfoHeaderV4 &ih, uint32_t lx, uint32_t ly, uint16_t bitCount) {
		memset(&ih, 0, sizeof(ih));
		ih.biSize = sizeof(BitmapInfoHeader);
		ih.biWidth = lx;
		ih.biHeight = ly;
		ih.biPlanes = 1;
		ih.biBitCount = bitCount;
		ih.biCompression = BitmapCompression::RGB;
		ih.biXPelsPerMeter = 3778;
		ih.biYPelsPerMeter = 3778;
	};

	static TPointer<Bitmap> newImageBits(uint32_t lx, uint32_t ly, uint16_t bitCount) {
		BitmapInfoHeaderV4 ih;
		initInfoHeader(ih, lx, ly, bitCount);
		BitmapImage *image = newBitmapImage(ih);
		if (!image) {
			return nullptr;
		};
		return Bitmap::newImageOwner(image);
	};

	Bitmap::Bitmap() {
		image = NULL;
	};

	Bitmap::~Bitmap() {
		if (image) {
			delete[] ((uint8_t *)image);
		};
	};

	TPointer<Bitmap> Bitmap::newImage32Bits(uint32_t lx, uint32_t ly) {
		BitmapInfoHeaderV4 ih;
		initInfoHeader(ih, lx, ly, 32);
		ih.biSize = sizeof(BitmapInfoHeaderV4);
		ih.biCompression = BitmapCompression::BITFIELDS;
		ih.biRedMask = 0x00FF0000;
		ih.biGreenMask = 0x0000FF00;
		ih.biBlueMask = 0x000000FF;
		ih.biAlphaMask = 0xFF000000;
		ih.biCSType = BitmapLogicalColorSpace::sRGB;
		BitmapImage *image_ = newBitmapImage(ih);
		if (!image_) {
			return nullptr;
		};
		return newImageOwner(image_);
	};

	TPointer<Bitmap> Bitmap::newImage24Bits(uint32_t lx, uint32_t ly) {
		return newImageBits(lx, ly, 24);
	};

	TPointer<Bitmap> Bitmap::newImage8Bits(uint32_t lx, uint32_t ly) {
		return newImageBits(lx, ly, 8);
	};

	TPointer<Bitmap> Bitmap::newImage4Bits(uint32_t lx, uint32_t ly) {
		return newImageBits(lx, ly, 4);
	};

	TPointer<Bitmap> Bitmap::newImage1Bit(uint32_t lx, uint32_t ly) {
		return newImageBits(lx, ly, 1);
	};

	// Accept only bit fields that match the BitmapRGBA layout
	static bool isStandardMask32(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha) {
		return (red == 0x00FF0000) && (green == 0x0000FF00) && (blue == 0x000000FF) && ((alpha == 0xFF000000) || (alpha == 0));
	};

	// Loaded images are normalized: bottom-up rows, full palette right after
	// the info header, pixels right after the palette.
	TPointer<Bitmap> Bitmap::load(const char *name) {
		File in;
		BitmapFileHeader fh;
		uint8_t header[bitmapMaxInfoHeaderSize];
		BitmapInfoHeaderV4 ih;

		if (!in.openRead(name)) {
			return nullptr;
		};

		if (in.read(&fh, sizeof(fh)) != sizeof(fh)) {
			return nullptr;
		};
		if (fh.bfType != XYO_PIXEL32_BITMAP_FILE_ID) {
			return nullptr;
		};
		if (in.read(header, sizeof(BitmapInfoHeader)) != sizeof(BitmapInfoHeader)) {
			return nullptr;
		};
		memset(&ih, 0, sizeof(ih));
		memcpy(&ih, header, sizeof(BitmapInfoHeader));
		if ((ih.biSize < sizeof(BitmapInfoHeader)) || (ih.biSize > bitmapMaxInfoHeaderSize)) {
			return nullptr;
		};
		if (ih.biSize > sizeof(BitmapInfoHeader)) {
			if (in.read(header + sizeof(BitmapInfoHeader), ih.biSize - sizeof(BitmapInfoHeader)) != ih.biSize - sizeof(BitmapInfoHeader)) {
				return nullptr;
			};
			memcpy(&ih, header, (ih.biSize < sizeof(ih)) ? ih.biSize : sizeof(ih));
		};

		if ((ih.biBitCount == 0) && (ih.biPlanes != 0)) {
			ih.biBitCount = ih.biPlanes;
			ih.biPlanes = 1;
		};
		if (ih.biPlanes != 1) {
			return nullptr;
		};

		uint32_t bits = ih.biBitCount;
		if ((bits != 1) && (bits != 4) && (bits != 8) && (bits != 24) && (bits != 32)) {
			return nullptr;
		};

		if (ih.biCompression == BitmapCompression::BITFIELDS) {
			if (bits != 32) {
				return nullptr;
			};
			uint32_t mask[3];
			if (ih.biSize >= 52) {
				mask[0] = ih.biRedMask;
				mask[1] = ih.biGreenMask;
				mask[2] = ih.biBlueMask;
			} else {
				// BITMAPINFOHEADER: masks follow the header
				if (in.read(mask, sizeof(mask)) != sizeof(mask)) {
					return nullptr;
				};
			};
			if (!isStandardMask32(mask[0], mask[1], mask[2], (ih.biSize >= 56) ? ih.biAlphaMask : 0)) {
				return nullptr;
			};
			if (ih.biSize < 52) {
				// Masks are not kept after the header, same layout as RGB
				ih.biCompression = BitmapCompression::RGB;
			};
		} else if (ih.biCompression != BitmapCompression::RGB) {
			return nullptr;
		};

		int32_t signedHeight = (int32_t)ih.biHeight;
		bool topDown = (signedHeight < 0);
		if (signedHeight == (int32_t)0x80000000) {
			return nullptr;
		};
		uint32_t height = (uint32_t)(topDown ? -signedHeight : signedHeight);
		uint32_t width = ih.biWidth;
		if ((width == 0) || (width > 0x7FFFFFFF) || (height == 0)) {
			return nullptr;
		};

		uint32_t paletteCount = paletteEntries(bits);
		uint32_t paletteInFile = 0;
		if (paletteCount) {
			paletteInFile = ih.biClrUsed ? ih.biClrUsed : paletteCount;
			if (paletteInFile > paletteCount) {
				return nullptr;
			};
		};

		ih.biHeight = height;
		ih.biClrUsed = 0;
		ih.biClrImportant = 0;
		BitmapImage *image_ = newBitmapImage(ih);
		if (!image_) {
			return nullptr;
		};
		// Header copied with its original size, then fixed fields
		memcpy(((uint8_t *)image_) + sizeof(BitmapFileHeader), header, ih.biSize);
		memcpy(&image_->ih, &ih, sizeof(BitmapInfoHeader));

		TPointer<Bitmap> retV = newImageOwner(image_);

		if (paletteInFile) {
			if (!in.seekFromBegin(sizeof(BitmapFileHeader) + ih.biSize)) {
				return nullptr;
			};
			if (in.read(bitmapPalette(image_), paletteInFile * sizeof(BitmapRGBA)) != paletteInFile * sizeof(BitmapRGBA)) {
				return nullptr;
			};
		};

		if (fh.bfOffBits < sizeof(BitmapFileHeader) + ih.biSize + paletteInFile * sizeof(BitmapRGBA)) {
			return nullptr;
		};
		if (!in.seekFromBegin(fh.bfOffBits)) {
			return nullptr;
		};

		uint32_t scanLine_ = scanLine(image_->ih);
		uint32_t y;
		for (y = 0; y < height; ++y) {
			if (in.read(bitmapRow(image_, topDown ? (height - y - 1) : y, scanLine_), scanLine_) != scanLine_) {
				return nullptr;
			};
		};

		return retV;
	};

	bool Bitmap::save(const char *name) {
		File out;
		size_t b_sz;

		if (!image) {
			return false;
		};

		if (image->fh.bfSize == 0) {
			calculateImageSizeNoCompression(image->fh, image->ih);
		};

		if (out.openWrite(name)) {
			b_sz = out.write(image, image->fh.bfSize);
			out.close();
			if (b_sz == image->fh.bfSize) {
				return true;
			};
		};
		return false;
	};

	uint32_t Bitmap::scanLine(BitmapInfoHeader &bih) {
		return (uint32_t)scanLine64(bih.biWidth, (uint64_t)bih.biPlanes * bih.biBitCount);
	};

	void Bitmap::calculateImageSizeNoCompression(BitmapFileHeader &bfh, BitmapInfoHeader &bih) {
		uint32_t bmp_palette_size;
		uint32_t bmp_scan_line;

		bmp_scan_line = scanLine(bih);
		bmp_palette_size = paletteEntries(bih.biBitCount * bih.biPlanes) * sizeof(BitmapRGBA);

		bfh.bfOffBits = sizeof(BitmapFileHeader) + bih.biSize + bmp_palette_size;
		bfh.bfSize = bfh.bfOffBits + bmp_scan_line * bih.biHeight;

		bih.biSizeImage = bmp_scan_line * bih.biHeight;
	};

	BitmapRGBA *Bitmap::getRow32Bits(uint32_t y, uint32_t scanLine) {
		return (BitmapRGBA *)bitmapRow(image, image->ih.biHeight - y - 1, scanLine);
	};

	uint32_t Bitmap::getScanLine() {
		return scanLine(image->ih);
	};

	void Bitmap::setPixel32(uint32_t x, uint32_t y, BitmapRGBA &c) {
		((BitmapRGBA *)bitmapRow(image, y, scanLine(image->ih)))[x] = c;
	};

	void Bitmap::setPixel24(uint32_t x, uint32_t y, BitmapRGB &c) {
		((BitmapRGB *)bitmapRow(image, y, scanLine(image->ih)))[x] = c;
	};

	void Bitmap::setPixel8(uint32_t x, uint32_t y, uint8_t &c) {
		bitmapRow(image, y, scanLine(image->ih))[x] = c;
	};

	void Bitmap::setPixel4(uint32_t x, uint32_t y, uint8_t &c) {
		uint8_t *pixels = bitmapRow(image, y, scanLine(image->ih)) + (x >> 1);
		if (x & 0x0001) {
			*pixels = ((*pixels) & 0xF0) | (c & 0x0F);
		} else {
			*pixels = ((*pixels) & 0x0F) | ((c & 0x0F) << 4);
		};
	};

	void Bitmap::setPixel1(uint32_t x, uint32_t y, uint8_t &c) {
		uint8_t *pixels = bitmapRow(image, y, scanLine(image->ih)) + (x >> 3);
		uint8_t mask = (uint8_t)(0x80 >> (x & 0x07));
		if (c) {
			*pixels |= mask;
		} else {
			*pixels &= (uint8_t)~mask;
		};
	};

	void Bitmap::getPixel32(uint32_t x, uint32_t y, BitmapRGBA &c) {
		c = ((BitmapRGBA *)bitmapRow(image, y, scanLine(image->ih)))[x];
	};

	void Bitmap::getPixel24(uint32_t x, uint32_t y, BitmapRGB &c) {
		c = ((BitmapRGB *)bitmapRow(image, y, scanLine(image->ih)))[x];
	};

	void Bitmap::getPixel8(uint32_t x, uint32_t y, uint8_t &c) {
		c = bitmapRow(image, y, scanLine(image->ih))[x];
	};

	void Bitmap::getPixel4(uint32_t x, uint32_t y, uint8_t &c) {
		uint8_t pixels = bitmapRow(image, y, scanLine(image->ih))[x >> 1];
		if (x & 0x0001) {
			c = pixels & 0x0F;
		} else {
			c = (pixels >> 4) & 0x0F;
		};
	};

	void Bitmap::getPixel1(uint32_t x, uint32_t y, uint8_t &c) {
		uint8_t pixels = bitmapRow(image, y, scanLine(image->ih))[x >> 3];
		c = (pixels & (0x80 >> (x & 0x07))) ? 1 : 0;
	};

	void Bitmap::getPixelPal8(uint32_t x, uint32_t y, BitmapRGBA &c) {
		uint8_t c2;
		getPixel8(x, y, c2);
		c = bitmapPalette(image)[c2];
	};

	void Bitmap::getPixelPal4(uint32_t x, uint32_t y, BitmapRGBA &c) {
		uint8_t c2;
		getPixel4(x, y, c2);
		c = bitmapPalette(image)[c2];
	};

	void Bitmap::getPixelPal1(uint32_t x, uint32_t y, BitmapRGBA &c) {
		uint8_t c2;
		getPixel1(x, y, c2);
		c = bitmapPalette(image)[c2];
	};

	void Bitmap::setPixelPal8(uint32_t x, uint32_t y, BitmapRGBA &c) {
		bool found;
		uint8_t c2 = findPaletteIndex(bitmapPalette(image), 256, c, found);
		setPixel8(x, y, c2);
	};

	void Bitmap::setPixelPal4(uint32_t x, uint32_t y, BitmapRGBA &c) {
		bool found;
		uint8_t c2 = findPaletteIndex(bitmapPalette(image), 16, c, found);
		setPixel4(x, y, c2);
	};

	void Bitmap::setPixelPal1(uint32_t x, uint32_t y, BitmapRGBA &c) {
		bool found;
		uint8_t c2 = findPaletteIndex(bitmapPalette(image), 2, c, found);
		setPixel1(x, y, c2);
	};

	uint16_t Bitmap::getPaletteSize() {
		return (uint16_t)paletteEntries(image->ih.biBitCount * image->ih.biPlanes);
	};

	void Bitmap::getPaletteIndex(uint8_t index, BitmapRGBA &c) {
		c = bitmapPalette(image)[index];
	};

	void Bitmap::setPaletteIndex(uint8_t index, BitmapRGBA &c) {
		bitmapPalette(image)[index] = c;
	};

	bool Bitmap::getPaletteColor(uint8_t &index, BitmapRGBA &c) {
		bool found;
		index = findPaletteIndex(bitmapPalette(image), getPaletteSize(), c, found);
		return found;
	};

	uint32_t Bitmap::getWidth() {
		return image->ih.biWidth;
	};

	uint32_t Bitmap::getHeight() {
		return image->ih.biHeight;
	};

	uint16_t Bitmap::getPixelWidth() {
		return image->ih.biBitCount * image->ih.biPlanes;
	};

	bool Bitmap::isPalette() {
		return (getPixelWidth() < 16);
	};

	void Bitmap::getPixel32s(long int x, long int y, BitmapRGBA &c) {
		if ((x < 0) || (y < 0) || (x >= (long)image->ih.biWidth) || (y >= (long)image->ih.biHeight)) {
			c.rgbBlue = 0;
			c.rgbRed = 0;
			c.rgbGreen = 0;
			c.rgbAlpha = 0;
			return;
		};
		getPixel32((uint32_t)x, (uint32_t)y, c);
	};

	void Bitmap::setPixel32s(long int x, long int y, BitmapRGBA &c) {
		if ((x < 0) || (y < 0) || (x >= (long)image->ih.biWidth) || (y >= (long)image->ih.biHeight)) {
			return;
		};
		setPixel32((uint32_t)x, (uint32_t)y, c);
	};

	// 24 bits has no alpha, the pixel is opaque
	void Bitmap::getPixel24X(uint32_t x, uint32_t y, BitmapRGBA &c) {
		BitmapRGB *pixels = ((BitmapRGB *)bitmapRow(image, y, scanLine(image->ih))) + x;
		c.rgbBlue = pixels->rgbBlue;
		c.rgbRed = pixels->rgbRed;
		c.rgbGreen = pixels->rgbGreen;
		c.rgbAlpha = 0xFF;
	};

	// Palette entries have no alpha, the pixel is opaque
	void Bitmap::getPixel32X(uint32_t x, uint32_t y, BitmapRGBA &retV) {
		switch (getPixelWidth()) {
		case 1:
			getPixelPal1(x, y, retV);
			retV.rgbAlpha = 0xFF;
			return;
		case 4:
			getPixelPal4(x, y, retV);
			retV.rgbAlpha = 0xFF;
			return;
		case 8:
			getPixelPal8(x, y, retV);
			retV.rgbAlpha = 0xFF;
			return;
		case 24:
			getPixel24X(x, y, retV);
			return;
		case 32:
			getPixel32(x, y, retV);
			return;
		};
		retV.rgbBlue = 0;
		retV.rgbRed = 0;
		retV.rgbGreen = 0;
		retV.rgbAlpha = 0;
	};

	TPointer<Bitmap> Bitmap::convertTo32Bits() {
		if (getPixelWidth() == 32) {
			return this;
		};
		TPointer<Bitmap> retV = newImage32Bits(image->ih.biWidth, image->ih.biHeight);
		if (!retV) {
			return nullptr;
		};
		uint32_t scanLine_ = retV->getScanLine();
		uint32_t x;
		uint32_t y;
		BitmapRGBA *row;
		for (y = 0; y < image->ih.biHeight; ++y) {
			row = (BitmapRGBA *)bitmapRow(retV->image, y, scanLine_);
			for (x = 0; x < image->ih.biWidth; ++x) {
				getPixel32X(x, y, row[x]);
			};
		};
		return retV;
	};

	TPointer<Bitmap> Bitmap::newImageOwner(BitmapImage *image_) {
		TPointer<Bitmap> retV;
		retV.newMemory();
		retV->image = image_;
		return retV;
	};

	void Bitmap::swapRB32() {
		uint32_t y;
		uint32_t x;
		uint32_t scan_line;
		BitmapRGBA *pixels;
		uint8_t swap;
		scan_line = scanLine(image->ih);
		for (y = 0; y < image->ih.biHeight; ++y) {
			pixels = (BitmapRGBA *)bitmapRow(image, y, scan_line);
			for (x = 0; x < image->ih.biWidth; ++x) {
				swap = pixels[x].rgbBlue;
				pixels[x].rgbBlue = pixels[x].rgbRed;
				pixels[x].rgbRed = swap;
			};
		};
	};

	void Bitmap::setAlpha32(uint8_t alpha) {
		uint32_t y;
		uint32_t x;
		uint32_t scan_line;
		BitmapRGBA *pixels;
		scan_line = scanLine(image->ih);
		for (y = 0; y < image->ih.biHeight; ++y) {
			pixels = (BitmapRGBA *)bitmapRow(image, y, scan_line);
			for (x = 0; x < image->ih.biWidth; ++x) {
				pixels[x].rgbAlpha = alpha;
			};
		};
	};

};
