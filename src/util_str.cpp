#include "util_str.hpp"

// Converts an int into a string
std::string int2str(int x) {
	std::stringstream type;
	type << x;
	return type.str();
}
