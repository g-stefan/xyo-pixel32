// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	TPointer<Image> resize(Image *imgThis, long int nx, long int ny) {
		TPointer<Image> retV;
		long int dx = imgThis->width;
		long int dy = imgThis->height;
		if ((nx <= 0) || (ny <= 0)) {
			return nullptr;
		};
		if ((nx == dx) && (ny == dy)) {
			retV = create(nx, ny);
			if (retV) {
				memcpy(retV->pixelMap, imgThis->pixelMap, sizeof(Pixel) * (size_t)nx * (size_t)ny);
			};
			return retV;
		};
		if (nx >= dx) {
			if (ny >= dy) {
				return scaleUp(imgThis, nx, ny);
			};
			retV = scaleUp(imgThis, nx, dy);
			if (!retV) {
				return nullptr;
			};
			return scaleDown(retV, nx, ny);
		};
		if (ny >= dy) {
			retV = scaleUp(imgThis, dx, ny);
			if (!retV) {
				return nullptr;
			};
			return scaleDown(retV, nx, ny);
		};
		return scaleDown(imgThis, nx, ny);
	};

};
