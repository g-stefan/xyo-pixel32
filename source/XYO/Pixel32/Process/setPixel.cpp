// Pixel32
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	void setPixel(Image *imgThis, long int x, long int y, Pixel pixel) {
		if (x < 0 || y < 0 || x >= imgThis->width || y >= imgThis->height) {
			return;
		};
		imgThis->pixel[y][x] = pixel;
	};

};
