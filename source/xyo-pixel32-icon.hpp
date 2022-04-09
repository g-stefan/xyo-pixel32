//
// XYO Pixel32
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_PIXEL32_ICON_HPP
#define XYO_PIXEL32_ICON_HPP

#ifndef XYO_PIXEL32_BMP_HPP
#	include "xyo-pixel32-bmp.hpp"
#endif

namespace XYO {
	namespace Pixel32 {

		using namespace XYO;

		class IconItem : public virtual Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(IconItem);

			public:
				inline IconItem(){};
				TPointer<Bmp> bmp;
				TPointer<Bmp> mask;
		};

	};
};

#endif
