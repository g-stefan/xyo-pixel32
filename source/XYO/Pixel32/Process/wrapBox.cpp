// Pixel32
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	TPointer<Image> wrapBox(Image *imgThis, long int dx, long int dy) {
		uint32_t lx = imgThis->width;
		uint32_t ly = imgThis->height;

		TPointer<Image> retV;

		retV = create(lx + 2 * dx, ly + 2 * dy);
		if (retV) {
			// center
			copy(retV, imgThis, dx, dy, 0, 0, lx, ly);
			// top
			copy(retV, imgThis, 0, 0, lx - dx, ly - dy, dx, dy);
			copy(retV, imgThis, dx, 0, 0, ly - dy, lx, dy);
			copy(retV, imgThis, lx + dx, 0, 0, ly - dy, dx, dy);
			// bottom
			copy(retV, imgThis, 0, ly + dy, lx - dx, 0, dx, dy);
			copy(retV, imgThis, dx, ly + dy, 0, 0, lx, dy);
			copy(retV, imgThis, lx + dx, ly + dy, 0, 0, dx, dy);
			// right
			copy(retV, imgThis, lx + dx, dy, 0, 0, dx, ly);
			// left
			copy(retV, imgThis, 0, dy, lx - dx, 0, dx, ly);
		};
		return retV;
	};

};
