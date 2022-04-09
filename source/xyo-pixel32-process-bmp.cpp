//
// XYO Pixel32
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-pixel32-process.hpp"

namespace XYO {
	namespace Pixel32 {
		namespace Process {

			using namespace XYO;

			bool bmp32Alpha1(Bmp *inBmp32, TPointer<Bmp> &outBmp1, int level) {
				if (inBmp32->getPixelWidth() == 32) {
					uint32_t lx, ly;

					lx = inBmp32->getWidth();
					ly = inBmp32->getHeight();

					outBmp1 = Bmp::newImage1Bit(lx, ly);

					uint32_t kx, ky;
					BmpRgbQuad c32;
					uint8_t c8;

					c32.rgbBlue = 0;
					c32.rgbGreen = 0;
					c32.rgbRed = 0;
					c32.rgbReserved = 0;
					outBmp1->setPaletteIndex(0, c32);
					c32.rgbBlue = 255;
					c32.rgbGreen = 255;
					c32.rgbRed = 255;
					c32.rgbReserved = 0;
					outBmp1->setPaletteIndex(1, c32);

					for (ky = 0; ky < ly; ky++) {
						for (kx = 0; kx < lx; kx++) {
							inBmp32->getPixel32(kx, ky, c32);
							c8 = c32.rgbReserved;
							if (c8 < level) {
								c8 = 1;
							} else {
								c8 = 0;
							}
							outBmp1->setPixel1(kx, ky, c8);
						};
					};

					return true;
				};
				return false;
			};

			bool bmp32To24Alpha8(Bmp *inBmp32, TPointer<Bmp> &outBmp24, TPointer<Bmp> &outBmp8) {
				if (inBmp32->getPixelWidth() == 32) {
					uint32_t lx, ly;

					lx = inBmp32->getWidth();
					ly = inBmp32->getHeight();

					outBmp24 = Bmp::newImage24Bits(lx, ly);
					outBmp8 = Bmp::newImage8Bits(lx, ly);

					uint32_t kx, ky;
					BmpRgbQuad c32;
					BmpRgbTriple c24;
					uint8_t c8;

					for (ky = 0; ky < ly; ky++) {
						for (kx = 0; kx < lx; kx++) {
							inBmp32->getPixel32(kx, ky, c32);
							c24.rgbtBlue = c32.rgbBlue;
							c24.rgbtGreen = c32.rgbGreen;
							c24.rgbtRed = c32.rgbRed;
							outBmp24->setPixel24(kx, ky, c24);
						};
					};

					for (kx = 0; kx < 256; kx++) {
						c32.rgbBlue = (uint8_t)kx;
						c32.rgbGreen = (uint8_t)kx;
						c32.rgbRed = (uint8_t)kx;
						c32.rgbReserved = 0;
						outBmp8->setPaletteIndex((uint8_t)kx, c32);
					};
					for (ky = 0; ky < ly; ky++) {
						for (kx = 0; kx < lx; kx++) {
							inBmp32->getPixel32(kx, ky, c32);
							c8 = c32.rgbReserved;
							outBmp8->setPixel8(kx, ky, c8);
						};
					};

					return true;
				};

				return false;
			};

			bool bmp32To8Alpha1(Bmp *inBmp32, TPointer<Bmp> &outBmp8, TPointer<Bmp> &outBmp1, int level, bool &noFreeColorsLeft) {
				noFreeColorsLeft = false;

				if (inBmp32->getPixelWidth() == 32) {
					uint32_t lx, ly;

					lx = inBmp32->getWidth();
					ly = inBmp32->getHeight();

					outBmp8 = Bmp::newImage8Bits(lx, ly);

					uint32_t kx, ky;
					BmpRgbQuad c32;
					BmpRgbQuad cx32;

					uint8_t c8;
					int index, k;

					index = 0;
					for (ky = 0; ky < ly; ky++) {
						for (kx = 0; kx < lx; kx++) {
							inBmp32->getPixel32(kx, ky, c32);

							for (k = 0; k < index; ++k) {
								outBmp8->getPaletteIndex((uint8_t)k, cx32);
								if ((cx32.rgbBlue == c32.rgbBlue) && (cx32.rgbGreen == c32.rgbGreen) && (cx32.rgbRed == c32.rgbRed)) {
									break;
								};
							};
							if (k < index) {
								c8 = (uint8_t)k;
							} else {
								if (index < 256) {
									c8 = (uint8_t)index;
									c32.rgbReserved = 0;
									outBmp8->setPaletteIndex(c8, c32);
									++index;
								} else {
									noFreeColorsLeft = true;
								};
							};

							outBmp8->setPixel8(kx, ky, c8);
						};
					};

					if (bmp32Alpha1(inBmp32, outBmp1, level)) {
						return true;
					};
				};

				return false;
			};

			bool bmp32To4Alpha1(Bmp *inBmp32, TPointer<Bmp> &outBmp4, TPointer<Bmp> &outBmp1, int level, bool &noFreeColorsLeft) {
				noFreeColorsLeft = false;

				if (inBmp32->getPixelWidth() == 32) {
					uint32_t lx, ly;

					lx = inBmp32->getWidth();
					ly = inBmp32->getHeight();

					outBmp4 = Bmp::newImage4Bits(lx, ly);

					uint32_t kx, ky;
					BmpRgbQuad c32;
					BmpRgbQuad cx32;

					uint8_t c4;
					int index, k;

					index = 0;
					for (ky = 0; ky < ly; ky++) {
						for (kx = 0; kx < lx; kx++) {
							inBmp32->getPixel32(kx, ky, c32);

							for (k = 0; k < index; ++k) {
								outBmp4->getPaletteIndex((uint8_t)k, cx32);
								if ((cx32.rgbBlue == c32.rgbBlue) && (cx32.rgbGreen == c32.rgbGreen) && (cx32.rgbRed == c32.rgbRed)) {
									break;
								};
							};

							if (k < index) {
								c4 = (uint8_t)k;
							} else {
								if (index < 16) {
									c4 = (uint8_t)index;
									c32.rgbReserved = 0;
									outBmp4->setPaletteIndex(c4, c32);
									++index;
								} else {
									noFreeColorsLeft = true;
								};
							};

							outBmp4->setPixel4(kx, ky, c4);
						};
					};

					if (bmp32Alpha1(inBmp32, outBmp1, level)) {
						return true;
					};
				};
				return false;
			};

			TPointer<Bmp> alphaToBmp8(Image *inImage) {
				uint32_t lx, ly;

				lx = inImage->width;
				ly = inImage->height;
				uint8_t c8;

				TPointer<Bmp> outBmp8 = Bmp::newImage8Bits(lx, ly);
				uint32_t x, y, cx;
				int crx, cgx, cbx;
				int palleteIndex;
				BmpRgbQuad palleteColor;
				for (palleteIndex = 0; palleteIndex < 256; ++palleteIndex) {
					palleteColor.rgbBlue = 0x00;
					palleteColor.rgbGreen = 0x00;
					palleteColor.rgbRed = 0x00;
					palleteColor.rgbReserved = palleteIndex;
					outBmp8->setPaletteIndex(palleteIndex, palleteColor);
				};

				for (y = 0; y < ly; ++y) {
					for (x = 0; x < lx; ++x) {
						c8 = XYO_PIXEL32_A(inImage->pixel[ly - y - 1][x]);
						outBmp8->setPixel8(x, y, c8);
					};
				};
				return outBmp8;
			};

			TPointer<Bmp> alphaToBmp1(Image *inImage, int level) {
				uint32_t lx, ly;

				lx = inImage->width;
				ly = inImage->height;
				BmpRgbQuad palleteColor;

				TPointer<Bmp> outBmp1;

				outBmp1 = Bmp::newImage1Bit(lx, ly);
				palleteColor.rgbBlue = 0x00;
				palleteColor.rgbGreen = 0x00;
				palleteColor.rgbRed = 0x00;
				palleteColor.rgbReserved = 0x00;
				outBmp1->setPaletteIndex(0, palleteColor);
				palleteColor.rgbBlue = 0xFF;
				palleteColor.rgbGreen = 0xFF;
				palleteColor.rgbRed = 0xFF;
				palleteColor.rgbReserved = 0x00;
				outBmp1->setPaletteIndex(1, palleteColor);

				uint32_t x, y;
				uint8_t cx;

				for (y = 0; y < ly; ++y) {
					for (x = 0; x < lx; ++x) {
						if (XYO_PIXEL32_A(inImage->pixel[ly - y - 1][x]) < level) {
							cx = 1;
						} else {
							cx = 0;
						}
						outBmp1->setPixel1(x, y, cx);
					};
				};

				return outBmp1;
			};

			TPointer<Bmp> toBmp24(Image *inImage) {
				uint32_t lx, ly;

				lx = inImage->width;
				ly = inImage->height;

				TPointer<Bmp> outBmp24 = Bmp::newImage24Bits(lx, ly);
				uint32_t x, y, cx;
				BmpRgbTriple color;
				for (y = 0; y < ly; ++y) {
					for (x = 0; x < lx; ++x) {
						cx = inImage->pixel[ly - y - 1][x];
						color.rgbtRed = XYO_PIXEL32_R(cx);
						color.rgbtGreen = XYO_PIXEL32_G(cx);
						color.rgbtBlue = XYO_PIXEL32_B(cx);
						outBmp24->setPixel24(x, y, color);
					};
				};
				return outBmp24;
			};

			TPointer<Bmp> toBmp32(Image *inImage) {
				uint32_t lx, ly;

				lx = inImage->width;
				ly = inImage->height;

				TPointer<Bmp> outBmp32 = Bmp::newImage32Bits(lx, ly);
				uint32_t x, y, cx;
				BmpRgbQuad color;
				for (y = 0; y < ly; ++y) {
					for (x = 0; x < lx; ++x) {
						cx = inImage->pixel[ly - y - 1][x];
						color.rgbRed = XYO_PIXEL32_R(cx);
						color.rgbGreen = XYO_PIXEL32_G(cx);
						color.rgbBlue = XYO_PIXEL32_B(cx);
						color.rgbReserved = XYO_PIXEL32_A(cx);
						outBmp32->setPixel32(x, y, color);
					};
				};
				return outBmp32;
			};

		};
	};
};
