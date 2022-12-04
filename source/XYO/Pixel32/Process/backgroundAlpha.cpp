// Pixel32
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

			using namespace XYO;

			void backgroundAlpha(Image *inOutImage, Pixel background) {
				long int lx, ly;

				lx = inOutImage->width;
				ly = inOutImage->height;
				long int x, y;
				Pixel cx;
				int crx, cgx, cbx, cax;

				for (y = 0; y < ly; ++y) {
					for (x = 0; x < lx; ++x) {
						cx = inOutImage->pixel[y][x];
						if (XYO_PIXEL32_A(cx) == 0x00) {
							inOutImage->pixel[y][x] = XYO_PIXEL32_CHANGE_A(background, 0x00);
						};
					};
				};
			};

		};
