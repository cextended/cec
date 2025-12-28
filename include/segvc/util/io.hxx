#include <iostream>
#include <string>

inline std::string readLine(std::istream &in) {
	std::string line;

	std::getline(in, line);

	return line;
}
