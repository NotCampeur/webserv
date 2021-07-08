#ifndef WEBSERV_EXCEPTION_H
# define WEBSERV_EXCEPTION_H

# include "webserv.hpp"

class HttpException : std::exception
{
	private:
		int	_error;

	public:

    	HttpException(int error);
    	HttpException(HttpException const & src);
    	~HttpException(void);
		
		HttpException &  operator=(HttpException const & src);

		int	error_code(void);
		// const char * what(void) const throw();

	private:
		HttpException(void);
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