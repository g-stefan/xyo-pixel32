// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	// Halve the size while the target is at most half as large,
	// then reach the exact size by interpolating to twice the size and halving
	TPointer<Image> scaleDown(Image *imgThis, long int nx, long int ny) {
		if ((nx <= 0) || (ny <= 0)) {
			return nullptr;
		};
		TPointer<Image> retV = imgThis;
		long int factorX;
		long int factorY;
		for (;;) {
			factorX = retV->width / nx;
			factorY = retV->height / ny;
			if (factorY > 1) {
				if (factorX > 1) {
					retV = scaleDownX2(retV);
				} else {
					retV = scaleDownX2OnY(retV);
				};
			} else if (factorX > 1) {
				retV = scaleDownX2OnX(retV);
			} else {
				break;
			};
			if (!retV) {
				return nullptr;
			};
		};
		if (retV->height == ny) {
			if (retV->width == nx) {
				return retV;
			};
			retV = scaleUpBicubic(retV, nx * 2, ny);
			if (!retV) {
				return nullptr;
			};
			return scaleDownX2OnX(retV);
		};
		if (retV->width == nx) {
			retV = scaleUpBicubic(retV, nx, ny * 2);
			if (!retV) {
				return nullptr;
			};
			return scaleDownX2OnY(retV);
		};
		retV = scaleUpBicubic(retV, nx * 2, ny * 2);
		if (!retV) {
			return nullptr;
		};
		return scaleDownX2(retV);
	};

};
