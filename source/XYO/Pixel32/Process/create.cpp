// Pixel32
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

			using namespace XYO;

			TPointer<Image> create(long int width, long int height) {
				if (width <= 0 || height <= 0) {
					return nullptr;
				};
				TPointer<Image> retV;
				retV.newMemory();
				retV->width = width;
				retV->height = height;
				uint32_t scan;
				retV->pixelMap = new Pixel[height * width];
				memset(retV->pixelMap, 0, sizeof(Pixel) * height * width);
				retV->pixel = new Pixel *[height];
				for (scan = 0; scan < height; ++scan) {
					retV->pixel[scan] = &retV->pixelMap[scan * width];
				};
				return retV;
			};

		};
