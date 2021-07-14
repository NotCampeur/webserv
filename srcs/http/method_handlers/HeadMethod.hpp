#ifndef WEBSERV_HEADMETHOD_H
# define WEBSERV_HEADMETHOD_H

# include "IHttpMethod.hpp"

class HeadMethod : public IHttpMethod
{
	public:
    	HeadMethod(void);
    	~HeadMethod(void);
    	HeadMethod(HeadMethod const & src);
		HeadMethod &  operator=(HeadMethod const & src);

		StatusCodes::status_index_t	handle(void);
		bool						has_body(void);
		static IHttpMethod			*create_s(void);
		IHttpMethod					*create_v(void);
};

#endif
