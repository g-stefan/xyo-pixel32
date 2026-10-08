// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include "png.h"
#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	// libpng simplified API: errors are reported by return value,
	// every color type and bit depth is converted to the requested format.

	// Image pixels are uint32_t with R in the low byte
	static png_uint_32 pngFormatPixel() {
		const uint32_t test = 0x01;
		if (*((const uint8_t *)&test) == 0x01) {
			return PNG_FORMAT_RGBA;
		};
		return PNG_FORMAT_ABGR;
	};

	class PNGImage {
		public:
			png_image image;

			inline PNGImage() {
				memset(&image, 0, sizeof(image));
				image.version = PNG_IMAGE_VERSION;
			};

			inline ~PNGImage() {
				png_image_free(&image);
			};
	};

	TPointer<Image> pngLoad(const char *name) {
		PNGImage png;
		TPointer<Image> retV;

		if (!png_image_begin_read_from_file(&png.image, name)) {
			return nullptr;
		};
		png.image.format = pngFormatPixel();
		if ((png.image.width > 0x7FFFFFFF / 4) || (png.image.height > 0x7FFFFFFF)) {
			return nullptr;
		};

		try {
			retV = create(png.image.width, png.image.height);
		} catch (const std::bad_alloc &) {
			return nullptr;
		};
		if (!retV) {
			return nullptr;
		};

		if (!png_image_finish_read(&png.image, NULL, retV->pixelMap, (png_int_32)(png.image.width * 4), NULL)) {
			return nullptr;
		};

		return retV;
	};

	bool pngSave(Image *image, const char *name) {
		PNGImage png;

		if (!image || !image->pixelMap) {
			return false;
		};
		if ((image->width <= 0) || (image->height <= 0) || (image->width > 0x7FFFFFFF / 4)) {
			return false;
		};

		png.image.width = (png_uint_32)image->width;
		png.image.height = (png_uint_32)image->height;
		png.image.format = pngFormatPixel();

		return png_image_write_to_file(&png.image, name, 0, image->pixelMap, (png_int_32)(image->width * 4), NULL) != 0;
	};

	TPointer<Bitmap> bitmap32LoadPNG(const char *name) {
		PNGImage png;
		TPointer<Bitmap> bmp;

		if (!png_image_begin_read_from_file(&png.image, name)) {
			return nullptr;
		};
		png.image.format = PNG_FORMAT_BGRA;
		if ((png.image.width > 0x7FFFFFFF / 4) || (png.image.height > 0x7FFFFFFF)) {
			return nullptr;
		};

		try {
			bmp = Bitmap::newImage32Bits(png.image.width, png.image.height);
		} catch (const std::bad_alloc &) {
			return nullptr;
		};
		if (!bmp) {
			return nullptr;
		};

		// Negative stride: the buffer starts with the last row (bottom-up)
		BitmapImage *image = bmp->getBitmapImage();
		if (!png_image_finish_read(&png.image, NULL, ((uint8_t *)image) + image->fh.bfOffBits, -(png_int_32)(png.image.width * 4), NULL)) {
			return nullptr;
		};

		return bmp;
	};

	bool bitmap32SavePNG(Bitmap *bmp, const char *name) {
		PNGImage png;

		if (!bmp || !bmp->getBitmapImage()) {
			return false;
		};
		if (bmp->getPixelWidth() != 32) {
			return false;
		};
		if ((bmp->getWidth() == 0) || (bmp->getHeight() == 0) || (bmp->getWidth() > 0x7FFFFFFF / 4)) {
			return false;
		};

		png.image.width = bmp->getWidth();
		png.image.height = bmp->getHeight();
		png.image.format = PNG_FORMAT_BGRA;

		BitmapImage *image = bmp->getBitmapImage();
		return png_image_write_to_file(&png.image, name, 0, ((uint8_t *)image) + image->fh.bfOffBits, -(png_int_32)(bmp->getScanLine()), NULL) != 0;
	};

	// Color bitmap keeps the smooth alpha, the mask uses the level
	static bool addIconItem(TDoubleEndedQueue<TPointer<IconItem>> &iconList, Image *image, int level, bool useBackgroundAlpha, uint32_t background) {
		if (!image) {
			return false;
		};

		TPointer<Bitmap> bmp = toBitmap32(image);
		if (!bmp) {
			return false;
		};

		if (useBackgroundAlpha) {
			backgroundAlphaLevel(image, background, level);
		};

		TPointer<Bitmap> mask = alphaToBitmap1(image, level);
		if (!mask) {
			return false;
		};

		TPointer<IconItem> iconItem;
		iconItem.newMemory();
		iconItem->bmp = bmp;
		iconItem->mask = mask;
		iconList.push(iconItem);
		return true;
	};

	bool pngToIcon(const char *pngFile, const char *iconFile, int level, bool useBackgroundAlpha, uint32_t background) {
		TPointer<Image> pngIn = pngLoad(pngFile);
		if (!pngIn) {
			return false;
		};
		if (useBackgroundAlpha) {
			backgroundAlpha(pngIn, background);
		};

		TDoubleEndedQueue<TPointer<IconItem>> iconList;
		static const long int size[4] = {16, 24, 32, 48};
		int k;
		for (k = 0; k < 4; ++k) {
			// resize returns a new image, the input is not changed
			if (!addIconItem(iconList, resize(pngIn, size[k], size[k]), level, useBackgroundAlpha, background)) {
				return false;
			};
		};

		return generateIcon(iconList, iconFile);
	};

	bool pngToIcon(const char *pngFile48, const char *pngFile32, const char *pngFile24, const char *pngFile16, const char *iconFile, int level, bool useBackgroundAlpha, uint32_t background) {
		TPointer<Image> pngIn[4];
		pngIn[0] = pngLoad(pngFile16);
		pngIn[1] = pngLoad(pngFile24);
		pngIn[2] = pngLoad(pngFile32);
		pngIn[3] = pngLoad(pngFile48);

		TDoubleEndedQueue<TPointer<IconItem>> iconList;
		static const long int size[4] = {16, 24, 32, 48};
		int k;
		for (k = 0; k < 4; ++k) {
			if (!pngIn[k]) {
				return false;
			};
			if (useBackgroundAlpha) {
				backgroundAlpha(pngIn[k], background);
			};
			if (!addIconItem(iconList, resize(pngIn[k], size[k], size[k]), level, useBackgroundAlpha, background)) {
				return false;
			};
		};

		return generateIcon(iconList, iconFile);
	};

	bool pngToIcon(TDynamicArray<String> &pngFile, const char *iconFile, int level, bool useBackgroundAlpha, uint32_t background) {
		TDoubleEndedQueue<TPointer<IconItem>> iconList;
		TPointer<Image> imgIn;
		size_t k;

		for (k = 0; k < pngFile.length(); ++k) {
			imgIn = pngLoad(pngFile[k]);
			if (!imgIn) {
				return false;
			};
			if (useBackgroundAlpha) {
				backgroundAlpha(imgIn, background);
			};
			if (!addIconItem(iconList, imgIn, level, useBackgroundAlpha, background)) {
				return false;
			};
		};

		return generateIcon(iconList, iconFile);
	};

};
