#ifndef WEBSERV_GETMETHOD_H
# define WEBSERV_GETMETHOD_H

# include "IHttpMethod.hpp"

class GetMethod : public IHttpMethod
{
	public:
    	GetMethod(void);
    	~GetMethod(void);
    	GetMethod(GetMethod const & src);

		GetMethod &  operator=(GetMethod const & src);

		void				handle(void);
		bool				has_body(void);
		static IHttpMethod	*create_s(void);
		IHttpMethod			*create_v(void);
};

#endif
