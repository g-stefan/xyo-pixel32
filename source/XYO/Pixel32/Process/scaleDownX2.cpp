// Pixel32
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	TPointer<Image> scaleDownX2(Image *imgThis) {
		TPointer<Image> retV;
		retV = create(imgThis->width / 2, imgThis->height / 2);
		if (retV) {
			long int x, y;
			uint32_t sumR;
			uint32_t sumG;
			uint32_t sumB;
			uint32_t sumA;
			Pixel pixel;

			for (y = 0; y < retV->height; ++y) {
				for (x = 0; x < retV->width; ++x) {

					pixel = imgThis->pixel[y * 2][x * 2];
					sumR = XYO_PIXEL32_R(pixel) * XYO_PIXEL32_A(pixel);
					sumG = XYO_PIXEL32_G(pixel) * XYO_PIXEL32_A(pixel);
					sumB = XYO_PIXEL32_B(pixel) * XYO_PIXEL32_A(pixel);
					sumA = XYO_PIXEL32_A(pixel);

					pixel = imgThis->pixel[y * 2][x * 2 + 1];
					sumR += XYO_PIXEL32_R(pixel) * XYO_PIXEL32_A(pixel);
					sumG += XYO_PIXEL32_G(pixel) * XYO_PIXEL32_A(pixel);
					sumB += XYO_PIXEL32_B(pixel) * XYO_PIXEL32_A(pixel);
					sumA += XYO_PIXEL32_A(pixel);

					pixel = imgThis->pixel[y * 2 + 1][x * 2];
					sumR += XYO_PIXEL32_R(pixel) * XYO_PIXEL32_A(pixel);
					sumG += XYO_PIXEL32_G(pixel) * XYO_PIXEL32_A(pixel);
					sumB += XYO_PIXEL32_B(pixel) * XYO_PIXEL32_A(pixel);
					sumA += XYO_PIXEL32_A(pixel);

					pixel = imgThis->pixel[y * 2 + 1][x * 2 + 1];
					sumR += XYO_PIXEL32_R(pixel) * XYO_PIXEL32_A(pixel);
					sumG += XYO_PIXEL32_G(pixel) * XYO_PIXEL32_A(pixel);
					sumB += XYO_PIXEL32_B(pixel) * XYO_PIXEL32_A(pixel);
					sumA += XYO_PIXEL32_A(pixel);

					sumA /= 4;
					if (sumA > 0) {
						sumR /= sumA;
						sumG /= sumA;
						sumB /= sumA;
					} else {
						sumR = 0;
						sumG = 0;
						sumB = 0;
					};

					sumR /= 4;
					sumG /= 4;
					sumB /= 4;

					retV->pixel[y][x] = XYO_PIXEL32_PIXEL(pixelClampX(sumR), pixelClampX(sumG), pixelClampX(sumB), pixelClampX(sumA));
				};
			};
		};
		return retV;
	};

};
