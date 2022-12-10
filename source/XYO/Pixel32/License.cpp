// Pixel32
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/License.hpp>

namespace XYO::Pixel32::License {

	const char *license() {
#include <XYO/Pixel32/License.xyo-pixel32.Source.cpp>
		"\r\n"
		"libpng\r\n"
		"\r\n"
#include <XYO/Pixel32/License.libpng.Source.cpp>
		"\r\n"
		"zlib\r\n"
		"\r\n"
#include <XYO/Pixel32/License.zlib.Source.cpp>
		    ;
	};

	const char *shortLicense() {
		return XYO::ManagedMemory::License::shortLicense();
	};

	const char *licenseBody() {
		return
#include <XYO/Pixel32/License.xyo-pixel32.Source.cpp>
		    "\r\n"
		    "libpng\r\n"
		    "\r\n"
#include <XYO/Pixel32/License.libpng.Source.cpp>
		    "\r\n"
		    "zlib\r\n"
		    "\r\n"
#include <XYO/Pixel32/License.zlib.Source.cpp>
		    ;
	};

	const char *shortLicense() {
		return shortLicense_;
	};

};
