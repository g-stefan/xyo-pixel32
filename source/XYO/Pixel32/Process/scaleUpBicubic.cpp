// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>
#include <vector>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	struct PixelPremultiplied {
			double r;
			double g;
			double b;
			double a;
	};

	static inline PixelPremultiplied premultiplied(Pixel pixel) {
		PixelPremultiplied retV;
		retV.a = XYO_PIXEL32_A(pixel);
		retV.r = XYO_PIXEL32_R(pixel) * retV.a;
		retV.g = XYO_PIXEL32_G(pixel) * retV.a;
		retV.b = XYO_PIXEL32_B(pixel) * retV.a;
		return retV;
	};

	static inline PixelPremultiplied cubic(const PixelPremultiplied *v, double m) {
		PixelPremultiplied retV;
		retV.r = interpolateCubic(v[0].r, v[1].r, v[2].r, v[3].r, m);
		retV.g = interpolateCubic(v[0].g, v[1].g, v[2].g, v[3].g, m);
		retV.b = interpolateCubic(v[0].b, v[1].b, v[2].b, v[3].b, m);
		retV.a = interpolateCubic(v[0].a, v[1].a, v[2].a, v[3].a, m);
		return retV;
	};

	// Samples outside the image repeat the edge pixels
	TPointer<Image> scaleUpBicubic(Image *imgThis, long int nx, long int ny) {
		TPointer<Image> retV;
		if ((nx < imgThis->width) || (ny < imgThis->height)) {
			return nullptr;
		};
		retV = create(nx, ny);
		if (!retV) {
			return nullptr;
		};

		long int lx = imgThis->width;
		long int ly = imgThis->height;
		double deltaX = (nx > 1) ? (double)(lx - 1) / (double)(nx - 1) : 0.0;
		double deltaY = (ny > 1) ? (double)(ly - 1) / (double)(ny - 1) : 0.0;

		// Source columns and weight for each output column
		std::vector<long int> column((size_t)nx * 4);
		std::vector<double> columnM((size_t)nx);

		long int x;
		long int y;
		long int k;
		long int kX;
		long int kY;
		long int index;
		double pX;
		double pY;
		double mY;

		for (x = 0; x < nx; ++x) {
			pX = (double)x * deltaX;
			kX = (long int)pX;
			columnM[x] = pX - (double)kX;
			for (k = 0; k < 4; ++k) {
				index = kX - 1 + k;
				column[x * 4 + k] = (index < 0) ? 0 : ((index >= lx) ? lx - 1 : index);
			};
		};

		Pixel *row[4];
		const long int *c;
		PixelPremultiplied v[4];
		PixelPremultiplied h[4];
		PixelPremultiplied p;

		for (y = 0; y < ny; ++y) {
			pY = (double)y * deltaY;
			kY = (long int)pY;
			mY = pY - (double)kY;
			for (k = 0; k < 4; ++k) {
				index = kY - 1 + k;
				row[k] = imgThis->pixel[(index < 0) ? 0 : ((index >= ly) ? ly - 1 : index)];
			};
			for (x = 0; x < nx; ++x) {
				c = &column[x * 4];
				for (k = 0; k < 4; ++k) {
					v[0] = premultiplied(row[k][c[0]]);
					v[1] = premultiplied(row[k][c[1]]);
					v[2] = premultiplied(row[k][c[2]]);
					v[3] = premultiplied(row[k][c[3]]);
					h[k] = cubic(v, columnM[x]);
				};
				p = cubic(h, mY);
				if (p.a > 0) {
					p.r /= p.a;
					p.g /= p.a;
					p.b /= p.a;
				} else {
					p.r = 0;
					p.g = 0;
					p.b = 0;
				};
				retV->pixel[y][x] = XYO_PIXEL32_PIXEL(pixelRound(p.r), pixelRound(p.g), pixelRound(p.b), pixelRound(p.a));
			};
		};
		return retV;
	};

};
