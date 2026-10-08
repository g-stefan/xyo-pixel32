// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	void blend(Image *imgInOut1, Image *imgIn2, long int dx, long int dy, long int sx, long int sy, long int lx, long int ly) {
		if (!clipSpan2(dx, sx, lx, imgInOut1->width, imgIn2->width)) {
			return;
		};
		if (!clipSpan2(dy, sy, ly, imgInOut1->height, imgIn2->height)) {
			return;
		};

		long int y;
		long int x;
		Pixel *out;
		Pixel *in;

		for (y = 0; y < ly; ++y) {
			out = &imgInOut1->pixel[dy + y][dx];
			in = &imgIn2->pixel[sy + y][sx];
			for (x = 0; x < lx; ++x) {
				out[x] = alphaBlending(in[x], out[x]);
			};
		};
	};

};
