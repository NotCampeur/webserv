#ifndef WEBSERV_GETMETHOD_H
# define WEBSERV_GETMETHOD_H

# include "IHttpMethod.hpp"
# include "SYSException.hpp"

class GetMethod : public IHttpMethod
{
	private:
		off_t	_file_size;

	public:
    	GetMethod(void);
    	~GetMethod(void);
    	GetMethod(GetMethod const & src);

		GetMethod &  operator=(GetMethod const & src);

		void					handle(Request & req, Response & resp, InitiationDispatcher & idis);
		bool					has_body(void);
		static IHttpMethod		*create_s(void);
		IHttpMethod				*create_v(void);
	
	private:

		void	set_content_length_header(const std::string & path, Response & resp);
		off_t	get_file_size(const std::string & path);
};

#endif
