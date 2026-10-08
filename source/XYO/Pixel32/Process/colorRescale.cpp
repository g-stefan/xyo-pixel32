// Pixel32
// Copyright (c) 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

	static inline long int rescale(long int value, long int min, long int max) {
		if (max > min) {
			return ((value - min) * 0xFF) / (max - min);
		};
		// Constant channel, nothing to stretch
		return value;
	};

	void colorRescale(Image *imgInOut) {
		long int x;
		long int y;
		Pixel cx;
		long int cxa;
		long int cxr;
		long int cxg;
		long int cxb;

		long int mina = 0xFF;
		long int minr = 0xFF;
		long int ming = 0xFF;
		long int minb = 0xFF;

		long int maxa = 0x00;
		long int maxr = 0x00;
		long int maxg = 0x00;
		long int maxb = 0x00;

		for (y = 0; y < imgInOut->height; ++y) {
			for (x = 0; x < imgInOut->width; ++x) {
				cx = imgInOut->pixel[y][x];

				cxa = XYO_PIXEL32_A(cx);
				if (cxa < mina) {
					mina = cxa;
				};
				if (cxa > maxa) {
					maxa = cxa;
				};

				cxr = XYO_PIXEL32_R(cx);
				if (cxr < minr) {
					minr = cxr;
				};
				if (cxr > maxr) {
					maxr = cxr;
				};

				cxg = XYO_PIXEL32_G(cx);
				if (cxg < ming) {
					ming = cxg;
				};
				if (cxg > maxg) {
					maxg = cxg;
				};

				cxb = XYO_PIXEL32_B(cx);
				if (cxb < minb) {
					minb = cxb;
				};
				if (cxb > maxb) {
					maxb = cxb;
				};
			};
		};

		for (y = 0; y < imgInOut->height; ++y) {
			for (x = 0; x < imgInOut->width; ++x) {
				cx = imgInOut->pixel[y][x];
				cxa = rescale(XYO_PIXEL32_A(cx), mina, maxa);
				cxr = rescale(XYO_PIXEL32_R(cx), minr, maxr);
				cxg = rescale(XYO_PIXEL32_G(cx), ming, maxg);
				cxb = rescale(XYO_PIXEL32_B(cx), minb, maxb);
				imgInOut->pixel[y][x] = XYO_PIXEL32_PIXEL(cxr, cxg, cxb, cxa);
			};
		};
	};

};
