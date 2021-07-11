#ifndef WEBSERV_REQUESTBODYPARSER_H
# define WEBSERV_REQUESTBODYPARSER_H

# include "Request.hpp"
# include "HttpException.hpp"

class RequestBodyParser
{
	private:
		enum body_state {
			START,
			CONTENT_LEN,
			// CHUNK_SIZE,
			// CHUNK_EXTENSION,
			// CHUNK_META_CRLF,
			// CHUNK_DATA,
			// CHUNK_DATA_CRLF
		};

		body_state			_state;
		unsigned long		_size;
		Request &			_request;
		std::string			_hex;

	public:

    	RequestBodyParser(Request & req);
		RequestBodyParser(RequestBodyParser const & src);
		~RequestBodyParser(void);

		bool	parse_char(char c);
		void	reset(void);

	private:
		RequestBodyParser(void);
		RequestBodyParser &  operator=(RequestBodyParser const & src);
};

#endif
