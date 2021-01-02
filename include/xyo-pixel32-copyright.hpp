//
// XYO Pixel32
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_PIXEL32_COPYRIGHT_HPP
#define XYO_PIXEL32_COPYRIGHT_HPP

#define XYO_PIXEL32_COPYRIGHT            "Copyright (C) Grigore Stefan."
#define XYO_PIXEL32_PUBLISHER            "Grigore Stefan"
#define XYO_PIXEL32_COMPANY              XYO_PIXEL32_PUBLISHER
#define XYO_PIXEL32_CONTACT              "g_stefan@yahoo.com"
#define XYO_PIXEL32_FULL_COPYRIGHT       XYO_PIXEL32_COPYRIGHT " <" XYO_PIXEL32_CONTACT ">"

#ifndef XYO_RC

#ifndef XYO_PIXEL32__EXPORT_HPP
#include "xyo-pixel32--export.hpp"
#endif

namespace XYO {
	namespace Pixel32 {
		namespace Copyright {
			XYO_PIXEL32_EXPORT const char *copyright();
			XYO_PIXEL32_EXPORT const char *publisher();
			XYO_PIXEL32_EXPORT const char *company();
			XYO_PIXEL32_EXPORT const char *contact();
			XYO_PIXEL32_EXPORT const char *fullCopyright();
		};
	};
};


#endif
#endif
