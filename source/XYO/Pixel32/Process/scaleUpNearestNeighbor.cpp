// Pixel32
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	TPointer<Image> scaleUpNearestNeighbor(Image *imgThis, long int nx, long int ny) {
		TPointer<Image> retV;
		if (nx >= imgThis->width && ny >= imgThis->height) {
			retV = create(nx, ny);
			if (retV) {

				double inX = (double)(imgThis->width - 1);
				double inY = (double)(imgThis->height - 1);
				double outX = (double)(nx - 1);
				double outY = (double)(ny - 1);

				double deltaX = inX / outX;
				double deltaY = inY / outY;

				long int x;
				long int y;

				long int kX;
				long int kY;

				double mX;
				double mY;

				double dX;
				double dY;

				Pixel pixel0X;
				Pixel pixel1X;

				double pixelR0;
				double pixelG0;
				double pixelB0;
				double pixelA0;

				double pixelR1;
				double pixelG1;
				double pixelB1;
				double pixelA1;

				double pixelRY;
				double pixelGY;
				double pixelBY;
				double pixelAY;

				double pX;
				double pY;

				for (y = 0; y < ny; ++y) {
					for (x = 0; x < nx; ++x) {
						pX = ((((double)x)) * deltaX);
						pY = ((((double)y)) * deltaY);

						kX = (long int)pX;
						kY = (long int)pY;

						mX = (pX - kX);
						mY = (pY - kY);

						pixel0X = getPixel(imgThis, kX, kY);
						pixel1X = getPixel(imgThis, kX + 1, kY);

						pixelR0 = interpolateNearestNeighbor(XYO_PIXEL32_R(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_R(pixel1X) * XYO_PIXEL32_A(pixel1X), mX);
						pixelG0 = interpolateNearestNeighbor(XYO_PIXEL32_G(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_G(pixel1X) * XYO_PIXEL32_A(pixel1X), mX);
						pixelB0 = interpolateNearestNeighbor(XYO_PIXEL32_B(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_B(pixel1X) * XYO_PIXEL32_A(pixel1X), mX);
						pixelA0 = interpolateNearestNeighbor(XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_A(pixel1X), mX);

						pixel0X = getPixel(imgThis, kX, kY + 1);
						pixel1X = getPixel(imgThis, kX + 1, kY + 1);

						pixelR1 = interpolateNearestNeighbor(XYO_PIXEL32_R(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_R(pixel1X) * XYO_PIXEL32_A(pixel1X), mX);
						pixelG1 = interpolateNearestNeighbor(XYO_PIXEL32_G(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_G(pixel1X) * XYO_PIXEL32_A(pixel1X), mX);
						pixelB1 = interpolateNearestNeighbor(XYO_PIXEL32_B(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_B(pixel1X) * XYO_PIXEL32_A(pixel1X), mX);
						pixelA1 = interpolateNearestNeighbor(XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_A(pixel1X), mX);

						pixelRY = interpolateNearestNeighbor(pixelR0, pixelR1, mY);
						pixelGY = interpolateNearestNeighbor(pixelG0, pixelG1, mY);
						pixelBY = interpolateNearestNeighbor(pixelB0, pixelB1, mY);
						pixelAY = interpolateNearestNeighbor(pixelA0, pixelA1, mY);

						if (pixelAY > 0) {
							pixelRY /= pixelAY;
							pixelGY /= pixelAY;
							pixelBY /= pixelAY;
						} else {
							pixelRY = 0;
							pixelGY = 0;
							pixelBY = 0;
						};

						retV->pixel[y][x] = XYO_PIXEL32_PIXEL(pixelClampX(pixelRY), pixelClampX(pixelGY), pixelClampX(pixelBY), pixelClampX(pixelAY));
					};
				};
			};
		};
		return retV;
	};

};
