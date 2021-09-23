#include "Utils.hpp"
#include "CgiHandler.hpp"
#include "InitiationDispatcher.hpp"

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

std::vector<std::string>
Utils::split(const std::string &src, const std::string &sep)
{
	std::vector<std::string> result;
	size_t pos(src.find(sep));
	size_t begin(0);
	
	while (pos != std::string::npos)
	{
		result.push_back(src.substr(begin, pos - begin));
		begin = pos + sep.size();
		pos = src.find(sep, begin);
	}
	result.push_back(src.substr(begin));
	return (result);
}

std::string
Utils::rm_charset(std::string str, std::string charset)
{
	size_t	charset_len(0);

	if (str.empty() || charset.empty())
		return str;
	charset_len = charset.size();
	for (unsigned int i = 0; i < charset_len; ++i)
	{
		str.erase(remove(str.begin(), str.end(), charset[i]), str.end());
	}
	return str;
}
