// Pixel32
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	TPointer<Image> resize(Image *imgThis, long int nx, long int ny) {
		TPointer<Image> retV;
		uint32_t dx = imgThis->width;
		uint32_t dy = imgThis->height;
		if (nx == dx) {
			if (ny == dy) {
				retV = create(nx, ny);
				memcpy(retV->pixelMap, imgThis->pixelMap, sizeof(Pixel) * nx * ny);
				return retV;
			};
		};
		if (nx >= dx) {
			if (ny >= dy) {
				return scaleUp(imgThis, nx, ny);
			};
			retV = scaleUp(imgThis, nx, dy);
			return scaleDown(retV, nx, ny);
		};
		if (ny >= dy) {
			retV = scaleUp(imgThis, dx, ny);
			return scaleDown(retV, nx, ny);
		};
		return scaleDown(imgThis, nx, ny);
	};

};
