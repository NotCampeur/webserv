#ifndef WEBSERV_UTILS_HPP
# define WEBSERV_UTILS_HPP

#include <string>
#include <vector>

namespace Utils
{
	std::string					get_file_ext(const std::string & filename);
	std::string					get_working_path();
	std::string					get_filename_from_path(const std::string & path);
	bool						is_redirect(int code);
	std::vector<std::string>	split(const std::string &src, const std::string &sep);
	std::string					rm_charset(std::string str, std::string charset);
};

#endif
