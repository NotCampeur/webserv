#ifndef WEBSERV_UTILS_HPP
# define WEBSERV_UTILS_HPP

#include <string>
class CgiHandler;
class Request;
class Response;

class Utils
{
	public:

    	Utils(void);
    	Utils(Utils const & src);
    	~Utils(void);

		Utils &  operator=(Utils const & src);

		static	std::string		get_file_ext(const std::string & filename);
		static	std::string		get_working_path();
	private:

};

#endif
