//
// XYO Pixel32
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_PIXEL32_IMAGE_HPP
#define XYO_PIXEL32_IMAGE_HPP

#ifndef XYO_PIXEL32__DEPENDENCY_HPP
#	include "xyo-pixel32--dependency.hpp"
#endif

namespace XYO {
	namespace Pixel32 {

		using namespace XYO;

		typedef uint32_t Pixel;

#define XYO_PIXEL32_R(x) ((x)&0xFF)
#define XYO_PIXEL32_G(x) (((x) >> 8) & 0xFF)
#define XYO_PIXEL32_B(x) (((x) >> 16) & 0xFF)
#define XYO_PIXEL32_A(x) (((x) >> 24) & 0xFF)
#define XYO_PIXEL32_RGB(x) (((x)&0x00FFFFFF) | 0xFF000000)

#define XYO_PIXEL32_PIXEL(R, G, B, A) (((uint32_t)(((A)&0xFF) << 24)) | (((B)&0xFF) << 16) | (((G)&0xFF) << 8) | ((R)&0xFF))

#define XYO_PIXEL32_CHANGE_R(Color, X) Color = (((Color)&0xFFFFFF00) | ((uint32_t)((X)&0xFF)))
#define XYO_PIXEL32_CHANGE_G(Color, X) Color = (((Color)&0xFFFF00FF) | ((uint32_t)(((X)&0xFF) << 8)))
#define XYO_PIXEL32_CHANGE_B(Color, X) Color = (((Color)&0xFF00FFFF) | ((uint32_t)(((X)&0xFF) << 16)))
#define XYO_PIXEL32_CHANGE_A(Color, X) Color = (((Color)&0x00FFFFFF) | ((uint32_t)(((X)&0xFF) << 24)))
#define XYO_PIXEL32_CHANGE_RGB(Color, R, G, B) Color = (((Color)&0xFF000000) | ((uint32_t)((R)&0xFF)) || ((uint32_t)(((G)&0xFF) << 8)) | ((uint32_t)(((B)&0xFF) << 16)))

		class Image : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(Image);

			public:
				long int width;
				long int height;

				Pixel *pixelMap;
				Pixel **pixel;

				XYO_PIXEL32_EXPORT Image();
				XYO_PIXEL32_EXPORT ~Image();
		};

	};
};

#endif
