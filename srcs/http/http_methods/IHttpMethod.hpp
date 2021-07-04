#ifndef WEBSERV_IHTTPMETHOD_H
# define WEBSERV_IHTTPMETHOD_H

class IHttpMethod
{
	public:

    	virtual			~IHttpMethod(void);
		virtual void	handle(void) = 0;

		virtual bool			is_authorized(void) = 0; // Is the method authorized on the server
};

#endif
