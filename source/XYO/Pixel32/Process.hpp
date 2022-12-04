// Pixel32
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_PIXEL32_PROCESS_HPP
#define XYO_PIXEL32_PROCESS_HPP

#ifndef XYO_PIXEL32_IMAGE_HPP
#	include <XYO/Pixel32/Image.hpp>
#endif

#ifndef XYO_PIXEL32_BMP_HPP
#	include <XYO/Pixel32/Bmp.hpp>
#endif

#ifndef XYO_PIXEL32_ICON_HPP
#	include <XYO/Pixel32/Icon.hpp>
#endif

#ifndef XYO_PIXEL32_KERNEL3X3_HPP
#	include <XYO/Pixel32/Kernel3x3.hpp>
#endif

namespace XYO::Pixel32::Process {

			XYO_PIXEL32_EXPORT TPointer<Image> create(long int width, long int height);
			XYO_PIXEL32_EXPORT TPointer<Image> pngLoad(const char *);
			XYO_PIXEL32_EXPORT bool pngSave(Image *, const char *);
			XYO_PIXEL32_EXPORT Pixel getPixel(Image *imgThis, long int x, long int y);
			XYO_PIXEL32_EXPORT void setPixel(Image *imgThis, long int x, long int y, Pixel color);
			XYO_PIXEL32_EXPORT Pixel getPixelX(Image *imgThis, long int x, long int y);
			//
			inline double interpolateCubic(double v0, double v1, double v2, double v3, double m) {
				double a0 = v3 - v2 - v0 + v1;
				double a1 = v0 - v1 - a0;
				double a2 = v2 - v0;
				double a3 = v1;
				double mm = m * m;
				return a0 * m * mm + a1 * mm + a2 * m + a3;
			};

			inline double interpolateLinear(double v0, double v1, double m) {
				return v0 * (1 - m) + v1 * m;
			};

			inline double interpolateNearestNeighbor(double v0, double v1, double m) {
				if (m <= 0.5) {
					return v0;
				};
				return v1;
			};

			inline int pixelClampX(int x) {
				if (x < 0) {
					return 0;
				};
				if (x > 255) {
					return 255;
				};
				return x;
			};

			inline Pixel alphaBlending(Pixel x1, Pixel x2) {
				long int a, r, g, b;
				a = XYO_PIXEL32_A(x1) + (XYO_PIXEL32_A(x2) * (255 - XYO_PIXEL32_A(x1))) / 255;
				if (a == 0) {
					return 0;
				};
				r = (XYO_PIXEL32_R(x1) * XYO_PIXEL32_A(x1) + ((XYO_PIXEL32_R(x2) * XYO_PIXEL32_A(x2)) * (255 - XYO_PIXEL32_A(x1))) / 255) / a;
				g = (XYO_PIXEL32_G(x1) * XYO_PIXEL32_A(x1) + ((XYO_PIXEL32_G(x2) * XYO_PIXEL32_A(x2)) * (255 - XYO_PIXEL32_A(x1))) / 255) / a;
				b = (XYO_PIXEL32_B(x1) * XYO_PIXEL32_A(x1) + ((XYO_PIXEL32_B(x2) * XYO_PIXEL32_A(x2)) * (255 - XYO_PIXEL32_A(x1))) / 255) / a;

				return XYO_PIXEL32_PIXEL(r, g, b, a);
			};

			//
			XYO_PIXEL32_EXPORT TPointer<Image> kernel3X3(Image *imgThis, Kernel3X3 &kernel);
			XYO_PIXEL32_EXPORT TPointer<Image> scaleUpBicubic(Image *imgThis, long int nx, long int ny);
			XYO_PIXEL32_EXPORT TPointer<Image> scaleUpBilinear(Image *imgThis, long int nx, long int ny);
			XYO_PIXEL32_EXPORT TPointer<Image> scaleUpNearestNeighbor(Image *imgThis, long int nx, long int ny);
			XYO_PIXEL32_EXPORT TPointer<Image> scaleDownX2(Image *imgThis);
			XYO_PIXEL32_EXPORT TPointer<Image> scaleDownX2OnX(Image *imgThis);
			XYO_PIXEL32_EXPORT TPointer<Image> scaleDownX2OnY(Image *imgThis);
			XYO_PIXEL32_EXPORT TPointer<Image> scaleDown(Image *imgThis, long int nx, long int ny);
			XYO_PIXEL32_EXPORT TPointer<Image> scaleUp(Image *imgThis, long int nx, long int ny);
			XYO_PIXEL32_EXPORT TPointer<Image> resize(Image *imgThis, long int nx, long int ny);
			XYO_PIXEL32_EXPORT TPointer<Image> cut(Image *imgThis, long int sx, long int sy, long int lx, long int ly);
			XYO_PIXEL32_EXPORT TPointer<Image> wrap(Image *imgThis, long int dx, long int dy);
			XYO_PIXEL32_EXPORT TPointer<Image> wrapBox(Image *imgThis, long int dx, long int dy);
			//
			XYO_PIXEL32_EXPORT void average(Image *imgInOut1, Image *imgIn2, uint32_t level1, uint32_t level2, uint32_t average);
			XYO_PIXEL32_EXPORT void blend(Image *imgInOut1, Image *imgIn2, long int dx, long int dy, long int sx, long int sy, long int lx, long int ly);
			XYO_PIXEL32_EXPORT void copy(Image *imgThis, Image *imgIn2, long int dx, long int dy, long int sx, long int sy, long int lx, long int ly);
			XYO_PIXEL32_EXPORT void clear(Image *imgThis, Pixel pixel);
			XYO_PIXEL32_EXPORT void noise(Image *imgIn, RandomMT &rnd);
			XYO_PIXEL32_EXPORT void noise2Bit(Image *imgIn, RandomMT &rnd);
			XYO_PIXEL32_EXPORT void drawRectangle(Image *imgThis, long int sx, long int sy, long int lx, long int ly, Pixel pixel);
			XYO_PIXEL32_EXPORT void drawFilledRectangle(Image *imgThis, long int sx, long int sy, long int lx, long int ly, Pixel pixel);
			XYO_PIXEL32_EXPORT void colorRescale(Image *imgInOut);
			//
			XYO_PIXEL32_EXPORT TPointer<Bmp> bmp32LoadPng(const char *name);
			XYO_PIXEL32_EXPORT bool bmp32SavePng(Bmp *bmp, const char *name);
			XYO_PIXEL32_EXPORT bool bmp32Alpha1(Bmp *inBmp32, TPointer<Bmp> &outBmp1, int level);
			XYO_PIXEL32_EXPORT bool bmp32To24Alpha8(Bmp *inBmp32, TPointer<Bmp> &outBmp24, TPointer<Bmp> &outBmp8);
			XYO_PIXEL32_EXPORT bool bmp32To8Alpha1(Bmp *inBmp32, TPointer<Bmp> &outBmp8, TPointer<Bmp> &outBmp1, int level, bool &noFreeColorsLeft);
			XYO_PIXEL32_EXPORT bool bmp32To4Alpha1(Bmp *inBmp32, TPointer<Bmp> &outBmp4, TPointer<Bmp> &outBmp1, int level, bool &noFreeColorsLeft);
			XYO_PIXEL32_EXPORT TPointer<Bmp> alphaToBmp8(Image *inImage);
			XYO_PIXEL32_EXPORT TPointer<Bmp> alphaToBmp1(Image *inImage, int level);
			XYO_PIXEL32_EXPORT TPointer<Bmp> toBmp24(Image *inImage);
			XYO_PIXEL32_EXPORT TPointer<Bmp> toBmp32(Image *inImage);
			XYO_PIXEL32_EXPORT void backgroundAlpha(Image *inOutImage, Pixel background);
			XYO_PIXEL32_EXPORT void backgroundAlphaLevel(Image *inOutImage, Pixel background, int level);
			XYO_PIXEL32_EXPORT bool generateIcon(TDoubleEndedQueue<TPointer<IconItem>> &itemList, const char *fileName);
			XYO_PIXEL32_EXPORT bool pngToIcon(const char *pngFile, const char *iconFile, int level, bool useBackgroundAlpha, uint32_t background);
			XYO_PIXEL32_EXPORT bool pngToIcon(const char *pngFile48, const char *pngFile32, const char *pngFile24, const char *pngFile16, const char *iconFile, int level, bool useBackgroundAlpha, uint32_t background);
			XYO_PIXEL32_EXPORT bool pngToIcon(TDynamicArray<String> &pngFile, const char *iconFile, int level, bool useBackgroundAlpha, uint32_t background);

		};

#endif
