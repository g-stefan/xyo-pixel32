// Pixel32
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_PIXEL32_KERNEL3X3_HPP
#define XYO_PIXEL32_KERNEL3X3_HPP

#ifndef XYO_PIXEL32_DEPENDENCY_HPP
#	include <XYO/Pixel32/Dependency.hpp>
#endif

namespace XYO::Pixel32 {

	class Kernel3X3 : public Object {
			XYO_DISALLOW_COPY_ASSIGN_MOVE(Kernel3X3);

		public:
			double v[3][3];
			double normalA;
			double normalB;
			XYO_PIXEL32_EXPORT Kernel3X3();
			XYO_PIXEL32_EXPORT Kernel3X3(const double v_[3][3], const double normalA_, const double normalB_);
			XYO_PIXEL32_EXPORT void copy(Kernel3X3 &src);

			XYO_PIXEL32_EXPORT static Kernel3X3 filter8X1;
			XYO_PIXEL32_EXPORT static Kernel3X3 gaussian;
			XYO_PIXEL32_EXPORT static Kernel3X3 blur;
			XYO_PIXEL32_EXPORT static Kernel3X3 sharpen;
			XYO_PIXEL32_EXPORT static Kernel3X3 edgeDetection;
			XYO_PIXEL32_EXPORT static Kernel3X3 edgeDetectionH;
			XYO_PIXEL32_EXPORT static Kernel3X3 edgeDetectionV;
			XYO_PIXEL32_EXPORT static Kernel3X3 gradientDetectionH;
			XYO_PIXEL32_EXPORT static Kernel3X3 gradientDetectionV;
	};

};

#endif
