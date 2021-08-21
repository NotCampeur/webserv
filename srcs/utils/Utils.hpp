#ifndef UTILS_H
# define UTILS_H

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

	private:

};

#endif
