// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	// Blend with the background, then alpha becomes 0 below level, 255 otherwise
	void backgroundAlphaLevel(Image *inOutImage, Pixel background, int level) {
		long int x, y;
		Pixel cx;
		uint32_t crx, cgx, cbx, cax;
		Pixel *row;

		for (y = 0; y < inOutImage->height; ++y) {
			row = inOutImage->pixel[y];
			for (x = 0; x < inOutImage->width; ++x) {
				cx = row[x];
				cax = XYO_PIXEL32_A(cx);
				crx = (XYO_PIXEL32_R(cx) * cax + XYO_PIXEL32_R(background) * (255 - cax)) / 255;
				cgx = (XYO_PIXEL32_G(cx) * cax + XYO_PIXEL32_G(background) * (255 - cax)) / 255;
				cbx = (XYO_PIXEL32_B(cx) * cax + XYO_PIXEL32_B(background) * (255 - cax)) / 255;
				cax = ((int)cax < level) ? 0 : 255;
				row[x] = XYO_PIXEL32_PIXEL(crx, cgx, cbx, cax);
			};
		};
	};

};
