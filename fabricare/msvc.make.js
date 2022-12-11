// Created by Grigore Stefan <g_stefan@yahoo.com>
// Public domain (Unlicense) <http://unlicense.org>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: Unlicense

exitIf(fileToCS("--touch=source/XYO/Pixel32/License.cpp", "--file-in=source/XYO/Pixel32/License/xyo-pixel32.txt", "--file-out=source/XYO/Pixel32/License.xyo-pixel32.Source.cpp", "--is-string-direct"));
exitIf(fileToCS("--touch=source/XYO/Pixel32/License.cpp", "--file-in=source/XYO/Pixel32/License/libpng.txt", "--file-out=source/XYO/Pixel32/License.libpng.Source.cpp", "--is-string-direct"));
exitIf(fileToCS("--touch=source/XYO/Pixel32/License.cpp", "--file-in=source/XYO/Pixel32/License/zlib.txt", "--file-out=source/XYO/Pixel32/License.zlib.Source.cpp", "--is-string-direct"));

if (!Fabricare.include("msvc.make." + Project.make)) {
	messageError("Don't know how to make '" + Project.make + "'!");
	exit(1);
};
