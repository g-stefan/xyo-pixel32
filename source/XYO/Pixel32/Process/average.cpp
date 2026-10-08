// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	// Only the area common to both images is changed
	void average(Image *imgInOut1, Image *imgIn2, uint32_t level1, uint32_t level2, uint32_t average) {
		long int x;
		long int y;
		long int lx;
		long int ly;
		Pixel c1;
		Pixel c2;
		uint64_t cxa;
		uint64_t cxr;
		uint64_t cxg;
		uint64_t cxb;

		if (average == 0) {
			return;
		};

		lx = (imgInOut1->width < imgIn2->width) ? imgInOut1->width : imgIn2->width;
		ly = (imgInOut1->height < imgIn2->height) ? imgInOut1->height : imgIn2->height;

		for (y = 0; y < ly; ++y) {
			for (x = 0; x < lx; ++x) {
				c1 = imgInOut1->pixel[y][x];
				c2 = imgIn2->pixel[y][x];

				cxa = ((uint64_t)XYO_PIXEL32_A(c1) * level1 + (uint64_t)XYO_PIXEL32_A(c2) * level2) / average;
				cxr = ((uint64_t)XYO_PIXEL32_R(c1) * level1 + (uint64_t)XYO_PIXEL32_R(c2) * level2) / average;
				cxg = ((uint64_t)XYO_PIXEL32_G(c1) * level1 + (uint64_t)XYO_PIXEL32_G(c2) * level2) / average;
				cxb = ((uint64_t)XYO_PIXEL32_B(c1) * level1 + (uint64_t)XYO_PIXEL32_B(c2) * level2) / average;

				imgInOut1->pixel[y][x] = XYO_PIXEL32_PIXEL((cxr > 255) ? 255 : cxr, (cxg > 255) ? 255 : cxg, (cxb > 255) ? 255 : cxb, (cxa > 255) ? 255 : cxa);
			};
		};
	};

};
