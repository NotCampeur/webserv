#ifndef WEBSERV_GETMETHOD_H
# define WEBSERV_GETMETHOD_H

# include "IHttpMethod.hpp"
# include "SYSException.hpp"

class GetMethod : public IHttpMethod
{
	public:
    	GetMethod(void);
    	~GetMethod(void);
    	GetMethod(GetMethod const & src);

		GetMethod &  operator=(GetMethod const & src);

		void					handle(Request & req, Response & resp);
		bool					has_body(void);
		static IHttpMethod		*create_s(void);
		IHttpMethod				*create_v(void);
};

#endif
