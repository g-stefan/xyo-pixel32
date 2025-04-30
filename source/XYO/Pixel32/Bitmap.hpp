// Pixel32
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_PIXEL32_BITMAP_HPP
#define XYO_PIXEL32_BITMAP_HPP

#ifndef XYO_PIXEL32_DEPENDENCY_HPP
#	include <XYO/Pixel32/Dependency.hpp>
#endif

namespace XYO::Pixel32 {

#define XYO_PIXEL32_BITMAP_FILE_ID 0x4D42

#ifdef XYO_PLATFORM_COMPILER_MSVC
#	include "pshpack1.h"
#endif

	struct BitmapFileHeader {
			uint16_t bfType;
			uint32_t bfSize;
			uint16_t bfReserved1;
			uint16_t bfReserved2;
			uint32_t bfOffBits;
	};

	struct BitmapInfoHeader {
			uint32_t biSize;
			uint32_t biWidth;
			uint32_t biHeight;
			uint16_t biPlanes;
			uint16_t biBitCount;
			uint32_t biCompression;
			uint32_t biSizeImage;
			uint32_t biXPelsPerMeter;
			uint32_t biYPelsPerMeter;
			uint32_t biClrUsed;
			uint32_t biClrImportant;
	};

	struct BitmapRBGA {
			uint8_t rgbBlue;
			uint8_t rgbGreen;
			uint8_t rgbRed;
			uint8_t rgbAlpha;
	};

	struct BitmapRBG {
			uint8_t rgbtBlue;
			uint8_t rgbtGreen;
			uint8_t rgbtRed;
	};

	struct BitmapImage {
			BitmapFileHeader fh;
			BitmapInfoHeader ih;
	};

#ifdef XYO_PLATFORM_COMPILER_MSVC
#	include "poppack.h"
#endif

	class Bitmap : public virtual Object {
			XYO_PLATFORM_DISALLOW_COPY_ASSIGN_MOVE(Bitmap);

		protected:
			BitmapImage *image;

		public:
			XYO_PIXEL32_EXPORT Bitmap();
			XYO_PIXEL32_EXPORT ~Bitmap();

			XYO_PIXEL32_EXPORT static TPointer<Bitmap> newImage32Bits(uint32_t lx, uint32_t ly);
			XYO_PIXEL32_EXPORT static TPointer<Bitmap> newImage24Bits(uint32_t lx, uint32_t ly);
			XYO_PIXEL32_EXPORT static TPointer<Bitmap> newImage8Bits(uint32_t lx, uint32_t ly);
			XYO_PIXEL32_EXPORT static TPointer<Bitmap> newImage4Bits(uint32_t lx, uint32_t ly);
			XYO_PIXEL32_EXPORT static TPointer<Bitmap> newImage1Bit(uint32_t lx, uint32_t ly);
			XYO_PIXEL32_EXPORT static TPointer<Bitmap> newImageOwner(BitmapImage *image_);
			XYO_PIXEL32_EXPORT static TPointer<Bitmap> loadImage(char *name);
			XYO_PIXEL32_EXPORT bool saveImage(char *name);

			inline BitmapImage *getBitmapImage() {
				return image;
			};

			XYO_PIXEL32_EXPORT static uint32_t scanLine(BitmapInfoHeader &bih);
			XYO_PIXEL32_EXPORT static void calculateImageSizeNoCompression(BitmapFileHeader &bfh, BitmapInfoHeader &bih);

			XYO_PIXEL32_EXPORT void setPixel32(uint32_t x, uint32_t y, BitmapRBGA &c);
			XYO_PIXEL32_EXPORT void setPixel24(uint32_t x, uint32_t y, BitmapRBG &c);
			XYO_PIXEL32_EXPORT void setPixel8(uint32_t x, uint32_t y, uint8_t &c);
			XYO_PIXEL32_EXPORT void setPixel4(uint32_t x, uint32_t y, uint8_t &c);
			XYO_PIXEL32_EXPORT void setPixel1(uint32_t x, uint32_t y, uint8_t &c);
			XYO_PIXEL32_EXPORT void getPixel32(uint32_t x, uint32_t y, BitmapRBGA &c);
			XYO_PIXEL32_EXPORT void getPixel24(uint32_t x, uint32_t y, BitmapRBG &c);
			XYO_PIXEL32_EXPORT void getPixel24X(uint32_t x, uint32_t y, BitmapRBGA &c);
			XYO_PIXEL32_EXPORT void getPixel8(uint32_t x, uint32_t y, uint8_t &c);
			XYO_PIXEL32_EXPORT void getPixel4(uint32_t x, uint32_t y, uint8_t &c);
			XYO_PIXEL32_EXPORT void getPixel1(uint32_t x, uint32_t y, uint8_t &c);
			XYO_PIXEL32_EXPORT void getPixelPal8(uint32_t x, uint32_t y, BitmapRBGA &c);
			XYO_PIXEL32_EXPORT void getPixelPal4(uint32_t x, uint32_t y, BitmapRBGA &c);
			XYO_PIXEL32_EXPORT void getPixelPal1(uint32_t x, uint32_t y, BitmapRBGA &c);
			XYO_PIXEL32_EXPORT void setPixelPal8(uint32_t x, uint32_t y, BitmapRBGA &c);
			XYO_PIXEL32_EXPORT void setPixelPal4(uint32_t x, uint32_t y, BitmapRBGA &c);
			XYO_PIXEL32_EXPORT void setPixelPal1(uint32_t x, uint32_t y, BitmapRBGA &c);
			XYO_PIXEL32_EXPORT uint16_t getPaletteSize();
			XYO_PIXEL32_EXPORT void getPaletteIndex(uint8_t index, BitmapRBGA &c);
			XYO_PIXEL32_EXPORT void setPaletteIndex(uint8_t index, BitmapRBGA &c);
			XYO_PIXEL32_EXPORT bool getPaletteColor(uint8_t &index, BitmapRBGA &c);
			XYO_PIXEL32_EXPORT uint32_t getWidth();
			XYO_PIXEL32_EXPORT uint32_t getHeight();
			XYO_PIXEL32_EXPORT uint16_t getPixelWidth();
			XYO_PIXEL32_EXPORT bool isPalette();
			XYO_PIXEL32_EXPORT void getPixel32s(long int x, long int y, BitmapRBGA &c);
			XYO_PIXEL32_EXPORT void setPixel32s(long int x, long int y, BitmapRBGA &c);
			XYO_PIXEL32_EXPORT BitmapRBGA *getRow32Bits(uint32_t y, uint32_t scanLine);
			XYO_PIXEL32_EXPORT uint32_t getScanLine();

			XYO_PIXEL32_EXPORT void getPixel32X(uint32_t x, uint32_t y, BitmapRBGA &c);
			XYO_PIXEL32_EXPORT TPointer<Bitmap> convertTo32Bits();
			XYO_PIXEL32_EXPORT void swapRBInvertA32();
			XYO_PIXEL32_EXPORT void setAlpha32(uint8_t alpha);
	};

};

#endif
