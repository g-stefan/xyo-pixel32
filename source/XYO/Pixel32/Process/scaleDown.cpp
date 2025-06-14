// Pixel32
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	TPointer<Image> scaleDown(Image *imgThis, long int nx, long int ny) {
		uint32_t factorX = imgThis->width / nx;
		uint32_t factorY = imgThis->height / ny;
		TPointer<Image> retV = imgThis;

		if (factorY > 1) {
			if (factorX > 1) {
				retV = scaleDownX2(retV);
				return scaleDown(retV, nx, ny);
			};
			retV = scaleDownX2OnY(retV);
			return scaleDown(retV, nx, ny);
		};
		if (factorX > 1) {
			retV = scaleDownX2OnX(retV);
			return scaleDown(retV, nx, ny);
		};
		if (imgThis->height == ny) {
			if (imgThis->width == nx) {
				return retV;
			};
			retV = scaleUpBicubic(retV, nx * 2, ny);
			retV = scaleDownX2OnX(retV);
			return retV;
		};
		if (imgThis->width == nx) {
			retV = scaleUpBicubic(retV, nx, ny * 2);
			retV = scaleDownX2OnY(retV);
			return retV;
		};
		retV = scaleUpBicubic(retV, nx * 2, ny * 2);
		retV = scaleDownX2(retV);
		return retV;
	};

};
