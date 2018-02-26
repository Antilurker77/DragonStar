// ==================================
//
// wordWrap.h
//
// Function that takes a string and
// calculates where to put new lines.
//
// ==================================

#include <string>
#include <vector>

#pragma once

namespace WordWrap {

	// Word wrap.
	std::string WrapString(std::string& s, size_t charPerLine = 50u);
}
