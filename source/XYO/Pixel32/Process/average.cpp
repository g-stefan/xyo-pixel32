// Pixel32
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	void average(Image *imgInOut1, Image *imgIn2, uint32_t level1, uint32_t level2, uint32_t average) {
		long int x;
		long int y;
		Pixel c1;
		Pixel c2;
		uint32_t cxa;
		uint32_t cxr;
		uint32_t cxg;
		uint32_t cxb;

		for (y = 0; y < imgInOut1->height; ++y) {
			for (x = 0; x < imgInOut1->width; ++x) {
				c1 = imgInOut1->pixel[y][x];
				c2 = imgIn2->pixel[y][x];

				cxa = (XYO_PIXEL32_A(c1) * level1 + XYO_PIXEL32_A(c2) * level2) / average;
				cxr = (XYO_PIXEL32_R(c1) * level1 + XYO_PIXEL32_R(c2) * level2) / average;
				cxg = (XYO_PIXEL32_G(c1) * level1 + XYO_PIXEL32_G(c2) * level2) / average;
				cxb = (XYO_PIXEL32_B(c1) * level1 + XYO_PIXEL32_B(c2) * level2) / average;

				imgInOut1->pixel[y][x] = XYO_PIXEL32_PIXEL(pixelClampX(cxr), pixelClampX(cxg), pixelClampX(cxb), pixelClampX(cxa));
			};
		};
	};

};
