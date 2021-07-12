#ifndef WEBSERV_RESPONSE_H
# define WEBSERV_RESPONSE_H

# include "webserv.hpp"

class Response
{
	private:
		std::string			_buffer;
		const std::string	_version;
		bool				_ready;

	public:

    	Response(void);
    	Response(Response const & src);
    	~Response(void);

		Response &  operator=(Response const & src);

		bool				isready(void) const;
		void				set_readyness(bool b);
		void				fill_response(std::string &str);
		const std::string &	get_response(void) const;
		void				reset(void);

	private:

};

#endif
