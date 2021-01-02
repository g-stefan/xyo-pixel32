//
// XYO Pixel32
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-pixel32-process.hpp"

namespace XYO {
	namespace Pixel32 {
		namespace Process {

			using namespace XYO;

			TPointer<Image> wrap(Image *imgThis, long int dx, long int dy) {
				long int lx = imgThis->width;
				long int ly = imgThis->height;

				TPointer<Image> retV;
				retV = create(lx, ly);
				if(retV) {
					copy(retV, imgThis, 0, 0, dx, dy, lx - dx, ly - dy);
					copy(retV, imgThis, dx, 0, 0, dy, dx, ly - dx);
					copy(retV, imgThis, 0, dy, dx, 0, lx - dx, dy);
					copy(retV, imgThis, dx, dy, 0, 0, dx, dy);
				};
				return retV;
			};

		};
	};
};



