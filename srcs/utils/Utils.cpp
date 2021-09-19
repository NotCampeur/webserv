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
Utils::get_filename_from_path(const std::string & path)
{
	if (path.empty())
		return std::string();

	for (size_t i = path.size(); i > 0; --i)
	{
		if (path[i - 1] == '/' || i == 1)
		{
			return path.substr(i);
		}
	}
	return path;
}

bool
Utils::is_redirect(int code)
{
	if (code >= 300 && code <= 307 && code != 304)
		return true;
	return false;
}