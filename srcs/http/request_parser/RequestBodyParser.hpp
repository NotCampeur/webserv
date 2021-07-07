#ifndef REQUESTBODYPARSER_H
# define REQUESTBODYPARSER_H

# include "RequestParser.hpp"
# include "Request.hpp"

class RequestBodyParser
{
	private:
		enum chunk_state {
			CHUNK_SIZE,
			CHUNK_EXTENSION,
			CHUNK_META_CRLF,
			CHUNK_DATA,
			CHUNK_DATA_CRLF,
			DONE
		};		

		chunk_state			_state;
		size_t				_size;
		Request &			_request;
		std::string			_hex;

	public:

    	RequestBodyParser(Request & req);
    	~RequestBodyParser(void);

		bool	parse_body(char *buf, size_t len);
		bool	parse_chunk(char *buf, size_t len);

	private:
		void	parse_chunk_char(char c);

	    RequestBodyParser(void);
		RequestBodyParser(RequestBodyParser const & src);
		RequestBodyParser &  operator=(RequestBodyParser const & src);
};

#endif
