//
// XYO Pixel32
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-pixel32-process.hpp"

namespace XYO {
	namespace Pixel32 {
		namespace Process {

			using namespace XYO;

			void setPixel(Image *imgThis, long int x, long int y, Pixel pixel) {
				if (x < 0 || y < 0 || x >= imgThis->width || y >= imgThis->height) {
					return;
				};
				imgThis->pixel[y][x] = pixel;
			};

		};
	};
};
