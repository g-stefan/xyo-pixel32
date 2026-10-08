// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	// Border of dx, dy around the image, filled as if the image is tiled:
	// result pixel (x, y) is the input pixel ((x - dx) mod width, (y - dy) mod height)
	TPointer<Image> wrapBox(Image *imgThis, long int dx, long int dy) {
		long int lx = imgThis->width;
		long int ly = imgThis->height;

		if (dx < 0) {
			dx = 0;
		};
		if (dy < 0) {
			dy = 0;
		};
		if ((dx > (0x7FFFFFFF - lx) / 2) || (dy > (0x7FFFFFFF - ly) / 2)) {
			return nullptr;
		};

		TPointer<Image> retV;

		retV = create(lx + 2 * dx, ly + 2 * dy);
		if (retV) {
			long int x;
			long int y;
			long int mx;
			long int my;
			long int startX = (lx - (dx % lx)) % lx;
			Pixel *out;
			Pixel *in;

			my = (ly - (dy % ly)) % ly;
			for (y = 0; y < retV->height; ++y) {
				out = retV->pixel[y];
				in = imgThis->pixel[my];
				mx = startX;
				for (x = 0; x < retV->width; ++x) {
					out[x] = in[mx];
					if (++mx == lx) {
						mx = 0;
					};
				};
				if (++my == ly) {
					my = 0;
				};
			};
		};
		return retV;
	};

};
