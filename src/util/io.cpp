#include <segvc/util/io.hxx>

std::string readLine(std::istream &in) {
	std::string line;

	std::getline(in, line);

	return line;
}
