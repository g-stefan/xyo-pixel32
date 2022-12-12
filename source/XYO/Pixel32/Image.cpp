// Pixel32
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/image.hpp>

namespace XYO::Pixel32 {

	Image::Image() {
		width = 0;
		height = 0;
		pixel = NULL;
		pixelMap = NULL;
	};

	Image::~Image() {
		if (pixel) {
			delete[] pixel;
		};
		if (pixelMap) {
			delete[] pixelMap;
		};
	};

};