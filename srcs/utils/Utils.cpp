#include "Utils.hpp"

Utils::Utils(void) {}

Utils::Utils(Utils const & src)
{
    (void)src;
}

Utils::~Utils(void) {}

Utils &
Utils::operator=(Utils const & src)
{
	(void)src;
    return (*this);
}

std::string
Utils::get_file_ext(const std::string & filename)
{
	int i = filename.size() - 1;

	for(; i >= 0; i--)
	{
		if (filename[i] == '.')
			break;
	}
	std::string file_ext;
	if (i >= 0)
	{
		file_ext = filename.substr(i);
	}
	return file_ext;
}