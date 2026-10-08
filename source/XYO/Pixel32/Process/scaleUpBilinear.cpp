// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	// Samples outside the image repeat the edge pixels
	TPointer<Image> scaleUpBilinear(Image *imgThis, long int nx, long int ny) {
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

		long int x;
		long int y;
		long int kX;
		long int kY;
		long int kX1;
		double mX;
		double mY;
		double pX;
		double pY;
		Pixel *row0;
		Pixel *row1;
		Pixel p00, p01, p10, p11;
		double a00, a01, a10, a11;
		double r0, g0, b0, a0;
		double r1, g1, b1, a1;
		double r, g, b, a;

		for (y = 0; y < ny; ++y) {
			pY = (double)y * deltaY;
			kY = (long int)pY;
			mY = pY - (double)kY;
			row0 = imgThis->pixel[kY];
			row1 = imgThis->pixel[(kY + 1 < ly) ? kY + 1 : ly - 1];
			for (x = 0; x < nx; ++x) {
				pX = (double)x * deltaX;
				kX = (long int)pX;
				mX = pX - (double)kX;
				kX1 = (kX + 1 < lx) ? kX + 1 : lx - 1;

				p00 = row0[kX];
				p01 = row0[kX1];
				p10 = row1[kX];
				p11 = row1[kX1];
				a00 = XYO_PIXEL32_A(p00);
				a01 = XYO_PIXEL32_A(p01);
				a10 = XYO_PIXEL32_A(p10);
				a11 = XYO_PIXEL32_A(p11);

				r0 = interpolateLinear(XYO_PIXEL32_R(p00) * a00, XYO_PIXEL32_R(p01) * a01, mX);
				g0 = interpolateLinear(XYO_PIXEL32_G(p00) * a00, XYO_PIXEL32_G(p01) * a01, mX);
				b0 = interpolateLinear(XYO_PIXEL32_B(p00) * a00, XYO_PIXEL32_B(p01) * a01, mX);
				a0 = interpolateLinear(a00, a01, mX);

				r1 = interpolateLinear(XYO_PIXEL32_R(p10) * a10, XYO_PIXEL32_R(p11) * a11, mX);
				g1 = interpolateLinear(XYO_PIXEL32_G(p10) * a10, XYO_PIXEL32_G(p11) * a11, mX);
				b1 = interpolateLinear(XYO_PIXEL32_B(p10) * a10, XYO_PIXEL32_B(p11) * a11, mX);
				a1 = interpolateLinear(a10, a11, mX);

				r = interpolateLinear(r0, r1, mY);
				g = interpolateLinear(g0, g1, mY);
				b = interpolateLinear(b0, b1, mY);
				a = interpolateLinear(a0, a1, mY);

				if (a > 0) {
					r /= a;
					g /= a;
					b /= a;
				} else {
					r = 0;
					g = 0;
					b = 0;
				};

				retV->pixel[y][x] = XYO_PIXEL32_PIXEL(pixelRound(r), pixelRound(g), pixelRound(b), pixelRound(a));
			};
		};
		return retV;
	};

};
