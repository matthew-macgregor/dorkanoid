// Copyright (c) 2015 Matthew MacGregor
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "util_str.hpp"

// Converts an int into a string
std::string int2str(int x) {
	std::stringstream type;
	type << x;
	return type.str();
}
