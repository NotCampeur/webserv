#ifndef WEBSERV_IHTTPMETHOD_H
# define WEBSERV_IHTTPMETHOD_H

class Request;
class Response;
class InitiationDispatcher;
# include "InitiationDispatcher.hpp"

class IHttpMethod
{
	public:
    	virtual								~IHttpMethod(void) {};
		//Performs http method actions (Delete, get...), set response status code and optionally adds headers to the response. <- TBU
		virtual void						handle(Request & req, Response & resp, InitiationDispatcher & idis) = 0;
		virtual bool						has_body(void) = 0;
		virtual IHttpMethod *				create_v(void) = 0;
};

#endif
