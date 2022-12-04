// Pixel32
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/License.hpp>

namespace XYO::Pixel32::License {

	static const char *licenseHeader_ =
	    "\r\n"
	    "XYO\r\n"
	    "\r\n"
	    "MIT License (MIT)\r\n"
	    "\r\n"
	    "Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>\r\n"
	    "\r\n";

	static const char *shortLicense_ =
	    "\r\n"
	    "Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>\r\n"
	    "MIT License (MIT) <http://opensource.org/licenses/MIT>\r\n"
	    "\r\n";

	const char *licenseHeader() {
		return licenseHeader_;
	};

	const char *licenseBody() {
		return "\r\n"
		#include <XYO/Pixel32/License.xyo-pixel32.Source.cpp>
			    "\r\n"
			    "libpng\r\n"
			    "\r\n"
		#include <XYO/Pixel32/License.libpng.Source.cpp>
			    "\r\n"
			    "zlib\r\n"
			    "\r\n"
		#include <XYO/Pixel32/License.zlib.Source.cpp>
			    "\r\n";
	};

	const char *shortLicense() {
		return shortLicense_;
	};

};
