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

			void copy(Image *imgThis, Image *imgIn2, long int dx, long int  dy, long int  sx, long int  sy, long int  lx, long int  ly) {

				if(dx < 0) {
					dx = 0;
				};
				if(dy < 0) {
					dy = 0;
				};
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


				if(dx >= imgThis->width) {
					return;
				};
				if(dy >= imgThis->height) {
					return;
				};

				if(sx >= imgIn2->width) {
					return;
				};
				if(sy >= imgIn2->height) {
					return;
				};



				if(lx > imgIn2->width) {
					lx = imgIn2->width;
				};
				if(ly > imgIn2->height) {
					ly = imgIn2->height;
				};
				if(dx + lx >= imgThis->width) {
					lx = imgThis->width - dx;
				};
				if(dy + ly >= imgThis->height) {
					ly = imgThis->height - dy;
				};

				if(sx + lx >= imgIn2->width) {
					lx = imgIn2->width - sx;
				};

				if(sy + ly >= imgIn2->height) {
					ly = imgIn2->height - sy;
				};

				if(lx < 0) {
					lx = 0;
				};
				if(ly < 0) {
					ly = 0;
				};

				long int y;
				long int x;
				long int ey;
				long int ex;
				long int my;
				long int mx;

				ey = dy + ly;
				ex = dx + lx;

				if(ex > imgThis->height) {
					ex = imgThis->height;
				};

				if(ey > imgThis->height) {
					ey = imgThis->height;
				};

				for(y = dy, my = sy; y < ey; ++y, ++my) {
					for(x = dx, mx = sx; x < ex; ++x, ++mx) {
						imgThis->pixel[y][x] = imgIn2->pixel[my][mx];
					};
				};

			};

		};
	};
};


