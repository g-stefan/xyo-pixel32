// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	void copy(Image *imgThis, Image *imgIn2, long int dx, long int dy, long int sx, long int sy, long int lx, long int ly) {
		if (!clipSpan2(dx, sx, lx, imgThis->width, imgIn2->width)) {
			return;
		};
		if (!clipSpan2(dy, sy, ly, imgThis->height, imgIn2->height)) {
			return;
		};

		long int y;
		// Same image, overlapping rows: copy in the direction that keeps the source intact
		if ((imgThis == imgIn2) && (dy > sy)) {
			for (y = ly - 1; y >= 0; --y) {
				memmove(&imgThis->pixel[dy + y][dx], &imgIn2->pixel[sy + y][sx], sizeof(Pixel) * lx);
			};
			return;
		};
		for (y = 0; y < ly; ++y) {
			memmove(&imgThis->pixel[dy + y][dx], &imgIn2->pixel[sy + y][sx], sizeof(Pixel) * lx);
		};
	};

};
