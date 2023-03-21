// Pixel32
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/Pixel32/Copyright.hpp>
#include <XYO/Pixel32/Copyright.rh>

namespace XYO::Pixel32::Copyright {

	static const char *copyright_ = XYO_PIXEL32_COPYRIGHT;
	static const char *publisher_ = XYO_PIXEL32_PUBLISHER;
	static const char *company_ = XYO_PIXEL32_COMPANY;
	static const char *contact_ = XYO_PIXEL32_CONTACT;

	std::string copyright() {
		return copyright_;
	};

	std::string publisher() {
		return publisher_;
	};

	std::string company() {
		return company_;
	};

	std::string contact() {
		return contact_;
	};

};
