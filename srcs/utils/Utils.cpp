#include "Utils.hpp"
#include "CgiHandler.hpp"
#include "InitiationDispatcher.hpp"

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
		file_ext = filename.substr(i + 1);
	}
	return file_ext;
}

std::string
Utils::get_working_path()
{
	char temp[FILENAME_MAX];
	return (getcwd(temp, sizeof(temp)) ? std::string( temp ) : std::string(""));
}