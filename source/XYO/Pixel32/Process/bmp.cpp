// Pixel32
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	bool bmp32Alpha1(Bitmap *inBitmap32, TPointer<Bitmap> &outBitmap1, int level) {
		if (inBitmap32->getPixelWidth() == 32) {
			uint32_t lx, ly;

			lx = inBitmap32->getWidth();
			ly = inBitmap32->getHeight();

			outBitmap1 = Bitmap::newImage1Bit(lx, ly);

			uint32_t kx, ky;
			BitmapRBGA c32;
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
					c8 = c32.rgbAlpha;
					if (c8 < level) {
						c8 = 1;
					} else {
						c8 = 0;
					}
					outBitmap1->setPixel1(kx, ky, c8);
				};
			};

			return true;
		};
		return false;
	};

	bool bmp32To24Alpha8(Bitmap *inBitmap32, TPointer<Bitmap> &outBitmap24, TPointer<Bitmap> &outBitmap8) {
		if (inBitmap32->getPixelWidth() == 32) {
			uint32_t lx, ly;

			lx = inBitmap32->getWidth();
			ly = inBitmap32->getHeight();

			outBitmap24 = Bitmap::newImage24Bits(lx, ly);
			outBitmap8 = Bitmap::newImage8Bits(lx, ly);

			uint32_t kx, ky;
			BitmapRBGA c32;
			BitmapRBG c24;
			uint8_t c8;

			for (ky = 0; ky < ly; ky++) {
				for (kx = 0; kx < lx; kx++) {
					inBitmap32->getPixel32(kx, ky, c32);
					c24.rgbtBlue = c32.rgbBlue;
					c24.rgbtGreen = c32.rgbGreen;
					c24.rgbtRed = c32.rgbRed;
					outBitmap24->setPixel24(kx, ky, c24);
				};
			};

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
					c8 = c32.rgbAlpha;
					outBitmap8->setPixel8(kx, ky, c8);
				};
			};

			return true;
		};

		return false;
	};

	bool bmp32To8Alpha1(Bitmap *inBitmap32, TPointer<Bitmap> &outBitmap8, TPointer<Bitmap> &outBitmap1, int level, bool &noFreeColorsLeft) {
		noFreeColorsLeft = false;

		if (inBitmap32->getPixelWidth() == 32) {
			uint32_t lx, ly;

			lx = inBitmap32->getWidth();
			ly = inBitmap32->getHeight();

			outBitmap8 = Bitmap::newImage8Bits(lx, ly);

			uint32_t kx, ky;
			BitmapRBGA c32;
			BitmapRBGA cx32;

			uint8_t c8;
			int index, k;

			index = 0;
			for (ky = 0; ky < ly; ky++) {
				for (kx = 0; kx < lx; kx++) {
					inBitmap32->getPixel32(kx, ky, c32);

					for (k = 0; k < index; ++k) {
						outBitmap8->getPaletteIndex((uint8_t)k, cx32);
						if ((cx32.rgbBlue == c32.rgbBlue) && (cx32.rgbGreen == c32.rgbGreen) && (cx32.rgbRed == c32.rgbRed)) {
							break;
						};
					};
					if (k < index) {
						c8 = (uint8_t)k;
					} else {
						if (index < 256) {
							c8 = (uint8_t)index;
							c32.rgbAlpha = 0;
							outBitmap8->setPaletteIndex(c8, c32);
							++index;
						} else {
							noFreeColorsLeft = true;
						};
					};

					outBitmap8->setPixel8(kx, ky, c8);
				};
			};

			if (bmp32Alpha1(inBitmap32, outBitmap1, level)) {
				return true;
			};
		};

		return false;
	};

	bool bmp32To4Alpha1(Bitmap *inBitmap32, TPointer<Bitmap> &outBitmap4, TPointer<Bitmap> &outBitmap1, int level, bool &noFreeColorsLeft) {
		noFreeColorsLeft = false;

		if (inBitmap32->getPixelWidth() == 32) {
			uint32_t lx, ly;

			lx = inBitmap32->getWidth();
			ly = inBitmap32->getHeight();

			outBitmap4 = Bitmap::newImage4Bits(lx, ly);

			uint32_t kx, ky;
			BitmapRBGA c32;
			BitmapRBGA cx32;

			uint8_t c4;
			int index, k;

			index = 0;
			for (ky = 0; ky < ly; ky++) {
				for (kx = 0; kx < lx; kx++) {
					inBitmap32->getPixel32(kx, ky, c32);

					for (k = 0; k < index; ++k) {
						outBitmap4->getPaletteIndex((uint8_t)k, cx32);
						if ((cx32.rgbBlue == c32.rgbBlue) && (cx32.rgbGreen == c32.rgbGreen) && (cx32.rgbRed == c32.rgbRed)) {
							break;
						};
					};

					if (k < index) {
						c4 = (uint8_t)k;
					} else {
						if (index < 16) {
							c4 = (uint8_t)index;
							c32.rgbAlpha = 0;
							outBitmap4->setPaletteIndex(c4, c32);
							++index;
						} else {
							noFreeColorsLeft = true;
						};
					};

					outBitmap4->setPixel4(kx, ky, c4);
				};
			};

			if (bmp32Alpha1(inBitmap32, outBitmap1, level)) {
				return true;
			};
		};
		return false;
	};

	TPointer<Bitmap> alphaToBitmap8(Image *inImage) {
		uint32_t lx, ly;

		lx = inImage->width;
		ly = inImage->height;
		uint8_t c8;

		TPointer<Bitmap> outBitmap8 = Bitmap::newImage8Bits(lx, ly);
		uint32_t x, y, cx;
		int crx, cgx, cbx;
		int palleteIndex;
		BitmapRBGA palleteColor;
		for (palleteIndex = 0; palleteIndex < 256; ++palleteIndex) {
			palleteColor.rgbBlue = 0x00;
			palleteColor.rgbGreen = 0x00;
			palleteColor.rgbRed = 0x00;
			palleteColor.rgbAlpha = palleteIndex;
			outBitmap8->setPaletteIndex(palleteIndex, palleteColor);
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
		BitmapRBGA palleteColor;

		TPointer<Bitmap> outBitmap1;

		outBitmap1 = Bitmap::newImage1Bit(lx, ly);
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
				if (XYO_PIXEL32_A(inImage->pixel[ly - y - 1][x]) < level) {
					cx = 1;
				} else {
					cx = 0;
				}
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
		uint32_t x, y, cx;
		BitmapRBG color;
		for (y = 0; y < ly; ++y) {
			for (x = 0; x < lx; ++x) {
				cx = inImage->pixel[ly - y - 1][x];
				color.rgbtRed = XYO_PIXEL32_R(cx);
				color.rgbtGreen = XYO_PIXEL32_G(cx);
				color.rgbtBlue = XYO_PIXEL32_B(cx);
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
		uint32_t x, y, cx;
		BitmapRBGA color;
		for (y = 0; y < ly; ++y) {
			for (x = 0; x < lx; ++x) {
				cx = inImage->pixel[ly - y - 1][x];
				color.rgbRed = XYO_PIXEL32_R(cx);
				color.rgbGreen = XYO_PIXEL32_G(cx);
				color.rgbBlue = XYO_PIXEL32_B(cx);
				color.rgbAlpha = XYO_PIXEL32_A(cx);
				outBitmap32->setPixel32(x, y, color);
			};
		};
		return outBitmap32;
	};

};
