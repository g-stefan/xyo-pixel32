// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	// Index of the color in the first count palette entries (rgb only),
	// or of the nearest one if not present
	static uint8_t findColorRGB(Bitmap *bmp, int count, BitmapRGBA &c, bool &found) {
		BitmapRGBA cx32;
		int k;
		int best = 0;
		int32_t bestDistance = 0x7FFFFFFF;
		int32_t dr, dg, db, distance;
		found = false;
		for (k = 0; k < count; ++k) {
			bmp->getPaletteIndex((uint8_t)k, cx32);
			if ((cx32.rgbBlue == c.rgbBlue) && (cx32.rgbGreen == c.rgbGreen) && (cx32.rgbRed == c.rgbRed)) {
				found = true;
				return (uint8_t)k;
			};
			dr = (int32_t)cx32.rgbRed - (int32_t)c.rgbRed;
			dg = (int32_t)cx32.rgbGreen - (int32_t)c.rgbGreen;
			db = (int32_t)cx32.rgbBlue - (int32_t)c.rgbBlue;
			distance = dr * dr + dg * dg + db * db;
			if (distance < bestDistance) {
				bestDistance = distance;
				best = k;
			};
		};
		return (uint8_t)best;
	};

	// Build the palette from the image colors, when it is full use the nearest color
	static bool bitmap32ToPalette(Bitmap *inBitmap32, Bitmap *outBitmap, int paletteSize, bool &noFreeColorsLeft) {
		uint32_t lx = inBitmap32->getWidth();
		uint32_t ly = inBitmap32->getHeight();
		uint32_t kx, ky;
		BitmapRGBA c32;
		uint8_t index;
		int used = 0;
		bool found;

		for (ky = 0; ky < ly; ky++) {
			for (kx = 0; kx < lx; kx++) {
				inBitmap32->getPixel32(kx, ky, c32);
				index = findColorRGB(outBitmap, used, c32, found);
				if (!found) {
					if (used < paletteSize) {
						index = (uint8_t)used;
						c32.rgbAlpha = 0;
						outBitmap->setPaletteIndex(index, c32);
						++used;
					} else {
						noFreeColorsLeft = true;
					};
				};
				if (paletteSize == 256) {
					outBitmap->setPixel8(kx, ky, index);
				} else {
					outBitmap->setPixel4(kx, ky, index);
				};
			};
		};
		return true;
	};

	bool bitmap32Alpha1(Bitmap *inBitmap32, TPointer<Bitmap> &outBitmap1, int level) {
		if (inBitmap32->getPixelWidth() == 32) {
			uint32_t lx, ly;

			lx = inBitmap32->getWidth();
			ly = inBitmap32->getHeight();

			outBitmap1 = Bitmap::newImage1Bit(lx, ly);
			if (!outBitmap1) {
				return false;
			};

			uint32_t kx, ky;
			BitmapRGBA c32;
			uint8_t c8;

			c32.rgbBlue = 0;
			c32.rgbGreen = 0;
			c32.rgbRed = 0;
			c32.rgbAlpha = 0;
			outBitmap1->setPaletteIndex(0, c32);
			c32.rgbBlue = 255;
			c32.rgbGreen = 255;
			c32.rgbRed = 255;
			c32.rgbAlpha = 0;
			outBitmap1->setPaletteIndex(1, c32);

			for (ky = 0; ky < ly; ky++) {
				for (kx = 0; kx < lx; kx++) {
					inBitmap32->getPixel32(kx, ky, c32);
					c8 = (c32.rgbAlpha < level) ? 1 : 0;
					outBitmap1->setPixel1(kx, ky, c8);
				};
			};

			return true;
		};
		return false;
	};

	bool bitmap32To24Alpha8(Bitmap *inBitmap32, TPointer<Bitmap> &outBitmap24, TPointer<Bitmap> &outBitmap8) {
		if (inBitmap32->getPixelWidth() == 32) {
			uint32_t lx, ly;

			lx = inBitmap32->getWidth();
			ly = inBitmap32->getHeight();

			outBitmap24 = Bitmap::newImage24Bits(lx, ly);
			outBitmap8 = Bitmap::newImage8Bits(lx, ly);
			if (!outBitmap24 || !outBitmap8) {
				return false;
			};

			uint32_t kx, ky;
			BitmapRGBA c32;
			BitmapRGB c24;
			uint8_t c8;

			for (kx = 0; kx < 256; kx++) {
				c32.rgbBlue = (uint8_t)kx;
				c32.rgbGreen = (uint8_t)kx;
				c32.rgbRed = (uint8_t)kx;
				c32.rgbAlpha = 0;
				outBitmap8->setPaletteIndex((uint8_t)kx, c32);
			};

			for (ky = 0; ky < ly; ky++) {
				for (kx = 0; kx < lx; kx++) {
					inBitmap32->getPixel32(kx, ky, c32);
					c24.rgbBlue = c32.rgbBlue;
					c24.rgbGreen = c32.rgbGreen;
					c24.rgbRed = c32.rgbRed;
					outBitmap24->setPixel24(kx, ky, c24);
					c8 = c32.rgbAlpha;
					outBitmap8->setPixel8(kx, ky, c8);
				};
			};

			return true;
		};

		return false;
	};

	bool bitmap32To8Alpha1(Bitmap *inBitmap32, TPointer<Bitmap> &outBitmap8, TPointer<Bitmap> &outBitmap1, int level, bool &noFreeColorsLeft) {
		noFreeColorsLeft = false;

		if (inBitmap32->getPixelWidth() == 32) {
			outBitmap8 = Bitmap::newImage8Bits(inBitmap32->getWidth(), inBitmap32->getHeight());
			if (!outBitmap8) {
				return false;
			};
			bitmap32ToPalette(inBitmap32, outBitmap8, 256, noFreeColorsLeft);
			return bitmap32Alpha1(inBitmap32, outBitmap1, level);
		};

		return false;
	};

	bool bitmap32To4Alpha1(Bitmap *inBitmap32, TPointer<Bitmap> &outBitmap4, TPointer<Bitmap> &outBitmap1, int level, bool &noFreeColorsLeft) {
		noFreeColorsLeft = false;

		if (inBitmap32->getPixelWidth() == 32) {
			outBitmap4 = Bitmap::newImage4Bits(inBitmap32->getWidth(), inBitmap32->getHeight());
			if (!outBitmap4) {
				return false;
			};
			bitmap32ToPalette(inBitmap32, outBitmap4, 16, noFreeColorsLeft);
			return bitmap32Alpha1(inBitmap32, outBitmap1, level);
		};
		return false;
	};

	TPointer<Bitmap> alphaToBitmap8(Image *inImage) {
		uint32_t lx, ly;

		lx = inImage->width;
		ly = inImage->height;
		uint8_t c8;

		TPointer<Bitmap> outBitmap8 = Bitmap::newImage8Bits(lx, ly);
		if (!outBitmap8) {
			return nullptr;
		};
		uint32_t x, y;
		int palleteIndex;
		BitmapRGBA palleteColor;
		for (palleteIndex = 0; palleteIndex < 256; ++palleteIndex) {
			palleteColor.rgbBlue = 0x00;
			palleteColor.rgbGreen = 0x00;
			palleteColor.rgbRed = 0x00;
			palleteColor.rgbAlpha = (uint8_t)palleteIndex;
			outBitmap8->setPaletteIndex((uint8_t)palleteIndex, palleteColor);
		};

		for (y = 0; y < ly; ++y) {
			for (x = 0; x < lx; ++x) {
				c8 = XYO_PIXEL32_A(inImage->pixel[ly - y - 1][x]);
				outBitmap8->setPixel8(x, y, c8);
			};
		};
		return outBitmap8;
	};

	TPointer<Bitmap> alphaToBitmap1(Image *inImage, int level) {
		uint32_t lx, ly;

		lx = inImage->width;
		ly = inImage->height;
		BitmapRGBA palleteColor;

		TPointer<Bitmap> outBitmap1;

		outBitmap1 = Bitmap::newImage1Bit(lx, ly);
		if (!outBitmap1) {
			return nullptr;
		};
		palleteColor.rgbBlue = 0x00;
		palleteColor.rgbGreen = 0x00;
		palleteColor.rgbRed = 0x00;
		palleteColor.rgbAlpha = 0x00;
		outBitmap1->setPaletteIndex(0, palleteColor);
		palleteColor.rgbBlue = 0xFF;
		palleteColor.rgbGreen = 0xFF;
		palleteColor.rgbRed = 0xFF;
		palleteColor.rgbAlpha = 0x00;
		outBitmap1->setPaletteIndex(1, palleteColor);

		uint32_t x, y;
		uint8_t cx;

		for (y = 0; y < ly; ++y) {
			for (x = 0; x < lx; ++x) {
				cx = (XYO_PIXEL32_A(inImage->pixel[ly - y - 1][x]) < (uint32_t)level) ? 1 : 0;
				outBitmap1->setPixel1(x, y, cx);
			};
		};

		return outBitmap1;
	};

	TPointer<Bitmap> toBitmap24(Image *inImage) {
		uint32_t lx, ly;

		lx = inImage->width;
		ly = inImage->height;

		TPointer<Bitmap> outBitmap24 = Bitmap::newImage24Bits(lx, ly);
		if (!outBitmap24) {
			return nullptr;
		};
		uint32_t x, y, cx;
		BitmapRGB color;
		for (y = 0; y < ly; ++y) {
			for (x = 0; x < lx; ++x) {
				cx = inImage->pixel[ly - y - 1][x];
				color.rgbRed = XYO_PIXEL32_R(cx);
				color.rgbGreen = XYO_PIXEL32_G(cx);
				color.rgbBlue = XYO_PIXEL32_B(cx);
				outBitmap24->setPixel24(x, y, color);
			};
		};
		return outBitmap24;
	};

	TPointer<Bitmap> toBitmap32(Image *inImage) {
		uint32_t lx, ly;

		lx = inImage->width;
		ly = inImage->height;

		TPointer<Bitmap> outBitmap32 = Bitmap::newImage32Bits(lx, ly);
		if (!outBitmap32) {
			return nullptr;
		};
		uint32_t x, y, cx;
		uint32_t scanLine = outBitmap32->getScanLine();
		BitmapRGBA *row;
		for (y = 0; y < ly; ++y) {
			// getRow32Bits counts rows from the top, same as the image
			row = outBitmap32->getRow32Bits(y, scanLine);
			for (x = 0; x < lx; ++x) {
				cx = inImage->pixel[y][x];
				row[x].rgbRed = XYO_PIXEL32_R(cx);
				row[x].rgbGreen = XYO_PIXEL32_G(cx);
				row[x].rgbBlue = XYO_PIXEL32_B(cx);
				row[x].rgbAlpha = XYO_PIXEL32_A(cx);
			};
		};
		return outBitmap32;
	};

	TPointer<Image> imageFromBitmap(Bitmap *bmp) {
		if (!bmp || !bmp->getBitmapImage()) {
			return nullptr;
		};
		TPointer<Image> retV = create(bmp->getWidth(), bmp->getHeight());
		if (!retV) {
			return nullptr;
		};
		uint32_t x, y;
		uint32_t lx = bmp->getWidth();
		uint32_t ly = bmp->getHeight();
		BitmapRGBA rgba;
		Pixel *pixel;
		if (bmp->getPixelWidth() == 32) {
			uint32_t scanLine = bmp->getScanLine();
			BitmapRGBA *row;
			for (y = 0; y < ly; ++y) {
				row = bmp->getRow32Bits(y, scanLine);
				pixel = retV->pixel[y];
				for (x = 0; x < lx; ++x) {
					pixel[x] = XYO_PIXEL32_PIXEL(row[x].rgbRed, row[x].rgbGreen, row[x].rgbBlue, row[x].rgbAlpha);
				};
			};
			return retV;
		};
		for (y = 0; y < ly; ++y) {
			pixel = retV->pixel[ly - y - 1];
			for (x = 0; x < lx; ++x) {
				bmp->getPixel32X(x, y, rgba);
				pixel[x] = XYO_PIXEL32_PIXEL(rgba.rgbRed, rgba.rgbGreen, rgba.rgbBlue, rgba.rgbAlpha);
			};
		};
		return retV;
	};
};
