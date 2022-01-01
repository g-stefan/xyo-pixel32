//
// XYO Pixel32
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-pixel32-image.hpp"

namespace XYO {
	namespace Pixel32 {

		Image::Image() {
			width = 0;
			height = 0;
			pixel = NULL;
			pixelMap = NULL;
		};

		Image::~Image() {
			if(pixel) {
				delete[] pixel;

			};
			if(pixelMap) {
				delete[] pixelMap;

			};
		};

	};
};

