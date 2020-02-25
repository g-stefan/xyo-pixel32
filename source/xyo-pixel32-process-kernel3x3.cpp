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

			TPointer<Image> kernel3X3(Image *imgThis, Kernel3X3 &kernel) {
				long int lx = imgThis->width;
				long int ly = imgThis->height;
				long int x;
				long int y;
				double sumR;
				double sumG;
				double sumB;
				double sumA;
				Pixel pixel;

				TPointer<Image> retV;

				retV = create(lx, ly);
				for(y = 0; y < ly; ++y) {
					for(x = 0; x < lx; ++x) {
						pixel = getPixelX(imgThis, x - 1, y - 1);
						sumR = kernel.v[0][0] * (((double)XYO_PIXEL32_R(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumG = kernel.v[0][0] * (((double)XYO_PIXEL32_G(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumB = kernel.v[0][0] * (((double)XYO_PIXEL32_B(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumA = kernel.v[0][0] * (((double)XYO_PIXEL32_A(pixel)));

						pixel = getPixelX(imgThis, x, y - 1);
						sumR += kernel.v[0][1] * (((double)XYO_PIXEL32_R(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumG += kernel.v[0][1] * (((double)XYO_PIXEL32_G(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumB += kernel.v[0][1] * (((double)XYO_PIXEL32_B(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumA += kernel.v[0][1] * (XYO_PIXEL32_A(pixel));

						pixel = getPixelX(imgThis, x + 1, y - 1);
						sumR += kernel.v[0][2] * (((double)XYO_PIXEL32_R(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumG += kernel.v[0][2] * (((double)XYO_PIXEL32_G(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumB += kernel.v[0][2] * (((double)XYO_PIXEL32_B(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumA += kernel.v[0][2] * (XYO_PIXEL32_A(pixel));


						pixel = getPixelX(imgThis, x - 1, y);
						sumR += kernel.v[1][0] * (((double)XYO_PIXEL32_R(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumG += kernel.v[1][0] * (((double)XYO_PIXEL32_G(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumB += kernel.v[1][0] * (((double)XYO_PIXEL32_B(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumA += kernel.v[1][0] * (XYO_PIXEL32_A(pixel));

						pixel = getPixelX(imgThis, x, y);
						sumR += kernel.v[1][1] * (((double)XYO_PIXEL32_R(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumG += kernel.v[1][1] * (((double)XYO_PIXEL32_G(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumB += kernel.v[1][1] * (((double)XYO_PIXEL32_B(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumA += kernel.v[1][1] * (((double)XYO_PIXEL32_A(pixel)));

						pixel = getPixelX(imgThis, x + 1, y);
						sumR += kernel.v[1][2] * (((double)XYO_PIXEL32_R(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumG += kernel.v[1][2] * (((double)XYO_PIXEL32_G(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumB += kernel.v[1][2] * (((double)XYO_PIXEL32_B(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumA += kernel.v[1][2] * (XYO_PIXEL32_A(pixel));

						pixel = getPixelX(imgThis, x - 1, y + 1);
						sumR += kernel.v[2][0] * (((double)XYO_PIXEL32_R(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumG += kernel.v[2][0] * (((double)XYO_PIXEL32_G(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumB += kernel.v[2][0] * (((double)XYO_PIXEL32_B(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumA += kernel.v[2][0] * (XYO_PIXEL32_A(pixel));

						pixel = getPixelX(imgThis, x, y + 1);
						sumR += kernel.v[2][1] * (((double)XYO_PIXEL32_R(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumG += kernel.v[2][1] * (((double)XYO_PIXEL32_G(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumB += kernel.v[2][1] * (((double)XYO_PIXEL32_B(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumA += kernel.v[2][1] * (XYO_PIXEL32_A(pixel));

						pixel = getPixelX(imgThis, x + 1, y + 1);
						sumR += kernel.v[2][2] * (((double)XYO_PIXEL32_R(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumG += kernel.v[2][2] * (((double)XYO_PIXEL32_G(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumB += kernel.v[2][2] * (((double)XYO_PIXEL32_B(pixel)) * ((double)XYO_PIXEL32_A(pixel)));
						sumA += kernel.v[2][2] * (XYO_PIXEL32_A(pixel));

						sumA = (kernel.normalA * sumA) / kernel.normalB;

						if(sumA > 0) {

							sumR /= sumA;
							sumG /= sumA;
							sumB /= sumA;

						} else {
							sumR = 0;
							sumG = 0;
							sumB = 0;
						};

						sumR = (kernel.normalA * sumR) / kernel.normalB;
						sumG = (kernel.normalA * sumG) / kernel.normalB;
						sumB = (kernel.normalA * sumB) / kernel.normalB;

						retV->pixel[y][x] = XYO_PIXEL32_PIXEL(pixelClampX(sumR), pixelClampX(sumG), pixelClampX(sumB), pixelClampX(sumA));

					};
				};
				return retV;
			};


		};
	};
};



