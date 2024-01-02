// Pixel32
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	void blend(Image *imgInOut1, Image *imgIn2, long int dx, long int dy, long int sx, long int sy, long int lx, long int ly) {

		if (dx < 0) {
			dx = 0;
		};
		if (dy < 0) {
			dy = 0;
		};
		if (sx < 0) {
			sx = 0;
		};
		if (sy < 0) {
			sy = 0;
		};
		if (lx < 0) {
			lx = 0;
		};
		if (ly < 0) {
			ly = 0;
		};

		if (lx > imgIn2->width) {
			lx = imgIn2->width;
		};
		if (ly > imgIn2->height) {
			ly = imgIn2->height;
		};
		if (dx + lx >= imgInOut1->width) {
			lx = imgInOut1->width - dx;
		};
		if (dy + ly >= imgInOut1->height) {
			ly = imgInOut1->height - dy;
		};

		long int y;
		long int x;
		long int ey;
		long int ex;
		long int my;
		long int mx;

		ey = dy + ly;
		ex = dx + lx;

		uint32_t r, g, b, a;

		for (y = dy, my = sy; y < ey; ++y, ++my) {
			for (x = dx, mx = sx; x < ex; ++x, ++mx) {

				imgInOut1->pixel[y][x] = alphaBlending(imgIn2->pixel[my][mx], imgInOut1->pixel[y][x]);
			};
		};
	};

};
