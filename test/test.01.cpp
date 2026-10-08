// Created by Grigore Stefan <g_stefan@yahoo.com>
// Public domain (Unlicense) <http://unlicense.org>
// SPDX-FileCopyrightText: 2016-2026 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: Unlicense

#include <XYO/Pixel32.hpp>

using namespace XYO::Pixel32;


void test1(int cmdN, char *cmdS[]) {
	TPointer<Bitmap> bmp = Process::bitmap32LoadPNG("../../test/test.01.input.png");
	if (!bmp) {
		throw std::runtime_error("test.01.input.png: load");
	};
	TPointer<Image> image = Process::imageFromBitmap(bmp);
	if (!image || !bmp->save("test.01.output.bmp") || !Process::pngSave(image, "test.01.output.png")) {
		throw std::runtime_error("test.01: save");
	};
};

void test2(int cmdN, char *cmdS[]) {
	TPointer<Bitmap> bmp = Process::bitmap32LoadPNG("../../test/test.02.input.png");
	if (!bmp) {
		throw std::runtime_error("test.02.input.png: load");
	};
	TPointer<Image> image = Process::imageFromBitmap(bmp);
	if (!image || !bmp->save("test.02.output.bmp") || !Process::pngSave(image, "test.02.output.png")) {
		throw std::runtime_error("test.02: save");
	};
};

int main(int cmdN, char *cmdS[]) {
	try {

		test1(cmdN,cmdS);
		test2(cmdN,cmdS);
		return 0;

	} catch (const std::exception &e) {
		printf("* Error: %s\n", e.what());
	} catch (...) {
		printf("* Error: Unknown\n");
	};

	return 1;
};
