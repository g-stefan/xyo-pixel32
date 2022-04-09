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

				BmpInfoHeader bmpIh;
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

						bmpWidth = (item->value->bmp->getBmpImage())->ih.biWidth;
						bmpHeight = (item->value->bmp->getBmpImage())->ih.biHeight;
						bmpColorCount = 0;
						bmpReserved = 0;
						bmpPlanes = (item->value->bmp->getBmpImage())->ih.biPlanes;
						bmpBitCount = (item->value->bmp->getBmpImage())->ih.biBitCount;
						bmpSizeInBytes = sizeof(BmpInfoHeader);
						// XOR Mask
						bmpBitsPerPixel = bmpPlanes * bmpBitCount;
						bmpScanLineWidth = bmpBitsPerPixel * (item->value->bmp->getBmpImage())->ih.biWidth;
						if (bmpScanLineWidth % 32) {
							bmpScanLineWidth += 32 - bmpScanLineWidth % 32;
						};
						bmpScanLineWidth /= 8;
						bmpSizeInBytes += bmpScanLineWidth * (item->value->bmp->getBmpImage())->ih.biHeight;
						bmpColorCount = 0;
						if (bmpBitsPerPixel == 1) {
							bmpSizeInBytes += 2 * sizeof(BmpRgbQuad);
							bmpColorCount = 2;
						};
						if (bmpBitsPerPixel == 4) {
							bmpSizeInBytes += 16 * sizeof(BmpRgbQuad);
							bmpColorCount = 16;
						};
						if (bmpBitsPerPixel == 8) {
							bmpSizeInBytes += 256 * sizeof(BmpRgbQuad);
							bmpColorCount = 0;
						};
						// AND Mask
						bmpScanLineWidth = (item->value->bmp->getBmpImage())->ih.biWidth;
						if (bmpScanLineWidth % 32) {
							bmpScanLineWidth += 32 - bmpScanLineWidth % 32;
						};
						bmpScanLineWidth /= 8;
						bmpSizeInBytes += bmpScanLineWidth * (item->value->bmp->getBmpImage())->ih.biHeight;

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
						memcpy(&bmpIh, &(item->value->bmp->getBmpImage())->ih, sizeof(BmpInfoHeader));
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
						fwrite(&bmpIh, 1, sizeof(BmpInfoHeader), out);
						fwrite(((uint8_t *)(item->value->bmp->getBmpImage())) + sizeof(BmpImage), 1, item->value->bmp->getScanLine() * bmpIh.biHeight / 2 + bmpPalSize * sizeof(BmpRgbQuad), out);
						fwrite(((uint8_t *)(item->value->mask->getBmpImage())) + sizeof(BmpImage) + sizeof(BmpRgbQuad) * 2, 1, item->value->mask->getScanLine() * bmpIh.biHeight / 2, out);
					};

					fclose(out);
					return true;
				};
				return false;
			};

		};
	};
};
