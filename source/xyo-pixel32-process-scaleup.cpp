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

			TPointer<Image> scaleUp(Image *imgThis, long int nx, long int ny) {
				uint32_t factorX = nx / imgThis->width;
				uint32_t factorY = ny / imgThis->height;
				TPointer<Image> retV = imgThis;
				if (factorY > 1) {
					if (factorX > 1) {
						retV = scaleUpBicubic(retV, retV->width * 2, retV->height * 2);
						retV = kernel3X3(retV, Kernel3X3::filter8X1);
						return scaleUp(retV, nx, ny);
					};
					retV = scaleUpBicubic(retV, retV->width, retV->height + (retV->height / 16));
					retV = kernel3X3(retV, Kernel3X3::filter8X1);
					return scaleUp(retV, nx, ny);
				};
				if (factorX > 1) {
					retV = scaleUpBicubic(retV, retV->width * 2, retV->height);
					retV = kernel3X3(retV, Kernel3X3::filter8X1);
					return scaleUp(retV, nx, ny);
				};
				if (imgThis->height == ny) {
					if (imgThis->width == nx) {
						return retV;
					};
				};
				retV = scaleUpBicubic(retV, nx, ny);
				return retV;
			};

		};
	};
};
