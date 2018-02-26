// ==================================
//
// wordWrap.cpp
//
// ==================================

#include "wordWrap.h"

#include <sstream>

std::string WordWrap::WrapString(std::string& s, size_t charPerLine) {
	std::string result;

	std::istringstream iss(s);
	std::vector<std::string> words;
	std::string token;

	while (std::getline(iss, token, ' ')) {
		words.push_back(token);
	}

	size_t charCount = 0;
	bool prevWasRichTextTag = false;
	for (auto w : words) {
		// Rich text tags do not contribute to letter count.
		//result += w + " ";
		
		if (w[0] == '#') {
			result += " " + w;
			prevWasRichTextTag = true;
		}
		else {
			size_t wordSize = w.length();
			if (charCount == 0) {
				result += w;
				charCount = wordSize;
			}
			else if (charCount + wordSize > charPerLine) {
				if (prevWasRichTextTag) {
					result += " ";
				}
				result += "\n" + w;
				charCount = wordSize;
			}
			else {
				result += " " + w;
				charCount += 1 + wordSize;
			}
			prevWasRichTextTag = false;
		}
		
	}

	return result;
}