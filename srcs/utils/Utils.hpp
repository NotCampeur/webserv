#ifndef WEBSERV_UTILS_HPP
# define WEBSERV_UTILS_HPP

#include <string>

namespace Utils
{
	std::string		get_file_ext(const std::string & filename);
	std::string		get_working_path();
	std::string		get_filename_from_path(const std::string & path);
	bool			is_redirect(int code);
};

#endif
