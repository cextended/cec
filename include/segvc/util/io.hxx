#pragma once
#include <iostream>
#include <string>

namespace segvc {

inline std::string readLine(std::istream &in) {
	std::string line;

	std::getline(in, line);

	return line;
}

}
