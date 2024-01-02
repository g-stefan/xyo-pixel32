// Pixel32
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Process.hpp>

namespace XYO::Pixel32::Process {

	using namespace XYO;

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

				cxa = XYO_PIXEL32_A(cx);
				if ((maxa - mina) > 0) {
					cxa = ((cxa - mina) * 0xFF) / (maxa - mina);
				} else {
					cxa = 0xFF;
				};

				cxr = XYO_PIXEL32_R(cx);
				if ((maxr - minr) > 0) {
					cxr = ((cxr - minr) * 0xFF) / (maxr - minr);
				} else {
					cxr = 0xFF;
				};

				cxg = XYO_PIXEL32_G(cx);
				if ((maxg - ming) > 0) {
					cxg = ((cxg - ming) * 0xFF) / (maxg - ming);
				} else {
					cxg = 0xFF;
				};

				cxb = XYO_PIXEL32_G(cx);
				if ((maxb - minb) > 0) {
					cxb = ((cxb - minb) * 0xFF) / (maxb - minb);
				} else {
					cxb = 0xFF;
				};

				imgInOut->pixel[y][x] = XYO_PIXEL32_PIXEL(cxr, cxg, cxb, cxa);
			};
		};
	};

};
