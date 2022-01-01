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

			void noise(Image *imgInOut, RandomMT &rnd) {
				long int y;
				long int x;

				uint32_t cx;

				for(y = 0; y < imgInOut->height; ++y) {
					for(x = 0; x < imgInOut->width; ++x) {

						cx = rnd.nextRandom() & 0xFF;

						imgInOut->pixel[y][x] = XYO_PIXEL32_PIXEL(cx, cx, cx, 0xFF);
					};
				};

			};


		};
	};
};

