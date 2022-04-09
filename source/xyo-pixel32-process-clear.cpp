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

			void clear(Image *imgThis, Pixel pixel) {
				long int y;
				Pixel *x;
				Pixel *xe;
				for (y = 0; y < imgThis->height; ++y) {
					x = imgThis->pixel[y];
					xe = x + imgThis->width;
					while (x < xe) {
						*x++ = pixel;
					};
				};
			};

		};
	};
};
