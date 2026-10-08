// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	// Kernels with a positive sum (blur, sharpen) are applied on alpha weighted colors,
	// kernels with a zero or negative sum (edge, gradient) on colors, keeping the alpha.
	// Samples outside the image repeat the edge pixels.
	TPointer<Image> kernel3X3(Image *imgThis, Kernel3X3 &kernel) {
		long int lx = imgThis->width;
		long int ly = imgThis->height;
		long int x;
		long int y;
		int i;
		int j;
		double sumR;
		double sumG;
		double sumB;
		double sumA;
		double k;
		double a;
		Pixel pixel;
		Pixel *row[3];
		long int column[3];

		TPointer<Image> retV;

		retV = create(lx, ly);
		if (!retV) {
			return nullptr;
		};

		double sum = 0;
		for (i = 0; i < 3; ++i) {
			for (j = 0; j < 3; ++j) {
				sum += kernel.v[i][j];
			};
		};
		bool alphaWeighted = (sum > 1e-9);

		for (y = 0; y < ly; ++y) {
			row[0] = imgThis->pixel[(y > 0) ? y - 1 : 0];
			row[1] = imgThis->pixel[y];
			row[2] = imgThis->pixel[(y + 1 < ly) ? y + 1 : ly - 1];
			for (x = 0; x < lx; ++x) {
				column[0] = (x > 0) ? x - 1 : 0;
				column[1] = x;
				column[2] = (x + 1 < lx) ? x + 1 : lx - 1;

				sumR = 0;
				sumG = 0;
				sumB = 0;
				sumA = 0;

				if (alphaWeighted) {
					for (i = 0; i < 3; ++i) {
						for (j = 0; j < 3; ++j) {
							pixel = row[i][column[j]];
							k = kernel.v[i][j];
							a = k * (double)XYO_PIXEL32_A(pixel);
							sumR += a * (double)XYO_PIXEL32_R(pixel);
							sumG += a * (double)XYO_PIXEL32_G(pixel);
							sumB += a * (double)XYO_PIXEL32_B(pixel);
							sumA += a;
						};
					};

					if (sumA > 0) {
						sumR /= sumA;
						sumG /= sumA;
						sumB /= sumA;
					} else {
						sumR = 0;
						sumG = 0;
						sumB = 0;
					};

					sumA = (kernel.normalA * sumA) / kernel.normalB;
				} else {
					for (i = 0; i < 3; ++i) {
						for (j = 0; j < 3; ++j) {
							pixel = row[i][column[j]];
							k = kernel.v[i][j];
							sumR += k * (double)XYO_PIXEL32_R(pixel);
							sumG += k * (double)XYO_PIXEL32_G(pixel);
							sumB += k * (double)XYO_PIXEL32_B(pixel);
						};
					};

					sumR = (kernel.normalA * sumR) / kernel.normalB;
					sumG = (kernel.normalA * sumG) / kernel.normalB;
					sumB = (kernel.normalA * sumB) / kernel.normalB;
					sumA = XYO_PIXEL32_A(row[1][x]);
				};

				retV->pixel[y][x] = XYO_PIXEL32_PIXEL(pixelRound(sumR), pixelRound(sumG), pixelRound(sumB), pixelRound(sumA));
			};
		};
		return retV;
	};

};
