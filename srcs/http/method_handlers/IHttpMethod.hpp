#ifndef WEBSERV_IHTTPMETHOD_H
# define WEBSERV_IHTTPMETHOD_H

class Request;
class Response;

class IHttpMethod
{
	public:
    	virtual					~IHttpMethod(void) {};
		virtual void			handle(Request & req, Response & resp) = 0;
		virtual bool			has_body(void) = 0;
};

#endif
