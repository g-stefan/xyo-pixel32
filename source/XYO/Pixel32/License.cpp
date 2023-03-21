// Pixel32
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/License.hpp>
#include <XYO/Pixel32/Copyright.hpp>

namespace XYO::Pixel32::License {

	std::string license() {
		std::string retV;
		retV += ManagedMemory::License::licenseMITHeader();
		retV += Copyright::copyright();
		retV += "\r\n";
		retV += ManagedMemory::License::licenseMITContent();

		retV +=
		    "\r\n"
		    "libpng\r\n"
		    "\r\n"
#include <XYO/Pixel32/License.libpng.Source.cpp>
		    "\r\n"
		    "zlib\r\n"
		    "\r\n"
#include <XYO/Pixel32/License.zlib.Source.cpp>
		    ;

		return retV;
	};

	std::string shortLicense() {
		return XYO::ManagedMemory::License::shortLicense();
	};

};
