//
// XYO Pixel32
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-pixel32-process.hpp"

namespace XYO {
	namespace Pixel32 {
		namespace Process {

			using namespace XYO;

			TPointer<Image> cut(Image *imgThis, long int sx, long int sy, long int lx, long int ly) {
				if(sx < 0) {
					sx = 0;
				};
				if(sy < 0) {
					sy = 0;
				};
				if(lx < 0) {
					lx = 0;
				};
				if(ly < 0) {
					ly = 0;
				};


				if(sx + lx >= imgThis->width) {
					lx = imgThis->width - sx;
				};
				if(sy + ly >= imgThis->height) {
					ly = imgThis->height - sy;
				};
				TPointer<Image> retV = create(lx, ly);
				if(retV) {

					long int y;
					long int x;
					long int ey;
					long int ex;
					long int my;
					long int mx;

					ey = sy + ly;
					ex = sx + lx;

					for(y = 0, my = sy; y < ly; ++y, ++my) {
						for(x = 0, mx = sx; x < lx; ++x, ++mx) {
							retV->pixel[y][x] = imgThis->pixel[my][mx];
						};
					};


				};
				return retV;
			};


		};
	};
};

