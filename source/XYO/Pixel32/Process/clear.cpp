// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	void clear(Image *imgThis, Pixel pixel) {
		Pixel *x = imgThis->pixelMap;
		Pixel *xe = x + (size_t)imgThis->width * (size_t)imgThis->height;
		while (x < xe) {
			*x++ = pixel;
		};
	};

};
