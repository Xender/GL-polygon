#include <fstream>
#include <vector>

//TODO - I don't know, whether this function is actually sane, but I hope so ^ ^
//Returns content of file, null terminated
//CAUTION - if file cannot be opened, returns empty vector (no null terminator!)
std::vector<char> ReadFile(const char* filename, bool verbose_on_error = false);
