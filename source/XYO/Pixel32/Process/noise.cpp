// Pixel32
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	void noise(Image *imgInOut, RandomMT &rnd) {
		long int y;
		long int x;

		uint32_t cx;

		for (y = 0; y < imgInOut->height; ++y) {
			for (x = 0; x < imgInOut->width; ++x) {

				cx = rnd.nextRandom() & 0xFF;

				imgInOut->pixel[y][x] = XYO_PIXEL32_PIXEL(cx, cx, cx, 0xFF);
			};
		};
	};

};
