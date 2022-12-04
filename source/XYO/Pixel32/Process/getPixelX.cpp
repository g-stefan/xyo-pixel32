// Pixel32
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

			using namespace XYO;

			Pixel getPixelX(Image *imgThis, long int x, long int y) {
				if (x < 0) {
					if (y < 0) {
						return imgThis->pixel[0][0];
					};
					if (y >= imgThis->height) {
						return imgThis->pixel[imgThis->height - 1][0];
					};
					return imgThis->pixel[y][0];
				};
				if (x >= imgThis->width) {
					if (y < 0) {
						return imgThis->pixel[0][imgThis->width - 1];
					};
					if (y >= imgThis->height) {
						return imgThis->pixel[imgThis->height - 1][imgThis->width - 1];
					};
					return imgThis->pixel[y][imgThis->width - 1];
				};
				if (y < 0) {
					return imgThis->pixel[0][x];
				};
				if (y >= imgThis->height) {
					return imgThis->pixel[imgThis->height - 1][x];
				};

				return imgThis->pixel[y][x];
			};

		};
