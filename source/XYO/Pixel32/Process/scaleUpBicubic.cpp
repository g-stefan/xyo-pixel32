// Pixel32
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	TPointer<Image> scaleUpBicubic(Image *imgThis, long int nx, long int ny) {
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
				Pixel pixel2X;
				Pixel pixel3X;

				double pixelR0;
				double pixelG0;
				double pixelB0;
				double pixelA0;

				double pixelR1;
				double pixelG1;
				double pixelB1;
				double pixelA1;

				double pixelR2;
				double pixelG2;
				double pixelB2;
				double pixelA2;

				double pixelR3;
				double pixelG3;
				double pixelB3;
				double pixelA3;

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

						pixel0X = getPixel(imgThis, kX - 1, kY - 1);
						pixel1X = getPixel(imgThis, kX, kY - 1);
						pixel2X = getPixel(imgThis, kX + 1, kY - 1);
						pixel3X = getPixel(imgThis, kX + 2, kY - 1);

						pixelR0 = interpolateCubic(XYO_PIXEL32_R(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_R(pixel1X) * XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_R(pixel2X) * XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_R(pixel3X) * XYO_PIXEL32_A(pixel3X), mX);
						pixelG0 = interpolateCubic(XYO_PIXEL32_G(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_G(pixel1X) * XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_G(pixel2X) * XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_G(pixel3X) * XYO_PIXEL32_A(pixel3X), mX);
						pixelB0 = interpolateCubic(XYO_PIXEL32_B(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_B(pixel1X) * XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_B(pixel2X) * XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_B(pixel3X) * XYO_PIXEL32_A(pixel3X), mX);
						pixelA0 = interpolateCubic(XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_A(pixel3X), mX);

						pixel0X = getPixel(imgThis, kX - 1, kY);
						pixel1X = getPixel(imgThis, kX, kY);
						pixel2X = getPixel(imgThis, kX + 1, kY);
						pixel3X = getPixel(imgThis, kX + 2, kY);

						pixelR1 = interpolateCubic(XYO_PIXEL32_R(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_R(pixel1X) * XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_R(pixel2X) * XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_R(pixel3X) * XYO_PIXEL32_A(pixel3X), mX);
						pixelG1 = interpolateCubic(XYO_PIXEL32_G(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_G(pixel1X) * XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_G(pixel2X) * XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_G(pixel3X) * XYO_PIXEL32_A(pixel3X), mX);
						pixelB1 = interpolateCubic(XYO_PIXEL32_B(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_B(pixel1X) * XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_B(pixel2X) * XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_B(pixel3X) * XYO_PIXEL32_A(pixel3X), mX);
						pixelA1 = interpolateCubic(XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_A(pixel3X), mX);

						pixel0X = getPixel(imgThis, kX - 1, kY + 1);
						pixel1X = getPixel(imgThis, kX, kY + 1);
						pixel2X = getPixel(imgThis, kX + 1, kY + 1);
						pixel3X = getPixel(imgThis, kX + 2, kY + 1);

						pixelR2 = interpolateCubic(XYO_PIXEL32_R(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_R(pixel1X) * XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_R(pixel2X) * XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_R(pixel3X) * XYO_PIXEL32_A(pixel3X), mX);
						pixelG2 = interpolateCubic(XYO_PIXEL32_G(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_G(pixel1X) * XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_G(pixel2X) * XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_G(pixel3X) * XYO_PIXEL32_A(pixel3X), mX);
						pixelB2 = interpolateCubic(XYO_PIXEL32_B(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_B(pixel1X) * XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_B(pixel2X) * XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_B(pixel3X) * XYO_PIXEL32_A(pixel3X), mX);
						pixelA2 = interpolateCubic(XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_A(pixel3X), mX);

						pixel0X = getPixel(imgThis, kX - 1, kY + 2);
						pixel1X = getPixel(imgThis, kX, kY + 2);
						pixel2X = getPixel(imgThis, kX + 1, kY + 2);
						pixel3X = getPixel(imgThis, kX + 2, kY + 2);

						pixelR3 = interpolateCubic(XYO_PIXEL32_R(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_R(pixel1X) * XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_R(pixel2X) * XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_R(pixel3X) * XYO_PIXEL32_A(pixel3X), mX);
						pixelG3 = interpolateCubic(XYO_PIXEL32_G(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_G(pixel1X) * XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_G(pixel2X) * XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_G(pixel3X) * XYO_PIXEL32_A(pixel3X), mX);
						pixelB3 = interpolateCubic(XYO_PIXEL32_B(pixel0X) * XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_B(pixel1X) * XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_B(pixel2X) * XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_B(pixel3X) * XYO_PIXEL32_A(pixel3X), mX);
						pixelA3 = interpolateCubic(XYO_PIXEL32_A(pixel0X), XYO_PIXEL32_A(pixel1X), XYO_PIXEL32_A(pixel2X), XYO_PIXEL32_A(pixel3X), mX);

						pixelRY = interpolateCubic(pixelR0, pixelR1, pixelR2, pixelR3, mY);
						pixelGY = interpolateCubic(pixelG0, pixelG1, pixelG2, pixelG3, mY);
						pixelBY = interpolateCubic(pixelB0, pixelB1, pixelB2, pixelB3, mY);
						pixelAY = interpolateCubic(pixelA0, pixelA1, pixelA2, pixelA3, mY);

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
