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

		StatusCodes::status_index_t	handle(void);
		bool						has_body(void);
		static IHttpMethod			*create_s(void);
		IHttpMethod					*create_v(void);
};

#endif
