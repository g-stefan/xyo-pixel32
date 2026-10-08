// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	void drawFilledRectangle(Image *imgThis, long int sx, long int sy, long int lx, long int ly, Pixel pixel) {
		if (!clipSpan(sx, lx, imgThis->width)) {
			return;
		};
		if (!clipSpan(sy, ly, imgThis->height)) {
			return;
		};

		long int x;
		long int y;
		Pixel *row;

		for (y = sy; y < sy + ly; ++y) {
			row = imgThis->pixel[y];
			for (x = sx; x < sx + lx; ++x) {
				row[x] = alphaBlending(pixel, row[x]);
			};
		};
	};

};
