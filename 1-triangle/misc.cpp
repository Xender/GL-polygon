#include "misc.h"

#include <iostream>
using namespace std;

//TODO - I don't know, whether this function is actually sane, but I hope so ^ ^
//Returns content of file, null terminated
//CAUTION - if file cannot be opened, returns empty vector (no null terminator!)
std::vector<char> ReadFile(const char* filename, bool verbose_on_error)
{
	std::ifstream file(filename);
	if(!file)
	{
		if(verbose_on_error)
			cerr << "Warning - Could not open file: " << filename << endl;
		return std::vector<char>();
	}

	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	std::vector<char> v(size + 1);

	file.seekg(0, std::ios::beg);
	file.read(v.data(), size);
	v.resize(file.gcount() + 1); // number of actually read characters
	v.back() = '\0';

	return v;
}
