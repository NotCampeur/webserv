#ifndef WEBSERV_IHTTPMETHOD_H
# define WEBSERV_IHTTPMETHOD_H

class IHttpMethod
{
	public:
    	virtual					~IHttpMethod(void) {};
		virtual void			handle(void) = 0;
		virtual bool			has_body(void) = 0;
		virtual IHttpMethod *	create_v(void) = 0;
};

#endif
