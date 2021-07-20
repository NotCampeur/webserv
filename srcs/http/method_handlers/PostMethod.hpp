#ifndef WEBSERV_POSTMETHOD_H
# define WEBSERV_POSTMETHOD_H

# include "IHttpMethod.hpp"

class PostMethod : public IHttpMethod
{
	public:
    	PostMethod(void);
    	~PostMethod(void);
    	PostMethod(PostMethod const & src);
		
		PostMethod &  operator=(PostMethod const & src);

		void					handle(Request & req, Response & resp, InitiationDispatcher & idis);
		bool					has_body(void);
		static IHttpMethod		*create_s(void);
		IHttpMethod				*create_v(void);
};

#endif
