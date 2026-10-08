// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>
#include <vector>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	TPointer<Image> scaleUpNearestNeighbor(Image *imgThis, long int nx, long int ny) {
		TPointer<Image> retV;
		if ((nx < imgThis->width) || (ny < imgThis->height)) {
			return nullptr;
		};
		retV = create(nx, ny);
		if (!retV) {
			return nullptr;
		};

		long int lx = imgThis->width;
		long int ly = imgThis->height;
		double deltaX = (nx > 1) ? (double)(lx - 1) / (double)(nx - 1) : 0.0;
		double deltaY = (ny > 1) ? (double)(ly - 1) / (double)(ny - 1) : 0.0;

		// Source column for each output column
		std::vector<long int> column((size_t)nx);

		long int x;
		long int y;
		long int k;
		double p;
		Pixel *row;

		for (x = 0; x < nx; ++x) {
			p = (double)x * deltaX;
			k = (long int)p;
			if ((p - (double)k) > 0.5) {
				++k;
			};
			column[x] = (k < lx) ? k : lx - 1;
		};

		for (y = 0; y < ny; ++y) {
			p = (double)y * deltaY;
			k = (long int)p;
			if ((p - (double)k) > 0.5) {
				++k;
			};
			row = imgThis->pixel[(k < ly) ? k : ly - 1];
			for (x = 0; x < nx; ++x) {
				retV->pixel[y][x] = row[column[x]];
			};
		};
		return retV;
	};

};
