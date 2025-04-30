// Pixel32
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_PIXEL32_DEPENDENCY_HPP
#define XYO_PIXEL32_DEPENDENCY_HPP

#ifndef XYO_SYSTEM_HPP
#	include <XYO/System.hpp>
#endif

#ifndef XYO_CRYPTOGRAPHY_HPP
#	include <XYO/Cryptography.hpp>
#endif

// -- Export

#ifdef XYO_PIXEL32_INTERNAL
#	define XYO_PIXEL32_EXPORT XYO_PLATFORM_LIBRARY_EXPORT
#else
#	define XYO_PIXEL32_EXPORT XYO_PLATFORM_LIBRARY_IMPORT
#endif
#ifdef XYO_PIXEL32_LIBRARY
#	undef XYO_PIXEL32_EXPORT
#	define XYO_PIXEL32_EXPORT
#endif

// --

namespace XYO::Pixel32 {
	using namespace XYO::System;
	using namespace XYO::Cryptography;
};

#endif
