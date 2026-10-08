// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	// Positive offset modulo size
	static inline long int wrapOffset(long int d, long int size) {
		d %= size;
		if (d < 0) {
			d += size;
		};
		return d;
	};

	// Result pixel (x, y) is the input pixel ((x + dx) mod width, (y + dy) mod height)
	TPointer<Image> wrap(Image *imgThis, long int dx, long int dy) {
		long int lx = imgThis->width;
		long int ly = imgThis->height;

		TPointer<Image> retV;
		retV = create(lx, ly);
		if (retV) {
			dx = wrapOffset(dx, lx);
			dy = wrapOffset(dy, ly);
			copy(retV, imgThis, 0, 0, dx, dy, lx - dx, ly - dy);
			copy(retV, imgThis, lx - dx, 0, 0, dy, dx, ly - dy);
			copy(retV, imgThis, 0, ly - dy, dx, 0, lx - dx, dy);
			copy(retV, imgThis, lx - dx, ly - dy, 0, 0, dx, dy);
		};
		return retV;
	};

};
