#ifndef MIME_H
# define MIME_H

# include "webserv.hpp"

class Mime
{
	public:

    	Mime(void);
    	Mime(Mime const & src);
    	~Mime(void);
		
		Mime &  operator=(Mime const & src);

		static const std::string &							get_content_type(std::string & extension);

	private:
		static const std::map<std::string, std::string> &	init_mime(void);

};

#endif
