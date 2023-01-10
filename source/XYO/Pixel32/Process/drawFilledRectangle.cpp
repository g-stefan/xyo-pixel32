// Pixel32
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	void drawFilledRectangle(Image *imgThis, long int sx, long int sy, long int lx, long int ly, Pixel pixel) {
		long int x;
		long int y;

		if (sx < 0) {
			sx = 0;
		};
		if (sy < 0) {
			sy = 0;
		};

		if (sx + lx >= imgThis->width) {
			lx = imgThis->width - sx;
		};
		if (sy + ly >= imgThis->height) {
			ly = imgThis->height - sy;
		};

		if (lx < 0) {
			lx = 0;
		};
		if (ly < 0) {
			ly = 0;
		};

		lx += sx;
		ly += sy;

		for (y = sy; y < ly; ++y) {
			for (x = sx; x < lx; ++x) {
				imgThis->pixel[y][x] = alphaBlending(pixel, imgThis->pixel[y][x]);
			};
		};
	};

};
