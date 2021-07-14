#ifndef WEBSERV_IHTTPMETHOD_H
# define WEBSERV_IHTTPMETHOD_H

# include "StatusCodes.hpp"

class IHttpMethod
{
	public:
    	virtual								~IHttpMethod(void) {};
		virtual StatusCodes::status_index_t	handle(void) = 0;
		virtual bool						has_body(void) = 0;
		virtual IHttpMethod *				create_v(void) = 0;
};

#endif
