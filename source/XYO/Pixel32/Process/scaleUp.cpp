// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	// Double the size while the target is at least twice as large,
	// smoothing each step, then interpolate to the exact size
	TPointer<Image> scaleUp(Image *imgThis, long int nx, long int ny) {
		if ((nx < imgThis->width) || (ny < imgThis->height)) {
			return nullptr;
		};
		TPointer<Image> retV = imgThis;
		long int factorX;
		long int factorY;
		for (;;) {
			factorX = nx / retV->width;
			factorY = ny / retV->height;
			if ((factorX <= 1) && (factorY <= 1)) {
				break;
			};
			retV = scaleUpBicubic(retV, (factorX > 1) ? retV->width * 2 : retV->width, (factorY > 1) ? retV->height * 2 : retV->height);
			if (!retV) {
				return nullptr;
			};
			retV = kernel3X3(retV, Kernel3X3::filter8X1);
			if (!retV) {
				return nullptr;
			};
		};
		if ((retV->width == nx) && (retV->height == ny)) {
			return retV;
		};
		return scaleUpBicubic(retV, nx, ny);
	};

};
