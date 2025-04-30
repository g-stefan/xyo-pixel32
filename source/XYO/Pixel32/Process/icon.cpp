// Pixel32
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

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
		uint32_t bmpSizeInBytes;

		uint32_t bmpBitsPerPixel;
		uint32_t bmpScanLineWidth;

		BitmapInfoHeader bmpIh;
		uint32_t bmpPalSize;

		TDoubleEndedQueue<TPointer<IconItem>>::Node *item;
		FILE *out;

		iconReserved = 0x0000;
		iconType = 0x0001;
		iconCount = 0;
		for (item = itemList.tail; item != NULL; item = item->back) {
			++iconCount;
		};
		out = fopen(fileName, "wb");
		if (out) {

			fwrite(&iconReserved, 1, sizeof(iconReserved), out);
			fwrite(&iconType, 1, sizeof(iconType), out);
			fwrite(&iconCount, 1, sizeof(iconCount), out);

			iconFileOffset = 6 + iconCount * 16;
			for (item = itemList.tail; item != NULL; item = item->back) {

				bmpWidth = (item->value->bmp->getBitmapImage())->ih.biWidth;
				bmpHeight = (item->value->bmp->getBitmapImage())->ih.biHeight;
				bmpColorCount = 0;
				bmpReserved = 0;
				bmpPlanes = (item->value->bmp->getBitmapImage())->ih.biPlanes;
				bmpBitCount = (item->value->bmp->getBitmapImage())->ih.biBitCount;
				bmpSizeInBytes = sizeof(BitmapInfoHeader);
				// XOR Mask
				bmpBitsPerPixel = bmpPlanes * bmpBitCount;
				bmpScanLineWidth = bmpBitsPerPixel * (item->value->bmp->getBitmapImage())->ih.biWidth;
				if (bmpScanLineWidth % 32) {
					bmpScanLineWidth += 32 - bmpScanLineWidth % 32;
				};
				bmpScanLineWidth /= 8;
				bmpSizeInBytes += bmpScanLineWidth * (item->value->bmp->getBitmapImage())->ih.biHeight;
				bmpColorCount = 0;
				if (bmpBitsPerPixel == 1) {
					bmpSizeInBytes += 2 * sizeof(BitmapRBGA);
					bmpColorCount = 2;
				};
				if (bmpBitsPerPixel == 4) {
					bmpSizeInBytes += 16 * sizeof(BitmapRBGA);
					bmpColorCount = 16;
				};
				if (bmpBitsPerPixel == 8) {
					bmpSizeInBytes += 256 * sizeof(BitmapRBGA);
					bmpColorCount = 0;
				};
				// AND Mask
				bmpScanLineWidth = (item->value->bmp->getBitmapImage())->ih.biWidth;
				if (bmpScanLineWidth % 32) {
					bmpScanLineWidth += 32 - bmpScanLineWidth % 32;
				};
				bmpScanLineWidth /= 8;
				bmpSizeInBytes += bmpScanLineWidth * (item->value->bmp->getBitmapImage())->ih.biHeight;

				fwrite(&bmpWidth, 1, sizeof(bmpWidth), out);
				fwrite(&bmpHeight, 1, sizeof(bmpHeight), out);
				fwrite(&bmpColorCount, 1, sizeof(bmpColorCount), out);
				fwrite(&bmpReserved, 1, sizeof(bmpReserved), out);
				fwrite(&bmpPlanes, 1, sizeof(bmpPlanes), out);
				fwrite(&bmpBitCount, 1, sizeof(bmpBitCount), out);
				fwrite(&bmpSizeInBytes, 1, sizeof(bmpSizeInBytes), out);
				fwrite(&iconFileOffset, 1, sizeof(iconFileOffset), out);

				iconFileOffset += bmpSizeInBytes;
			};

			for (item = itemList.tail; item != NULL; item = item->back) {
				memcpy(&bmpIh, &(item->value->bmp->getBitmapImage())->ih, sizeof(BitmapInfoHeader));
				bmpIh.biHeight *= 2;
				bmpIh.biClrUsed = 0;
				bmpIh.biSizeImage = 0;
				bmpIh.biCompression = 0;
				bmpPalSize = 0;
				bmpBitsPerPixel = bmpIh.biPlanes * bmpIh.biBitCount;
				if (bmpBitsPerPixel == 1) {
					bmpPalSize = 2;
				};
				if (bmpBitsPerPixel == 4) {
					bmpPalSize = 16;
				};
				if (bmpBitsPerPixel == 8) {
					bmpPalSize = 256;
				};
				fwrite(&bmpIh, 1, sizeof(BitmapInfoHeader), out);
				fwrite(((uint8_t *)(item->value->bmp->getBitmapImage())) + sizeof(BitmapImage), 1, item->value->bmp->getScanLine() * bmpIh.biHeight / 2 + bmpPalSize * sizeof(BitmapRBGA), out);
				fwrite(((uint8_t *)(item->value->mask->getBitmapImage())) + sizeof(BitmapImage) + sizeof(BitmapRBGA) * 2, 1, item->value->mask->getScanLine() * bmpIh.biHeight / 2, out);
			};

			fclose(out);
			return true;
		};
		return false;
	};

};
