// Pixel32
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

			using namespace XYO;

			void backgroundAlphaLevel(Image *inOutImage, Pixel background, int level) {
				long int lx, ly;

				lx = inOutImage->width;
				ly = inOutImage->height;
				long int x, y;
				Pixel cx;
				int crx, cgx, cbx, cax;

				for (y = 0; y < ly; ++y) {
					for (x = 0; x < lx; ++x) {
						cx = inOutImage->pixel[y][x];
						cax = XYO_PIXEL32_A(cx);
						crx = ((((uint32_t)(XYO_PIXEL32_R(cx))) * (cax) + ((uint32_t)(XYO_PIXEL32_R(background))) * (255 - cax)) / 255);
						cgx = ((((uint32_t)(XYO_PIXEL32_G(cx))) * (cax) + ((uint32_t)(XYO_PIXEL32_G(background))) * (255 - cax)) / 255);
						cbx = ((((uint32_t)(XYO_PIXEL32_B(cx))) * (cax) + ((uint32_t)(XYO_PIXEL32_B(background))) * (255 - cax)) / 255);

						if (cax < level) {
							cax = 0;
						} else {
							cax = 255;
						};

						inOutImage->pixel[y][x] = XYO_PIXEL32_PIXEL(crx, cgx, cbx, cax);
					};
				};
			};

		};
