// Pixel32
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

			using namespace XYO;

			void clear(Image *imgThis, Pixel pixel) {
				long int y;
				Pixel *x;
				Pixel *xe;
				for (y = 0; y < imgThis->height; ++y) {
					x = imgThis->pixel[y];
					xe = x + imgThis->width;
					while (x < xe) {
						*x++ = pixel;
					};
				};
			};

		};
