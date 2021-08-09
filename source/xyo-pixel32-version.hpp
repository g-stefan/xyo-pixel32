//
// XYO Pixel32
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_PIXEL32_VERSION_HPP
#define XYO_PIXEL32_VERSION_HPP

#define XYO_PIXEL32_VERSION_ABCD               1,7,0,10
#define XYO_PIXEL32_VERSION_STR                 "1.7.0"
#define XYO_PIXEL32_VERSION_STR_BUILD           "10"
#define XYO_PIXEL32_VERSION_STR_DATETIME        "2021-08-05 20:38:15"

#ifndef XYO_RC

#ifndef XYO_PIXEL32__EXPORT_HPP
#include "xyo-pixel32--export.hpp"
#endif


namespace XYO {
	namespace Pixel32 {
		namespace Version {
			XYO_PIXEL32_EXPORT const char *version();
			XYO_PIXEL32_EXPORT const char *build();
			XYO_PIXEL32_EXPORT const char *versionWithBuild();
			XYO_PIXEL32_EXPORT const char *datetime();
		};
	};
};


#endif
#endif

