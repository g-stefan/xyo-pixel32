// Pixel32
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	Pixel getPixel(Image *imgThis, long int x, long int y) {
		if (x < 0 || y < 0 || x >= imgThis->width || y >= imgThis->height) {
			return 0L;
		};
		return imgThis->pixel[y][x];
	};

};
