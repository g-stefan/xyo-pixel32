// Pixel32
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_PIXEL32_ICON_HPP
#define XYO_PIXEL32_ICON_HPP

#ifndef XYO_PIXEL32_BMP_HPP
#	include <XYO/Pixel32/Bmp.hpp>
#endif

namespace XYO::Pixel32 {

	class IconItem : public virtual Object {
			XYO_PLATFORM_DISALLOW_COPY_ASSIGN_MOVE(IconItem);

		public:
			inline IconItem(){};
			TPointer<Bmp> bmp;
			TPointer<Bmp> mask;
	};

};

#endif
