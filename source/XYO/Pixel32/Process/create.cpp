// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	TPointer<Image> create(long int width, long int height) {
		if (width <= 0 || height <= 0) {
			return nullptr;
		};
		// width * height * sizeof(Pixel) must not overflow
		if ((size_t)width > (SIZE_MAX / sizeof(Pixel)) / (size_t)height) {
			return nullptr;
		};
		TPointer<Image> retV;
		retV.newMemory();
		retV->width = width;
		retV->height = height;
		retV->pixelMap = new Pixel[(size_t)width * (size_t)height]();
		retV->pixel = new Pixel *[(size_t)height];
		for (size_t scan = 0; scan < (size_t)height; ++scan) {
			retV->pixel[scan] = &retV->pixelMap[scan * (size_t)width];
		};
		return retV;
	};

};
