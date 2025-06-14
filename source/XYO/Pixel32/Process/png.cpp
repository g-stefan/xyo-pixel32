// Pixel32
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include "png.h"
#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	static void PNGAPI pngError(png_structp png, png_const_charp sz) {
		png;
		sz;
	};

	static void PNGAPI pngWarning(png_structp png, png_const_charp sz) {
		png;
		sz;
	};

	TPointer<Image> pngLoad(const char *name) {
		FILE *in;
		TPointer<Image> retV;
		in = fopen(name, "rb");
		if (in != NULL) {
			uint8_t pngHeader[8];
			if (fread(pngHeader, 1, 8, in) == 8) {
				if (png_sig_cmp(pngHeader, 0, 8) == 0) {
					png_structp png;
					png_infop info;

					png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, pngError, pngWarning);
					if (png != NULL) {
						info = png_create_info_struct(png);
						if (info != NULL) {
							png_uint_32 width;
							png_uint_32 height;
							int bitDepth;
							int colorType;
							double gamma;

							png_init_io(png, in);
							png_set_sig_bytes(png, 8);
							png_read_info(png, info);

							png_get_IHDR(png, info, &width, &height, &bitDepth, &colorType, NULL, NULL, NULL);

							if (colorType == PNG_COLOR_TYPE_PALETTE) {
								png_set_expand(png);
							} else if ((colorType == PNG_COLOR_TYPE_GRAY) && (bitDepth < 8)) {
								png_set_expand(png);
							} else if (png_get_valid(png, info, PNG_INFO_tRNS)) {
								png_set_expand(png);
							} else if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA) {
								png_set_gray_to_rgb(png);
							}
							if (bitDepth == 16) {
								png_set_strip_16(png);
							}
							png_read_update_info(png, info);

							retV = create(width, height);

							int y;
							png_read_image(png, (png_bytep *)retV->pixel);
							png_read_end(png, NULL);

							if (colorType != PNG_COLOR_TYPE_RGB_ALPHA) {
								int x;
								int p;
								for (y = 0; y < height; ++y) {
									p = 3 * width;
									for (x = 4 * width; x >= 4;) {
										p -= 3;
										x -= 4;
										((uint8_t *)(retV->pixel[y]))[x + 3] = 0xFF;
										((uint8_t *)(retV->pixel[y]))[x + 2] = ((uint8_t *)(retV->pixel[y]))[p + 2];
										((uint8_t *)(retV->pixel[y]))[x + 1] = ((uint8_t *)(retV->pixel[y]))[p + 1];
										((uint8_t *)(retV->pixel[y]))[x + 0] = ((uint8_t *)(retV->pixel[y]))[p + 0];
									};
								};
							};

							png_destroy_read_struct(&png, &info, NULL);
						} else {
							png_destroy_read_struct(&png, NULL, NULL);
						}
					}
				}
			};
			fclose(in);
		}

		return retV;
	};

	bool pngSave(Image *image, const char *name) {
		FILE *out;
		bool retV;

		retV = false;
		out = fopen(name, "wb");
		if (out != NULL) {

			png_structp png;
			png_infop info;

			png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, pngError, pngWarning);
			if (png != NULL) {
				info = png_create_info_struct(png);
				if (info != NULL) {
					png_color_8 sigBit;
					int y;
					png_bytep *rowPointers;

					png_init_io(png, out);
					png_set_compression_mem_level(png, 9);

					png_set_IHDR(png, info, image->width, image->height, 8, PNG_COLOR_TYPE_RGB_ALPHA,
					             PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

					sigBit.red = 8;
					sigBit.green = 8;
					sigBit.blue = 8;
					sigBit.alpha = 8;

					png_set_sBIT(png, info, &sigBit);

					png_write_info(png, info);

					png_write_image(png, (png_bytep *)image->pixel);
					png_write_end(png, info);
					png_destroy_write_struct(&png, &info);
					retV = true;
				} else {
					png_destroy_write_struct(&png, NULL);
				};
			};
			fclose(out);
		};
		return retV;
	};

	TPointer<Bitmap> bitmap32LoadPNG(const char *name) {
		FILE *in;
		TPointer<Bitmap> bmp;
		in = fopen(name, "rb");
		if (in != NULL) {
			uint8_t pngHeader[8];
			if (fread(pngHeader, 1, 8, in) == 8) {
				if (png_sig_cmp(pngHeader, 0, 8) == 0) {
					png_structp png;
					png_infop info;

					png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, pngError, pngWarning);
					if (png != NULL) {
						info = png_create_info_struct(png);
						if (info != NULL) {
							png_uint_32 width;
							png_uint_32 height;
							int bitDepth;
							int colorType;
							double gamma;

							png_init_io(png, in);
							png_set_sig_bytes(png, 8);
							png_read_info(png, info);

							png_get_IHDR(png, info, &width, &height, &bitDepth, &colorType, NULL, NULL, NULL);

							if (colorType == PNG_COLOR_TYPE_PALETTE) {
								png_set_expand(png);
							} else if ((colorType == PNG_COLOR_TYPE_GRAY) && (bitDepth < 8)) {
								png_set_expand(png);
							} else if (png_get_valid(png, info, PNG_INFO_tRNS)) {
								png_set_expand(png);
							} else if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA) {
								png_set_gray_to_rgb(png);
							}
							if (bitDepth == 16) {
								png_set_strip_16(png);
							}
							png_read_update_info(png, info);

							bmp = Bitmap::newImage32Bits(width, height);
							if (bmp) {
								int y;
								uint32_t scanLine;
								png_bytep *rowPointers;
								rowPointers = new png_bytep[height];
								scanLine = bmp->getScanLine();
								for (y = 0; y < height; ++y) {
									rowPointers[y] = (png_bytep)bmp->getRow32Bits(y, scanLine);
								}
								png_read_image(png, rowPointers);
								png_read_end(png, NULL);

								if (colorType != PNG_COLOR_TYPE_RGB_ALPHA) {
									int x;
									int p;
									for (y = 0; y < height; ++y) {
										p = 3 * width;
										for (x = 4 * width; x >= 4;) {
											p -= 3;
											x -= 4;
											rowPointers[y][x + 3] = 0xFF;
											rowPointers[y][x + 2] = rowPointers[y][p + 2];
											rowPointers[y][x + 1] = rowPointers[y][p + 1];
											rowPointers[y][x + 0] = rowPointers[y][p + 0];
										};
									};
								};

								delete[] rowPointers;

								bmp->swapRB32();
							};

							png_destroy_read_struct(&png, &info, NULL);
						} else {
							png_destroy_read_struct(&png, NULL, NULL);
						}
					}
				}
			}
			fclose(in);
		}

		return bmp;
	};

	bool bitmap32SavePNG(Bitmap *bmp, const char *name) {
		FILE *out;
		bool retV;

		retV = false;
		if (bmp->getPixelWidth() != 32) {
			return false;
		};

		out = fopen(name, "wb");
		if (out != NULL) {
			png_structp png;
			png_infop info;

			png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, pngError, pngWarning);
			if (png != NULL) {
				info = png_create_info_struct(png);
				if (info != NULL) {
					png_color_8 sigBit;
					int y;
					uint32_t scanLine;
					png_bytep *rowPointers;

					png_init_io(png, out);
					png_set_compression_mem_level(png, 9);

					png_set_IHDR(png, info, bmp->getWidth(), bmp->getHeight(), 8, PNG_COLOR_TYPE_RGB_ALPHA,
					             PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

					sigBit.red = 8;
					sigBit.green = 8;
					sigBit.blue = 8;
					sigBit.alpha = 8;

					png_set_sBIT(png, info, &sigBit);

					png_write_info(png, info);

					bmp->swapRB32();

					int yLn = bmp->getHeight();
					rowPointers = new png_bytep[yLn];
					scanLine = bmp->getScanLine();
					for (y = 0; y < yLn; ++y) {
						rowPointers[y] = (png_bytep)bmp->getRow32Bits(y, scanLine);
					};

					png_write_image(png, rowPointers);
					png_write_end(png, info);

					bmp->swapRB32();

					delete[] rowPointers;
					retV = true;
					png_destroy_write_struct(&png, &info);
				} else {
					png_destroy_write_struct(&png, NULL);
				};
			};
			fclose(out);
		};

		return retV;
	};

	bool pngToIcon(const char *pngFile, const char *iconFile, int level, bool useBackgroundAlpha, uint32_t background) {
		TPointer<Image> pngIn;
		pngIn = pngLoad(pngFile);
		if (pngIn) {

			if (useBackgroundAlpha) {
				backgroundAlpha(pngIn, background);
			};

			TPointer<Image> img48 = resize(pngIn, 48, 48);
			TPointer<Image> img32 = resize(pngIn, 32, 32);
			TPointer<Image> img24 = resize(pngIn, 24, 24);
			TPointer<Image> img16 = resize(pngIn, 16, 16);

			TPointer<Bitmap> bmp48x32 = toBitmap32(img48);
			TPointer<Bitmap> bitmap32x32 = toBitmap32(img32);
			TPointer<Bitmap> bmp24x32 = toBitmap32(img24);
			TPointer<Bitmap> bmp16x32 = toBitmap32(img16);

			if (useBackgroundAlpha) {
				backgroundAlphaLevel(img48, background, level);
				backgroundAlphaLevel(img32, background, level);
				backgroundAlphaLevel(img24, background, level);
				backgroundAlphaLevel(img16, background, level);
			};

			TPointer<Bitmap> bmp48x1 = alphaToBitmap1(img48, level);
			TPointer<Bitmap> bitmap32x1 = alphaToBitmap1(img32, level);
			TPointer<Bitmap> bmp24x1 = alphaToBitmap1(img24, level);
			TPointer<Bitmap> bmp16x1 = alphaToBitmap1(img16, level);

			TDoubleEndedQueue<TPointer<IconItem>> iconList;
			TPointer<IconItem> iconItem;

			iconItem.newMemory();
			iconItem->bmp = bmp16x32;
			iconItem->mask = bmp16x1;
			iconList.push(iconItem);
			iconItem.newMemory();
			iconItem->bmp = bmp24x32;
			iconItem->mask = bmp24x1;
			iconList.push(iconItem);
			iconItem.newMemory();
			iconItem->bmp = bitmap32x32;
			iconItem->mask = bitmap32x1;
			iconList.push(iconItem);
			iconItem.newMemory();
			iconItem->bmp = bmp48x32;
			iconItem->mask = bmp48x1;
			iconList.push(iconItem);

			return generateIcon(iconList, iconFile);
		};
		return false;
	};

	bool pngToIcon(const char *pngFile48, const char *pngFile32, const char *pngFile24, const char *pngFile16, const char *iconFile, int level, bool useBackgroundAlpha, uint32_t background) {
		TPointer<Image> pngIn48;
		TPointer<Image> pngIn32;
		TPointer<Image> pngIn24;
		TPointer<Image> pngIn16;
		pngIn48 = pngLoad(pngFile48);
		pngIn32 = pngLoad(pngFile32);
		pngIn24 = pngLoad(pngFile24);
		pngIn16 = pngLoad(pngFile16);
		if (pngIn48 && pngIn32 && pngIn24 && pngIn16) {

			if (useBackgroundAlpha) {
				backgroundAlpha(pngIn48, background);
				backgroundAlpha(pngIn32, background);
				backgroundAlpha(pngIn24, background);
				backgroundAlpha(pngIn16, background);
			};

			TPointer<Image> img48 = resize(pngIn48, 48, 48);
			TPointer<Image> img32 = resize(pngIn32, 32, 32);
			TPointer<Image> img24 = resize(pngIn24, 24, 24);
			TPointer<Image> img16 = resize(pngIn16, 16, 16);

			TPointer<Bitmap> bmp48x32 = toBitmap32(img48);
			TPointer<Bitmap> bitmap32x32 = toBitmap32(img32);
			TPointer<Bitmap> bmp24x32 = toBitmap32(img24);
			TPointer<Bitmap> bmp16x32 = toBitmap32(img16);

			if (useBackgroundAlpha) {
				backgroundAlphaLevel(img48, background, level);
				backgroundAlphaLevel(img32, background, level);
				backgroundAlphaLevel(img24, background, level);
				backgroundAlphaLevel(img16, background, level);
			};

			TPointer<Bitmap> bmp48x1 = alphaToBitmap1(img48, level);
			TPointer<Bitmap> bitmap32x1 = alphaToBitmap1(img32, level);
			TPointer<Bitmap> bmp24x1 = alphaToBitmap1(img24, level);
			TPointer<Bitmap> bmp16x1 = alphaToBitmap1(img16, level);

			TDoubleEndedQueue<TPointer<IconItem>> iconList;
			TPointer<IconItem> iconItem;

			iconItem.newMemory();
			iconItem->bmp = bmp16x32;
			iconItem->mask = bmp16x1;
			iconList.push(iconItem);
			iconItem.newMemory();
			iconItem->bmp = bmp24x32;
			iconItem->mask = bmp24x1;
			iconList.push(iconItem);
			iconItem.newMemory();
			iconItem->bmp = bitmap32x32;
			iconItem->mask = bitmap32x1;
			iconList.push(iconItem);
			iconItem.newMemory();
			iconItem->bmp = bmp48x32;
			iconItem->mask = bmp48x1;
			iconList.push(iconItem);

			return generateIcon(iconList, iconFile);
		};
		return false;
	};

	bool pngToIcon(TDynamicArray<String> &pngFile, const char *iconFile, int level, bool useBackgroundAlpha, uint32_t background) {
		TDynamicArray<TPointer<Image>> imgIn;
		TDynamicArray<TPointer<Bitmap>> bmpX32;
		TDynamicArray<TPointer<Bitmap>> bmpX1;

		int k;
		for (k = 0; k < pngFile.length(); ++k) {
			imgIn[k] = pngLoad(pngFile[k]);
			if (!imgIn[k]) {
				return false;
			};
		};

		if (useBackgroundAlpha) {
			for (k = 0; k < imgIn.length(); ++k) {
				backgroundAlpha(imgIn[k], background);
				backgroundAlphaLevel(imgIn[k], background, level);
			};
		};

		for (k = 0; k < imgIn.length(); ++k) {
			bmpX32[k] = toBitmap32(imgIn[k]);
			bmpX1[k] = alphaToBitmap1(imgIn[k], level);
		};

		TDoubleEndedQueue<TPointer<IconItem>> iconList;
		TPointer<IconItem> iconItem;

		for (k = 0; k < bmpX32.length(); ++k) {
			iconItem.newMemory();
			iconItem->bmp = bmpX32[k];
			iconItem->mask = bmpX1[k];
			iconList.push(iconItem);
		};

		return generateIcon(iconList, iconFile);
	};

};
