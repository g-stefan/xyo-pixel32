// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	static inline void blendPixel(Image *imgThis, int64_t x, int64_t y, Pixel pixel) {
		if ((x < 0) || (y < 0) || (x >= imgThis->width) || (y >= imgThis->height)) {
			return;
		};
		imgThis->pixel[y][x] = alphaBlending(pixel, imgThis->pixel[y][x]);
	};

	// Outline of [sx, sx + lx) x [sy, sy + ly), clipped to the image, each pixel blended once
	void drawRectangle(Image *imgThis, long int sx, long int sy, long int lx, long int ly, Pixel pixel) {
		if ((lx <= 0) || (ly <= 0)) {
			return;
		};

		int64_t x;
		int64_t y;
		int64_t x0 = sx;
		int64_t y0 = sy;
		int64_t x1 = (int64_t)sx + lx - 1;
		int64_t y1 = (int64_t)sy + ly - 1;

		// Visible part of the horizontal edges
		int64_t xs = (x0 < 0) ? 0 : x0;
		int64_t xe = (x1 >= imgThis->width) ? imgThis->width - 1 : x1;
		for (x = xs; x <= xe; ++x) {
			blendPixel(imgThis, x, y0, pixel);
			if (y1 != y0) {
				blendPixel(imgThis, x, y1, pixel);
			};
		};

		// Vertical edges without the corners
		int64_t ys = (y0 + 1 < 0) ? 0 : y0 + 1;
		int64_t ye = (y1 - 1 >= imgThis->height) ? imgThis->height - 1 : y1 - 1;
		for (y = ys; y <= ye; ++y) {
			blendPixel(imgThis, x0, y, pixel);
			if (x1 != x0) {
				blendPixel(imgThis, x1, y, pixel);
			};
		};
	};

};
