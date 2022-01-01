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

			TPointer<Image> resize(Image *imgThis, long int nx, long int ny) {
				TPointer<Image> retV;
				uint32_t dx = imgThis->width;
				uint32_t dy = imgThis->height;
				if(nx == dx) {
					if(ny == dy) {						
						retV = create(nx, ny);
						memcpy(retV->pixelMap, imgThis->pixelMap, sizeof(Pixel)*nx * ny);
						return retV;
					};
				};
				if(nx >= dx) {
					if(ny >= dy) {
						return scaleUp(imgThis, nx, ny);
					};
					retV = scaleUp(imgThis, nx, dy);
					return scaleDown(retV, nx, ny);
				};
				if(ny >= dy) {
					retV = scaleUp(imgThis, dx, ny);
					return scaleDown(retV, nx, ny);
				};
				return scaleDown(imgThis, nx, ny);
			};

		};
	};
};



