// Pixel32
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_PIXEL32_VERSION_HPP
#define XYO_PIXEL32_VERSION_HPP

#ifndef XYO_PIXEL32_DEPENDENCY_HPP
#	include <XYO/Pixel32/Dependency.hpp>
#endif

namespace XYO::Pixel32::Version {

	XYO_PIXEL32_EXPORT const char *version();
	XYO_PIXEL32_EXPORT const char *build();
	XYO_PIXEL32_EXPORT const char *versionWithBuild();
	XYO_PIXEL32_EXPORT const char *datetime();

};

#endif
