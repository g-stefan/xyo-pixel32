// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	// Fully transparent pixels get the background color, still transparent
	void backgroundAlpha(Image *inOutImage, Pixel background) {
		long int x, y;
		Pixel *row;
		Pixel transparentBackground = background & 0x00FFFFFF;

		for (y = 0; y < inOutImage->height; ++y) {
			row = inOutImage->pixel[y];
			for (x = 0; x < inOutImage->width; ++x) {
				if (XYO_PIXEL32_A(row[x]) == 0x00) {
					row[x] = transparentBackground;
				};
			};
		};
	};

};
