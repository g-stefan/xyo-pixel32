// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32.hpp>

using namespace XYO::Pixel32;


void test1(int cmdN, char *cmdS[]) {
        TPointer<Bitmap> bmp=Process::bitmap32LoadPNG("../../test/test.01.input.png");
        TPointer<Image> image=Process::imageFromBitmap(bmp);
	bmp->save("test.01.output.bmp");
	Process::pngSave(image, "test.01.output.png");
};

void test2(int cmdN, char *cmdS[]) {
        TPointer<Bitmap> bmp=Process::bitmap32LoadPNG("../../test/test.02.input.png");
        TPointer<Image> image=Process::imageFromBitmap(bmp);
	bmp->save("test.02.output.bmp");
	Process::pngSave(image, "test.02.output.png");
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
