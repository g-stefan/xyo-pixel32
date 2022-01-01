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

			Pixel getPixelX(Image *imgThis, long int x, long int y) {
				if(x < 0) {
					if(y < 0) {
						return imgThis->pixel[0][0];
					};
					if(y >= imgThis->height) {
						return imgThis->pixel[imgThis->height - 1][0];
					};
					return imgThis->pixel[y][0];
				};
				if(x >= imgThis->width) {
					if(y < 0) {
						return imgThis->pixel[0][imgThis->width - 1];
					};
					if(y >= imgThis->height) {
						return imgThis->pixel[imgThis->height - 1][imgThis->width - 1];
					};
					return imgThis->pixel[y][imgThis->width - 1];
				};
				if(y < 0) {
					return imgThis->pixel[0][x];
				};
				if(y >= imgThis->height) {
					return imgThis->pixel[imgThis->height - 1][x];
				};

				return imgThis->pixel[y][x];
			};


		};
	};
};

