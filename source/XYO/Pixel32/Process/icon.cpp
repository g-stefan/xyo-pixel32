// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	static uint32_t iconPaletteEntries(uint32_t bits) {
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

	static uint8_t *iconPalette(BitmapImage *image) {
		return ((uint8_t *)image) + sizeof(BitmapFileHeader) + image->ih.biSize;
	};

	static uint8_t *iconPixels(BitmapImage *image) {
		return ((uint8_t *)image) + image->fh.bfOffBits;
	};

	struct IconEntry {
			BitmapImage *image;
			BitmapImage *mask;
			uint32_t bits;
			uint32_t paletteSize;
			uint32_t pixelSize;
			uint32_t maskSize;
			uint32_t size;
	};

	static bool iconEntry(IconItem *item, IconEntry &entry) {
		if (!item || !item->bmp || !item->mask) {
			return false;
		};
		entry.image = item->bmp->getBitmapImage();
		entry.mask = item->mask->getBitmapImage();
		if (!entry.image || !entry.mask) {
			return false;
		};
		uint32_t width = entry.image->ih.biWidth;
		uint32_t height = entry.image->ih.biHeight;
		if ((width == 0) || (height == 0) || (width > 256) || (height > 256)) {
			return false;
		};
		if ((entry.mask->ih.biWidth != width) || (entry.mask->ih.biHeight != height) || (item->mask->getPixelWidth() != 1)) {
			return false;
		};
		entry.bits = item->bmp->getPixelWidth();
		if ((entry.bits != 1) && (entry.bits != 4) && (entry.bits != 8) && (entry.bits != 24) && (entry.bits != 32)) {
			return false;
		};
		entry.paletteSize = iconPaletteEntries(entry.bits) * sizeof(BitmapRGBA);
		entry.pixelSize = item->bmp->getScanLine() * height;
		entry.maskSize = item->mask->getScanLine() * height;
		entry.size = sizeof(BitmapInfoHeader) + entry.paletteSize + entry.pixelSize + entry.maskSize;
		return true;
	};

	bool generateIcon(TDoubleEndedQueue<TPointer<IconItem>> &itemList, const char *fileName) {
		uint16_t iconReserved;
		uint16_t iconType;
		uint16_t iconCount;

		uint32_t iconFileOffset;

		uint8_t bmpWidth;
		uint8_t bmpHeight;
		uint8_t bmpColorCount;
		uint8_t bmpReserved;
		uint16_t bmpPlanes;
		uint16_t bmpBitCount;

		BitmapInfoHeader bmpIh;
		IconEntry entry;

		TDoubleEndedQueue<TPointer<IconItem>>::Node *item;
		File out;
		bool isOk;

		iconReserved = 0x0000;
		iconType = 0x0001;
		iconCount = 0;
		for (item = itemList.tail; item != NULL; item = item->back) {
			if (!iconEntry(item->value, entry)) {
				return false;
			};
			if (iconCount == 0xFFFF) {
				return false;
			};
			++iconCount;
		};
		if (iconCount == 0) {
			return false;
		};

		if (!out.openWrite(fileName)) {
			return false;
		};

		isOk = true;
		isOk = isOk && (out.write(&iconReserved, sizeof(iconReserved)) == sizeof(iconReserved));
		isOk = isOk && (out.write(&iconType, sizeof(iconType)) == sizeof(iconType));
		isOk = isOk && (out.write(&iconCount, sizeof(iconCount)) == sizeof(iconCount));

		iconFileOffset = 6 + iconCount * 16;
		for (item = itemList.tail; (item != NULL) && isOk; item = item->back) {
			iconEntry(item->value, entry);

			// 256 is stored as 0
			bmpWidth = (uint8_t)(entry.image->ih.biWidth & 0xFF);
			bmpHeight = (uint8_t)(entry.image->ih.biHeight & 0xFF);
			bmpColorCount = (entry.bits < 8) ? (uint8_t)iconPaletteEntries(entry.bits) : 0;
			bmpReserved = 0;
			bmpPlanes = 1;
			bmpBitCount = (uint16_t)entry.bits;

			isOk = isOk && (out.write(&bmpWidth, sizeof(bmpWidth)) == sizeof(bmpWidth));
			isOk = isOk && (out.write(&bmpHeight, sizeof(bmpHeight)) == sizeof(bmpHeight));
			isOk = isOk && (out.write(&bmpColorCount, sizeof(bmpColorCount)) == sizeof(bmpColorCount));
			isOk = isOk && (out.write(&bmpReserved, sizeof(bmpReserved)) == sizeof(bmpReserved));
			isOk = isOk && (out.write(&bmpPlanes, sizeof(bmpPlanes)) == sizeof(bmpPlanes));
			isOk = isOk && (out.write(&bmpBitCount, sizeof(bmpBitCount)) == sizeof(bmpBitCount));
			isOk = isOk && (out.write(&entry.size, sizeof(entry.size)) == sizeof(entry.size));
			isOk = isOk && (out.write(&iconFileOffset, sizeof(iconFileOffset)) == sizeof(iconFileOffset));

			iconFileOffset += entry.size;
		};

		for (item = itemList.tail; (item != NULL) && isOk; item = item->back) {
			iconEntry(item->value, entry);

			// Icon images always use BITMAPINFOHEADER, the height covers image and mask
			memcpy(&bmpIh, &entry.image->ih, sizeof(BitmapInfoHeader));
			bmpIh.biSize = sizeof(BitmapInfoHeader);
			bmpIh.biHeight *= 2;
			bmpIh.biPlanes = 1;
			bmpIh.biBitCount = (uint16_t)entry.bits;
			bmpIh.biCompression = BitmapCompression::RGB;
			bmpIh.biSizeImage = entry.pixelSize + entry.maskSize;
			bmpIh.biClrUsed = 0;
			bmpIh.biClrImportant = 0;

			isOk = isOk && (out.write(&bmpIh, sizeof(BitmapInfoHeader)) == sizeof(BitmapInfoHeader));
			if (entry.paletteSize) {
				isOk = isOk && (out.write(iconPalette(entry.image), entry.paletteSize) == entry.paletteSize);
			};
			isOk = isOk && (out.write(iconPixels(entry.image), entry.pixelSize) == entry.pixelSize);
			isOk = isOk && (out.write(iconPixels(entry.mask), entry.maskSize) == entry.maskSize);
		};

		out.close();
		return isOk;
	};

};
