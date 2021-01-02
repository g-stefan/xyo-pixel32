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

			void drawRectangle(Image *imgThis, long int sx, long int sy, long int lx, long int ly, Pixel pixel) {
				long int x;
				long int y;

				if(sx < 0) {
					sx = 0;
				};
				if(sy < 0) {
					sy = 0;
				};

				if(sx + lx >= imgThis->width) {
					lx = imgThis->width - sx;
				};
				if(sy + ly >= imgThis->height) {
					ly = imgThis->height - sy;
				};

				if(lx < 0) {
					lx = 0;
				};
				if(ly < 0) {
					ly = 0;
				};

				lx += sx;
				ly += sy;


				lx--;
				for(y = sy; y < ly; ++y) {
					imgThis->pixel[y][sx] = alphaBlending(pixel, imgThis->pixel[y][sx]);
					imgThis->pixel[y][lx] = alphaBlending(pixel, imgThis->pixel[y][lx]);
				};

				for(x = sx + 1; x < lx; ++x) {
					imgThis->pixel[sy][x] = alphaBlending(pixel, imgThis->pixel[sy][x]);
					imgThis->pixel[ly - 1][x] = alphaBlending(pixel, imgThis->pixel[ly - 1][x]);
				};

			};

		};
	};
};


