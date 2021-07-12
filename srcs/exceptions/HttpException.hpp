#ifndef WEBSERV_HTTPEXCEPTION_H
# define WEBSERV_HTTPEXCEPTION_H

# include "webserv.hpp"

class HttpException
{
	public:
		typedef enum error_index_e {
			CONTINUE_100,
			SWITCHING_PROTOCOLS_101,
			OK_200,
			CREATED_201,
			ACCEPTED_202,
			NON_AUTHORITATIVE_INFORMATION_203,
			NO_CONTENT_204,
			RESET_CONTENT_205,
			PARTIAL_CONTENT_206,
			MULTIPLE_CHOICES_300,
			MOVED_PERMANENTLY_301,
			FOUND_302,
			SEE_OTHER_303,
			NOT_MODIFIED_304,
			USE_PROXY_305,
			TEMPORARY_REDIRECT_307,
			BAD_REQUEST_400,
			UNAUTHORIZED_401,
			PAYMENT_REQUIRED_402,
			FORBIDDEN_403,
			NOT_FOUND_404,
			METHOD_NOT_ALLOWED_405,
			NOT_ACCEPTABLE_406,
			PROXY_AUTHENTICATION_REQUIRED_407,
			REQUEST_TIMEOUT_408,
			CONFLICT_409,
			GONE_410,
			LENGTH_REQUIRED_411,
			PRECONDITION_FAILED_412,
			REQUEST_ENTITY_TOO_LARGE_413,
			REQUEST_URI_TOO_LONG_414,
			UNSUPPORTED_MEDIA_TYPE_415,
			REQUESTED_RANGE_NOT_SATISFIABLE_416,
			EXPECTATION_FAILED_417,
			INTERNAL_SERVER_ERROR_500,
			NOT_IMPLEMENTED_501,
			BAD_GATEWAY_502,
			SERVICE_UNAVAILABLE_503,
			GATEWAY_TIMEOUT_504,
			HTTP_VERSION_NOT_SUPPORTE_505
		} error_index_t;

    	HttpException(error_index_t error) throw();
	    HttpException(HttpException const & src) throw();    	
		~HttpException(void) throw();
		
		std::string &	get_error_msg(void) const throw();
		int				get_error_value(void) const throw();

	private:
		HttpException(void) throw();
		HttpException &  operator=(HttpException const & src) throw();

		error_index_t _index;
};

#endif

/*
Parsing (Headers + body)
Validation: is path ok, is method allowed
Handle request:
	- Set response headers
	- Read/write body : 
		for a get, want to send as I read: fill response buffer -> call writeable on response -> flush buffer -> read file
		MethodObj creates read handler;
		read handler reads in response buffer;
		When response buffer is full: allow only send(), forbid additional reading

		for a Post: create a write handler to write to the file (writes body buffer at once)
					set headers
					send response;
		
		Annoying: Headers need to be set and sent before reading for a Get, but for a Post or Delete, need to perform the action before setting and sending the headers

	ClientHandler writable: check if response ready to be sent
		Different states: 
			- Ready to Send/Not ready
			- Response Complete/Incomplete (When complete, the ClientHandler should reset everything)


[FILTERS]

REQ_PARSER :
	-> Calls body parsing (if method.hasbody())
	-> Calls Validation
	-> Calls Sending (if error)
BODY_PARSER : parse normal/chunked body
	-> Calls Validation
	-> Calls Sending (if error)
VALIDATION : check path, method and sets direct path
	-> calls Handling
	-> calls Sending (if error)
HANDLING : method.handle: creates EventHandlers for Get and Post, spawns a process for CGI
	-> calls sending
SENDING : sets headers on first call
	-> Calls Handling ()
	-> If req is not complete, give it back to handling

	Objects (filters):
		- requestparser -> parse(char *buf, size_t len + response)
		- bodyparser	-> parse(char *buf, size_t len + response)	// Want these 2 to interact with the response as well! (to set error if necessary)

		- validator		-> validate(request + response (optional))
		- method handler -> handle(request + response)
		- sender	-> sendready(request + response)

*/