//
// XYO Pixel32
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_PIXEL32_BMP_HPP
#define XYO_PIXEL32_BMP_HPP

#ifndef XYO_PIXEL32__DEPENDENCY_HPP
#	include "xyo-pixel32--dependency.hpp"
#endif

namespace XYO {
	namespace Pixel32 {

		using namespace XYO;

#define XYO_PIXEL32_BMP_FILE_ID 0x4D42

#ifdef XYO_COMPILER_MSVC
#	include "pshpack1.h"
#endif

		typedef struct SBmpFileHeader {
				uint16_t bfType;
				uint32_t bfSize;
				uint16_t bfReserved1;
				uint16_t bfReserved2;
				uint32_t bfOffBits;
		} BmpFileHeader;

		typedef struct SBmpInfoHeader {
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
		} BmpInfoHeader;

		typedef struct SBmpRgbQuad {
				uint8_t rgbBlue;
				uint8_t rgbGreen;
				uint8_t rgbRed;
				uint8_t rgbReserved;
		} BmpRgbQuad;

		typedef struct SBmpRgbTriple {
				uint8_t rgbtBlue;
				uint8_t rgbtGreen;
				uint8_t rgbtRed;
		} BmpRgbTriple;

		typedef struct SBmpImage {
				BmpFileHeader fh;
				BmpInfoHeader ih;
		} BmpImage;

#ifdef XYO_COMPILER_MSVC
#	include "poppack.h"
#endif

		class Bmp : public virtual Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(Bmp);

			protected:
				BmpImage *image;

			public:
				XYO_PIXEL32_EXPORT Bmp();
				XYO_PIXEL32_EXPORT ~Bmp();

				XYO_PIXEL32_EXPORT static TPointer<Bmp> newImage32Bits(uint32_t lx, uint32_t ly);
				XYO_PIXEL32_EXPORT static TPointer<Bmp> newImage24Bits(uint32_t lx, uint32_t ly);
				XYO_PIXEL32_EXPORT static TPointer<Bmp> newImage8Bits(uint32_t lx, uint32_t ly);
				XYO_PIXEL32_EXPORT static TPointer<Bmp> newImage4Bits(uint32_t lx, uint32_t ly);
				XYO_PIXEL32_EXPORT static TPointer<Bmp> newImage1Bit(uint32_t lx, uint32_t ly);
				XYO_PIXEL32_EXPORT static TPointer<Bmp> newImageOwner(BmpImage *image_);
				XYO_PIXEL32_EXPORT static TPointer<Bmp> loadImage(char *name);
				XYO_PIXEL32_EXPORT bool saveImage(char *name);

				inline BmpImage *getBmpImage() {
					return image;
				};

				XYO_PIXEL32_EXPORT static uint32_t scanLine(BmpInfoHeader &bih);
				XYO_PIXEL32_EXPORT static void calculateImageSizeNoCompression(BmpFileHeader &bfh, BmpInfoHeader &bih);

				XYO_PIXEL32_EXPORT void setPixel32(uint32_t x, uint32_t y, BmpRgbQuad &c);
				XYO_PIXEL32_EXPORT void setPixel24(uint32_t x, uint32_t y, BmpRgbTriple &c);
				XYO_PIXEL32_EXPORT void setPixel8(uint32_t x, uint32_t y, uint8_t &c);
				XYO_PIXEL32_EXPORT void setPixel4(uint32_t x, uint32_t y, uint8_t &c);
				XYO_PIXEL32_EXPORT void setPixel1(uint32_t x, uint32_t y, uint8_t &c);
				XYO_PIXEL32_EXPORT void getPixel32(uint32_t x, uint32_t y, BmpRgbQuad &c);
				XYO_PIXEL32_EXPORT void getPixel24(uint32_t x, uint32_t y, BmpRgbTriple &c);
				XYO_PIXEL32_EXPORT void getPixel24X(uint32_t x, uint32_t y, BmpRgbQuad &c);
				XYO_PIXEL32_EXPORT void getPixel8(uint32_t x, uint32_t y, uint8_t &c);
				XYO_PIXEL32_EXPORT void getPixel4(uint32_t x, uint32_t y, uint8_t &c);
				XYO_PIXEL32_EXPORT void getPixel1(uint32_t x, uint32_t y, uint8_t &c);
				XYO_PIXEL32_EXPORT void getPixelPal8(uint32_t x, uint32_t y, BmpRgbQuad &c);
				XYO_PIXEL32_EXPORT void getPixelPal4(uint32_t x, uint32_t y, BmpRgbQuad &c);
				XYO_PIXEL32_EXPORT void getPixelPal1(uint32_t x, uint32_t y, BmpRgbQuad &c);
				XYO_PIXEL32_EXPORT void setPixelPal8(uint32_t x, uint32_t y, BmpRgbQuad &c);
				XYO_PIXEL32_EXPORT void setPixelPal4(uint32_t x, uint32_t y, BmpRgbQuad &c);
				XYO_PIXEL32_EXPORT void setPixelPal1(uint32_t x, uint32_t y, BmpRgbQuad &c);
				XYO_PIXEL32_EXPORT uint16_t getPaletteSize();
				XYO_PIXEL32_EXPORT void getPaletteIndex(uint8_t index, BmpRgbQuad &c);
				XYO_PIXEL32_EXPORT void setPaletteIndex(uint8_t index, BmpRgbQuad &c);
				XYO_PIXEL32_EXPORT bool getPaletteColor(uint8_t &index, BmpRgbQuad &c);
				XYO_PIXEL32_EXPORT uint32_t getWidth();
				XYO_PIXEL32_EXPORT uint32_t getHeight();
				XYO_PIXEL32_EXPORT uint16_t getPixelWidth();
				XYO_PIXEL32_EXPORT bool isPallete();
				XYO_PIXEL32_EXPORT void getPixel32s(long int x, long int y, BmpRgbQuad &c);
				XYO_PIXEL32_EXPORT void setPixel32s(long int x, long int y, BmpRgbQuad &c);
				XYO_PIXEL32_EXPORT BmpRgbQuad *getRow32Bits(uint32_t y, uint32_t scanLine);
				XYO_PIXEL32_EXPORT uint32_t getScanLine();

				XYO_PIXEL32_EXPORT void getPixel32X(uint32_t x, uint32_t y, BmpRgbQuad &c);
				XYO_PIXEL32_EXPORT TPointer<Bmp> convertTo32Bits();
				XYO_PIXEL32_EXPORT void swapRBInvertA32();
				XYO_PIXEL32_EXPORT void setAlpha32(uint8_t alpha);
		};

	};
};

#endif
