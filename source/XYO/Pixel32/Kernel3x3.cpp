// Pixel32
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Kernel3x3.hpp>

namespace XYO::Pixel32 {

	Kernel3X3::Kernel3X3() {

		v[0][0] = 0;
		v[0][1] = 0;
		v[0][2] = 0;

		v[1][0] = 0;
		v[1][1] = 1;
		v[1][2] = 0;

		v[2][0] = 0;
		v[2][1] = 0;
		v[2][2] = 0;

		normalA = 1;
		normalB = 1;
	};

	Kernel3X3::Kernel3X3(const double v_[3][3], const double normalA_, const double normalB_) {
		v[0][0] = v_[0][0];
		v[0][1] = v_[0][1];
		v[0][2] = v_[0][2];

		v[1][0] = v_[1][0];
		v[1][1] = v_[1][1];
		v[1][2] = v_[1][2];

		v[2][0] = v_[2][0];
		v[2][1] = v_[2][1];
		v[2][2] = v_[2][2];

		normalA = normalA_;
		normalB = normalB_;
	};

	void Kernel3X3::copy(Kernel3X3 &src) {
		memcpy(v, src.v, sizeof(v));
		normalA = src.normalA;
		normalB = src.normalB;
	};

	static double filter8X1_[3][3] = {
	    {1, 1, 1},
	    {1, 8, 1},
	    {1, 1, 1}};

	static double gaussian_[3][3] = {
	    {1, 2, 1},
	    {2, 4, 2},
	    {1, 2, 1}};

	static double blur_[3][3] = {
	    {1, 1, 1},
	    {1, 1, 1},
	    {1, 1, 1}};

	static double sharpen_[3][3] = {
	    {0, -1, 0},
	    {-1, 5, -1},
	    {0, -1, 0}};

	static double edgeDetection_[3][3] = {
	    {0, -1, 0},
	    {-1, 4, -1},
	    {0, -1, 0}};

	static double edgeDetectionH_[3][3] = {
	    {0, 0, 0},
	    {-1, 2, -1},
	    {0, 0, 0}};

	static double edgeDetectionV_[3][3] = {
	    {0, -1, 0},
	    {0, 2, 0},
	    {0, -1, 0}};

	static double gradientDetectionH_[3][3] = {
	    {-1, -1, -1},
	    {0, 0, 0},
	    {1, 1, 1}};

	static double gradientDetectionV_[3][3] = {
	    {-1, 0, 1},
	    {-1, 0, 1},
	    {-1, 0, 1}};

	Kernel3X3 Kernel3X3::filter8X1(filter8X1_, 1, 16);
	Kernel3X3 Kernel3X3::gaussian(gaussian_, 1, 16);
	Kernel3X3 Kernel3X3::blur(blur_, 1, 9);
	Kernel3X3 Kernel3X3::sharpen(sharpen_, 1, 1);
	Kernel3X3 Kernel3X3::edgeDetection(edgeDetection_, 1, 1);
	Kernel3X3 Kernel3X3::edgeDetectionH(edgeDetectionH_, 1, 1);
	Kernel3X3 Kernel3X3::edgeDetectionV(edgeDetectionV_, 1, 1);
	Kernel3X3 Kernel3X3::gradientDetectionH(gradientDetectionH_, 1, 1);
	Kernel3X3 Kernel3X3::gradientDetectionV(gradientDetectionV_, 1, 1);

};
