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

			TPointer<Image> scaleDownX2OnX(Image *imgThis) {
				TPointer<Image> retV;
				retV = create(imgThis->width / 2, imgThis->height);
				if(retV) {
					long int x, y;
					uint32_t sumR;
					uint32_t sumG;
					uint32_t sumB;
					uint32_t sumA;
					Pixel pixel;



					for(y = 0; y < retV->height; ++y) {
						for(x = 0; x < retV->width; ++x) {

							pixel = imgThis->pixel[y][x * 2];
							sumR = XYO_PIXEL32_R(pixel) * XYO_PIXEL32_A(pixel);
							sumG = XYO_PIXEL32_G(pixel) * XYO_PIXEL32_A(pixel);
							sumB = XYO_PIXEL32_B(pixel) * XYO_PIXEL32_A(pixel);
							sumA = XYO_PIXEL32_A(pixel);

							pixel = imgThis->pixel[y][x * 2 + 1];
							sumR += XYO_PIXEL32_R(pixel) * XYO_PIXEL32_A(pixel);
							sumG += XYO_PIXEL32_G(pixel) * XYO_PIXEL32_A(pixel);
							sumB += XYO_PIXEL32_B(pixel) * XYO_PIXEL32_A(pixel);
							sumA += XYO_PIXEL32_A(pixel);

							sumA /= 2;
							if(sumA > 0) {
								sumR /= sumA;
								sumG /= sumA;
								sumB /= sumA;
							} else {
								sumR = 0;
								sumG = 0;
								sumB = 0;
							};

							sumR /= 2;
							sumG /= 2;
							sumB /= 2;

							retV->pixel[y][x] = XYO_PIXEL32_PIXEL(pixelClampX(sumR), pixelClampX(sumG), pixelClampX(sumB), pixelClampX(sumA));
						};
					};



				};
				return retV;
			};

		};
	};
};



