// Pixel32
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Bitmap.hpp>

namespace XYO::Pixel32 {

	Bitmap::Bitmap() {
		image = NULL;
	};

	Bitmap::~Bitmap() {
		if (image) {
			delete[] ((uint8_t *)image);
		};
	};

	TPointer<Bitmap> Bitmap::newImage32Bits(uint32_t lx, uint32_t ly) {
		TPointer<Bitmap> retV;

		retV.newMemory();

		BitmapImage bmp_x;
		BitmapImage *bmp_new;

		bmp_x.fh.bfType = XYO_PIXEL32_BITMAP_FILE_ID;
		bmp_x.fh.bfSize = 0;
		bmp_x.fh.bfReserved1 = 0;
		bmp_x.fh.bfReserved2 = 0;
		bmp_x.fh.bfOffBits = 0;

		bmp_x.ih.biSize = sizeof(BitmapInfoHeader);
		bmp_x.ih.biWidth = lx;
		bmp_x.ih.biHeight = ly;
		bmp_x.ih.biPlanes = 1;
		bmp_x.ih.biBitCount = 32;
		bmp_x.ih.biCompression = 0;
		bmp_x.ih.biSizeImage = 0;
		bmp_x.ih.biXPelsPerMeter = 256;
		bmp_x.ih.biYPelsPerMeter = 256;
		bmp_x.ih.biClrUsed = 0;
		bmp_x.ih.biClrImportant = 0;

		calculateImageSizeNoCompression(bmp_x.fh, bmp_x.ih);
		if (bmp_x.fh.bfSize >= sizeof(BitmapImage)) {
			bmp_new = (BitmapImage *)(new uint8_t[bmp_x.fh.bfSize]);
			memcpy(bmp_new, &bmp_x, sizeof(BitmapImage));
			retV->image = bmp_new;
		};

		return retV;
	};

	TPointer<Bitmap> Bitmap::newImage24Bits(uint32_t lx, uint32_t ly) {

		TPointer<Bitmap> retV;
		retV.newMemory();

		BitmapImage bmp_x;
		BitmapImage *bmp_new;

		bmp_x.fh.bfType = XYO_PIXEL32_BITMAP_FILE_ID;
		bmp_x.fh.bfSize = 0;
		bmp_x.fh.bfReserved1 = 0;
		bmp_x.fh.bfReserved2 = 0;
		bmp_x.fh.bfOffBits = 0;

		bmp_x.ih.biSize = sizeof(BitmapInfoHeader);
		bmp_x.ih.biWidth = lx;
		bmp_x.ih.biHeight = ly;
		bmp_x.ih.biPlanes = 1;
		bmp_x.ih.biBitCount = 24;
		bmp_x.ih.biCompression = 0;
		bmp_x.ih.biSizeImage = 0;
		bmp_x.ih.biXPelsPerMeter = 256;
		bmp_x.ih.biYPelsPerMeter = 256;
		bmp_x.ih.biClrUsed = 0;
		bmp_x.ih.biClrImportant = 0;

		calculateImageSizeNoCompression(bmp_x.fh, bmp_x.ih);
		if (bmp_x.fh.bfSize >= sizeof(BitmapImage)) {
			bmp_new = (BitmapImage *)(new uint8_t[bmp_x.fh.bfSize]);
			memcpy(bmp_new, &bmp_x, sizeof(BitmapImage));
			retV->image = bmp_new;
		};

		return retV;
	};

	TPointer<Bitmap> Bitmap::newImage8Bits(uint32_t lx, uint32_t ly) {

		TPointer<Bitmap> retV;

		retV.newMemory();

		BitmapImage bmp_x;
		BitmapImage *bmp_new;

		bmp_x.fh.bfType = XYO_PIXEL32_BITMAP_FILE_ID;
		bmp_x.fh.bfSize = 0;
		bmp_x.fh.bfReserved1 = 0;
		bmp_x.fh.bfReserved2 = 0;
		bmp_x.fh.bfOffBits = 0;

		bmp_x.ih.biSize = sizeof(BitmapInfoHeader);
		bmp_x.ih.biWidth = lx;
		bmp_x.ih.biHeight = ly;
		bmp_x.ih.biPlanes = 1;
		bmp_x.ih.biBitCount = 8;
		bmp_x.ih.biCompression = 0;
		bmp_x.ih.biSizeImage = 0;
		bmp_x.ih.biXPelsPerMeter = 256;
		bmp_x.ih.biYPelsPerMeter = 256;
		bmp_x.ih.biClrUsed = 0;
		bmp_x.ih.biClrImportant = 0;

		calculateImageSizeNoCompression(bmp_x.fh, bmp_x.ih);
		if (bmp_x.fh.bfSize >= (sizeof(BitmapImage) + (sizeof(BitmapRBGA) * 256))) {
			bmp_new = (BitmapImage *)(new uint8_t[bmp_x.fh.bfSize]);
			memcpy(bmp_new, &bmp_x, sizeof(BitmapImage));
			memset(bmp_new + 1, 0, sizeof(BitmapRBGA) * 256);
			retV->image = bmp_new;
		};

		return retV;
	};

	TPointer<Bitmap> Bitmap::newImage4Bits(uint32_t lx, uint32_t ly) {

		TPointer<Bitmap> retV;

		retV.newMemory();

		BitmapImage bmp_x;
		BitmapImage *bmp_new;

		bmp_x.fh.bfType = XYO_PIXEL32_BITMAP_FILE_ID;
		bmp_x.fh.bfSize = 0;
		bmp_x.fh.bfReserved1 = 0;
		bmp_x.fh.bfReserved2 = 0;
		bmp_x.fh.bfOffBits = 0;

		bmp_x.ih.biSize = sizeof(BitmapInfoHeader);
		bmp_x.ih.biWidth = lx;
		bmp_x.ih.biHeight = ly;
		bmp_x.ih.biPlanes = 1;
		bmp_x.ih.biBitCount = 4;
		bmp_x.ih.biCompression = 0;
		bmp_x.ih.biSizeImage = 0;
		bmp_x.ih.biXPelsPerMeter = 256;
		bmp_x.ih.biYPelsPerMeter = 256;
		bmp_x.ih.biClrUsed = 0;
		bmp_x.ih.biClrImportant = 0;

		calculateImageSizeNoCompression(bmp_x.fh, bmp_x.ih);
		if (bmp_x.fh.bfSize >= (sizeof(BitmapImage) + (sizeof(BitmapRBGA) * 16))) {
			bmp_new = (BitmapImage *)(new uint8_t[bmp_x.fh.bfSize]);
			memcpy(bmp_new, &bmp_x, sizeof(BitmapImage));
			memset(bmp_new + 1, 0, sizeof(BitmapRBGA) * 16);
			retV->image = bmp_new;
		};

		return retV;
	};

	TPointer<Bitmap> Bitmap::newImage1Bit(uint32_t lx, uint32_t ly) {

		TPointer<Bitmap> retV;

		retV.newMemory();

		BitmapImage bmp_x;
		BitmapImage *bmp_new;

		bmp_x.fh.bfType = XYO_PIXEL32_BITMAP_FILE_ID;
		bmp_x.fh.bfSize = 0;
		bmp_x.fh.bfReserved1 = 0;
		bmp_x.fh.bfReserved2 = 0;
		bmp_x.fh.bfOffBits = 0;

		bmp_x.ih.biSize = sizeof(BitmapInfoHeader);
		bmp_x.ih.biWidth = lx;
		bmp_x.ih.biHeight = ly;
		bmp_x.ih.biPlanes = 1;
		bmp_x.ih.biBitCount = 1;
		bmp_x.ih.biCompression = 0;
		bmp_x.ih.biSizeImage = 0;
		bmp_x.ih.biXPelsPerMeter = 256;
		bmp_x.ih.biYPelsPerMeter = 256;
		bmp_x.ih.biClrUsed = 0;
		bmp_x.ih.biClrImportant = 0;

		calculateImageSizeNoCompression(bmp_x.fh, bmp_x.ih);
		if (bmp_x.fh.bfSize >= (sizeof(BitmapImage) + (sizeof(BitmapRBGA) * 2))) {
			bmp_new = (BitmapImage *)(new uint8_t[bmp_x.fh.bfSize]);
			memcpy(bmp_new, &bmp_x, sizeof(BitmapImage));
			memset(bmp_new + 1, 0, sizeof(BitmapRBGA) * 2);
			retV->image = bmp_new;
		};

		return retV;
	};

	TPointer<Bitmap> Bitmap::loadImage(char *name) {
		TPointer<Bitmap> retV;
		File in;

		BitmapImage bmp_x;
		BitmapImage *p_bmp;
		uint32_t b_sz;

		p_bmp = NULL;

		if (in.openRead(name)) {
			in.read(&bmp_x, sizeof(BitmapImage));
			if ((bmp_x.ih.biBitCount == 0) && (bmp_x.ih.biPlanes != 0)) {
				bmp_x.ih.biBitCount = bmp_x.ih.biPlanes;
				bmp_x.ih.biPlanes = 1;
			};
			if (bmp_x.fh.bfType == XYO_PIXEL32_BITMAP_FILE_ID) {
				if ((bmp_x.fh.bfSize == 0) || (bmp_x.ih.biSizeImage == 0)) {
					calculateImageSizeNoCompression(bmp_x.fh, bmp_x.ih);
				};
				if (bmp_x.fh.bfSize >= sizeof(BitmapImage)) {
					p_bmp = (BitmapImage *)new uint8_t[bmp_x.fh.bfSize];
					b_sz = in.read(&p_bmp[1], bmp_x.fh.bfSize - sizeof(BitmapImage));
					if (b_sz == (bmp_x.fh.bfSize - sizeof(BitmapImage))) {
						memcpy(p_bmp, &bmp_x, sizeof(BitmapImage));
					} else {
						delete[] ((uint8_t *)p_bmp);
						p_bmp = NULL;
					};
				};
			};

			in.close();
		};

		if (p_bmp) {
			retV.newMemory();
			retV->image = p_bmp;
		};
		return retV;
	};

	bool Bitmap::saveImage(char *name) {
		File out;

		uint32_t b_sz;

		if (out.openWrite(name)) {
			if ((image->fh.bfSize == 0) || (image->ih.biSizeImage == 0)) {
				calculateImageSizeNoCompression(image->fh, image->ih);
			};
			b_sz = out.write(image, image->fh.bfSize);
			out.close();
			if (b_sz == image->fh.bfSize) {
				return true;
			};
		};
		return false;
	};

	uint32_t Bitmap::scanLine(BitmapInfoHeader &bih) {

		uint32_t scan_line;
		scan_line = (bih.biPlanes) * (bih.biBitCount);
		scan_line *= (bih.biWidth);
		if (scan_line % 32) {
			scan_line += 32 - scan_line % 32;
		}
		scan_line /= 8;
		return scan_line;
	};

	void Bitmap::calculateImageSizeNoCompression(BitmapFileHeader &bfh, BitmapInfoHeader &bih) {

		uint32_t bmp_palette_size;
		uint32_t bmp_bits;
		uint32_t bmp_scan_line;

		bmp_scan_line = scanLine(bih);
		bmp_bits = (bih.biPlanes) * (bih.biBitCount);
		bmp_palette_size = 0;
		if (bih.biBitCount * bih.biPlanes == 1) {
			bmp_palette_size = 2 * sizeof(BitmapRBGA);
		}
		if (bih.biBitCount * bih.biPlanes == 4) {
			bmp_palette_size = 16 * sizeof(BitmapRBGA);
		}
		if (bih.biBitCount * bih.biPlanes == 8) {
			bmp_palette_size = 256 * sizeof(BitmapRBGA);
		}

		bfh.bfOffBits = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + bmp_palette_size;
		bfh.bfSize = bfh.bfOffBits + bmp_scan_line * (bih.biHeight);

		bih.biSizeImage = sizeof(BitmapInfoHeader) + bmp_palette_size + bmp_scan_line * (bih.biHeight);
	};

	BitmapRBGA *Bitmap::getRow32Bits(uint32_t y, uint32_t scanLine) {
		return (BitmapRBGA *)(((uint8_t *)(image + 1)) + (image->ih.biHeight - y - 1) * scanLine);
	};

	uint32_t Bitmap::getScanLine() {
		return scanLine(image->ih);
	};

	void Bitmap::setPixel32(uint32_t x, uint32_t y, BitmapRBGA &c) {

		uint32_t scan_line;
		BitmapRBGA *pixels;
		scan_line = scanLine(image->ih);
		pixels = (BitmapRBGA *)(((uint8_t *)(image + 1)) + x * sizeof(BitmapRBGA) + y * scan_line);
		pixels->rgbBlue = c.rgbBlue;
		pixels->rgbRed = c.rgbRed;
		pixels->rgbGreen = c.rgbGreen;
		pixels->rgbAlpha = c.rgbAlpha;
	};

	void Bitmap::setPixel24(uint32_t x, uint32_t y, BitmapRBG &c) {
		uint32_t scan_line;
		BitmapRBG *pixels;

		scan_line = scanLine(image->ih);
		pixels = (BitmapRBG *)(((uint8_t *)(image + 1)) + x * sizeof(BitmapRBG) + y * scan_line);
		pixels->rgbtBlue = c.rgbtBlue;
		pixels->rgbtRed = c.rgbtRed;
		pixels->rgbtGreen = c.rgbtGreen;
	};

	void Bitmap::setPixel8(uint32_t x, uint32_t y, uint8_t &c) {

		uint32_t scan_line;
		uint8_t *pixels;
		scan_line = scanLine(image->ih);
		pixels = (uint8_t *)(((uint8_t *)(image + 1)) + x + y * scan_line + 256 * sizeof(BitmapRBGA));
		*pixels = c;
	};

	void Bitmap::setPixel4(uint32_t x, uint32_t y, uint8_t &c) {
		uint32_t scan_line;
		uint8_t *pixels;
		scan_line = scanLine(image->ih);
		pixels = (uint8_t *)(((uint8_t *)(image + 1)) + (x >> 1) + y * scan_line + 16 * sizeof(BitmapRBGA));

		if (x & 0x0001) {
			*pixels = ((*pixels) & 0xF0) | ((c)&0x0F);
		} else {
			*pixels = ((*pixels) & 0x0F) | (((c)&0x0F) << 4);
		};
	};

	void Bitmap::setPixel1(uint32_t x, uint32_t y, uint8_t &c) {
		uint32_t scan_line;
		uint8_t *pixels;
		uint8_t mask;
		uint8_t c2;
		scan_line = scanLine(image->ih);
		pixels = (uint8_t *)(((uint8_t *)(image + 1)) + (x >> 3) + y * scan_line + 2 * sizeof(BitmapRBGA));
		if (c) {
			c2 = 0xFF;
		} else {
			c2 = 0x00;
		}

		mask = (uint8_t)(0x01 << (7 - (x & 0x07)));
		*pixels = (*pixels & (~mask)) | ((c2 & mask));
	};

	void Bitmap::getPixel32(uint32_t x, uint32_t y, BitmapRBGA &c) {

		uint32_t scan_line;
		BitmapRBGA *pixels;
		scan_line = scanLine(image->ih);
		pixels = (BitmapRBGA *)(((uint8_t *)(image + 1)) + x * sizeof(BitmapRBGA) + y * scan_line);
		c.rgbBlue = pixels->rgbBlue;
		c.rgbRed = pixels->rgbRed;
		c.rgbGreen = pixels->rgbGreen;
		c.rgbAlpha = pixels->rgbAlpha;
	};

	void Bitmap::getPixel24(uint32_t x, uint32_t y, BitmapRBG &c) {

		uint32_t scan_line;
		BitmapRBG *pixels;
		scan_line = scanLine(image->ih);
		pixels = (BitmapRBG *)(((uint8_t *)(image + 1)) + x * sizeof(BitmapRBG) + y * scan_line);
		c.rgbtBlue = pixels->rgbtBlue;
		c.rgbtRed = pixels->rgbtRed;
		c.rgbtGreen = pixels->rgbtGreen;
	};

	void Bitmap::getPixel8(uint32_t x, uint32_t y, uint8_t &c) {

		uint32_t scan_line;
		uint8_t *pixels;
		scan_line = scanLine(image->ih);
		pixels = (uint8_t *)(((uint8_t *)(image + 1)) + x + y * scan_line + 256 * sizeof(BitmapRBGA));
		c = *pixels;
	};

	void Bitmap::getPixel4(uint32_t x, uint32_t y, uint8_t &c) {

		uint32_t scan_line;
		uint8_t *pixels;

		scan_line = scanLine(image->ih);
		pixels = (uint8_t *)(((uint8_t *)(image + 1)) + (x >> 1) + y * scan_line + 16 * sizeof(BitmapRBGA));

		if (x & 0x0001) {
			c = (*pixels) & 0x0F;
		} else {
			c = *pixels & 0xF0;
			c >>= 4;
			c &= 0x0F;
		};
	};

	void Bitmap::getPixel1(uint32_t x, uint32_t y, uint8_t &c) {

		uint32_t scan_line;
		uint8_t *pixels;
		uint8_t mask;
		uint8_t c2;

		scan_line = scanLine(image->ih);
		pixels = (uint8_t *)(((uint8_t *)(image + 1)) + (x / 8) + y * scan_line + 2 * sizeof(BitmapRBGA));
		mask = (uint8_t)(0x01 << (7 - x & 0x07));
		c2 = (*pixels & mask);
		if (c2) {
			c = 1;
		} else {
			c = 0;
		}
	};

	void Bitmap::getPixelPal8(uint32_t x, uint32_t y, BitmapRBGA &c) {

		uint8_t c2;
		getPixel8(x, y, c2);
		memcpy(&c, &((BitmapRBGA *)(image + 1))[c2], sizeof(BitmapRBGA));
	};

	void Bitmap::getPixelPal4(uint32_t x, uint32_t y, BitmapRBGA &c) {

		uint8_t c2;

		getPixel4(x, y, c2);

		memcpy(&c, &((BitmapRBGA *)(image + 1))[c2], sizeof(BitmapRBGA));
	};

	void Bitmap::getPixelPal1(uint32_t x, uint32_t y, BitmapRBGA &c) {

		uint8_t c2;

		getPixel1(x, y, c2);
		memcpy(&c, &((BitmapRBGA *)(image + 1))[c2], sizeof(BitmapRBGA));
	};

	void Bitmap::setPixelPal8(uint32_t x, uint32_t y, BitmapRBGA &c) {

		uint16_t index;
		uint8_t c2;
		BitmapRBGA *palette;

		palette = (BitmapRBGA *)(image + 1);
		for (index = 0; index < 256; index++) {
			if ((c.rgbBlue == palette[index].rgbBlue) && (c.rgbRed == palette[index].rgbRed) && (c.rgbGreen == palette[index].rgbGreen) && (c.rgbAlpha == palette[index].rgbAlpha)) {
				break;
			}
		};
		c2 = (uint8_t)index;
		setPixel8(x, y, c2);
	};

	void Bitmap::setPixelPal4(uint32_t x, uint32_t y, BitmapRBGA &c) {

		uint16_t index;
		uint8_t c2;
		BitmapRBGA *palette;

		palette = (BitmapRBGA *)(image + 1);
		for (index = 0; index < 16; index++) {
			if ((c.rgbBlue == palette[index].rgbBlue) && (c.rgbRed == palette[index].rgbRed) && (c.rgbGreen == palette[index].rgbGreen) && (c.rgbAlpha == palette[index].rgbAlpha)) {
				break;
			}
		};
		c2 = (uint8_t)index;

		setPixel4(x, y, c2);
	};

	void Bitmap::setPixelPal1(uint32_t x, uint32_t y, BitmapRBGA &c) {

		uint16_t index;
		uint8_t c2;
		BitmapRBGA *palette;

		palette = (BitmapRBGA *)(image + 1);
		for (index = 0; index < 2; index++) {
			if ((c.rgbBlue == palette[index].rgbBlue) && (c.rgbRed == palette[index].rgbRed) && (c.rgbGreen == palette[index].rgbGreen) && (c.rgbAlpha == palette[index].rgbAlpha)) {
				break;
			}
		};
		c2 = (uint8_t)index;
		setPixel1(x, y, c2);
	};

	uint16_t Bitmap::getPaletteSize() {

		if (image->ih.biBitCount * image->ih.biPlanes == 1) {
			return 2;
		}
		if (image->ih.biBitCount * image->ih.biPlanes == 4) {
			return 16;
		}
		if (image->ih.biBitCount * image->ih.biPlanes == 8) {
			return 256;
		}
		return 0;
	};

	void Bitmap::getPaletteIndex(uint8_t index, BitmapRBGA &c) {

		BitmapRBGA *palette;

		palette = (BitmapRBGA *)(image + 1);
		c.rgbBlue = palette[index].rgbBlue;
		c.rgbRed = palette[index].rgbRed;
		c.rgbGreen = palette[index].rgbGreen;
		c.rgbAlpha = palette[index].rgbAlpha;
	};

	void Bitmap::setPaletteIndex(uint8_t index, BitmapRBGA &c) {

		BitmapRBGA *palette;

		palette = (BitmapRBGA *)(image + 1);
		palette[index].rgbBlue = c.rgbBlue;
		palette[index].rgbRed = c.rgbRed;
		palette[index].rgbGreen = c.rgbGreen;
		palette[index].rgbAlpha = c.rgbAlpha;
	};

	bool Bitmap::getPaletteColor(uint8_t &index, BitmapRBGA &c) {

		uint16_t index2;
		uint16_t index2p;

		BitmapRBGA *palette;

		palette = (BitmapRBGA *)(image + 1);
		index2p = getPaletteSize();
		for (index2 = 0; index2 < index2p; index2++) {
			if ((c.rgbBlue == palette[index2].rgbBlue) && (c.rgbRed == palette[index2].rgbRed) && (c.rgbGreen == palette[index2].rgbGreen) && (c.rgbAlpha == palette[index2].rgbAlpha)) {
				break;
			}
		};
		index = (uint8_t)index2;
		if (index < index2p) {
			return true;
		}
		return false;
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

		if (getPixelWidth() < 16) {
			return true;
		}
		return false;
	};

	void Bitmap::getPixel32s(long int x, long int y, BitmapRBGA &c) {
		uint32_t scanLine_;
		BitmapRBGA *pixels;

		if (x < 0) {
			c.rgbBlue = 0;
			c.rgbRed = 0;
			c.rgbGreen = 0;
			c.rgbAlpha = 0;
			return;
		};

		if (y < 0) {
			c.rgbBlue = 0;
			c.rgbRed = 0;
			c.rgbGreen = 0;
			c.rgbAlpha = 0;
			return;
		};

		if (x >= (long)image->ih.biWidth) {
			c.rgbBlue = 0;
			c.rgbRed = 0;
			c.rgbGreen = 0;
			c.rgbAlpha = 0;
			return;
		};

		if (y >= (long)image->ih.biHeight) {
			c.rgbBlue = 0;
			c.rgbRed = 0;
			c.rgbGreen = 0;
			c.rgbAlpha = 0;
			return;
		};

		scanLine_ = scanLine(image->ih);
		pixels = (BitmapRBGA *)(((uint8_t *)(image + 1)) + x * sizeof(BitmapRBGA) + y * scanLine_);
		c.rgbBlue = pixels->rgbBlue;
		c.rgbRed = pixels->rgbRed;
		c.rgbGreen = pixels->rgbGreen;
		c.rgbAlpha = pixels->rgbAlpha;
	};

	void Bitmap::setPixel32s(long int x, long int y, BitmapRBGA &c) {
		uint32_t scanLine_;
		BitmapRBGA *pixels;

		if (x < 0) {
			return;
		}
		if (y < 0) {
			return;
		}
		if (x >= (long)image->ih.biWidth) {
			return;
		}
		if (y >= (long)image->ih.biHeight) {
			return;
		}

		scanLine_ = scanLine(image->ih);
		pixels = (BitmapRBGA *)(((uint8_t *)(image + 1)) + x * sizeof(BitmapRBGA) + y * scanLine_);
		pixels->rgbBlue = c.rgbBlue;
		pixels->rgbRed = c.rgbRed;
		pixels->rgbGreen = c.rgbGreen;
		pixels->rgbAlpha = c.rgbAlpha;
	};

	void Bitmap::getPixel24X(uint32_t x, uint32_t y, BitmapRBGA &c) {
		uint32_t scan_line;
		BitmapRBG *pixels;
		scan_line = scanLine(image->ih);
		pixels = (BitmapRBG *)(((uint8_t *)(image + 1)) + x * sizeof(BitmapRBG) + y * scan_line);
		c.rgbBlue = pixels->rgbtBlue;
		c.rgbRed = pixels->rgbtRed;
		c.rgbGreen = pixels->rgbtGreen;
		c.rgbAlpha = 0;
	};

	void Bitmap::getPixel32X(uint32_t x, uint32_t y, BitmapRBGA &retV) {
		switch (getPixelWidth()) {
		case 1:
			getPixelPal1(x, y, retV);
			return;
		case 4:
			getPixelPal4(x, y, retV);
			return;
		case 8:
			getPixelPal8(x, y, retV);
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
		BitmapRBGA rgba;
		uint32_t x;
		uint32_t y;
		for (x = 0; x < image->ih.biWidth; ++x) {
			for (y = 0; y < image->ih.biHeight; ++y) {
				getPixel32X(x, y, rgba);
				retV->setPixel32(x, y, rgba);
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

	void Bitmap::swapRBInvertA32() {
		uint32_t y;
		uint32_t x;
		uint32_t scan_line;
		BitmapRBGA *pixels;
		scan_line = scanLine(image->ih);
		for (y = 0; y < image->ih.biHeight; ++y) {
			pixels = (BitmapRBGA *)(((uint8_t *)(image + 1)) + y * scan_line);
			for (x = 0; x < image->ih.biWidth; ++x) {
				pixels[x].rgbBlue ^= pixels[x].rgbRed;
				pixels[x].rgbRed ^= pixels[x].rgbBlue;
				pixels[x].rgbBlue ^= pixels[x].rgbRed;
				pixels[x].rgbAlpha ^= 255;
			};
		};
	};

	void Bitmap::setAlpha32(uint8_t alpha) {
		uint32_t y;
		uint32_t x;
		uint32_t scan_line;
		BitmapRBGA *pixels;
		scan_line = scanLine(image->ih);
		for (y = 0; y < image->ih.biHeight; ++y) {
			pixels = (BitmapRBGA *)(((uint8_t *)(image + 1)) + y * scan_line);
			for (x = 0; x < image->ih.biWidth; ++x) {
				pixels[x].rgbAlpha = alpha;
			};
		};
	};

};
