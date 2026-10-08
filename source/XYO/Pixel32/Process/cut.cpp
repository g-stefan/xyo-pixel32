// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	TPointer<Image> cut(Image *imgThis, long int sx, long int sy, long int lx, long int ly) {
		if (!clipSpan(sx, lx, imgThis->width)) {
			return nullptr;
		};
		if (!clipSpan(sy, ly, imgThis->height)) {
			return nullptr;
		};
		TPointer<Image> retV = create(lx, ly);
		if (retV) {
			long int y;
			for (y = 0; y < ly; ++y) {
				memcpy(retV->pixel[y], &imgThis->pixel[sy + y][sx], sizeof(Pixel) * lx);
			};
		};
		return retV;
	};

};
