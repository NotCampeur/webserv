#ifndef WEBSERV_REQUESTURIPARSER_HPP
# define WEBSERV_REQUESTURIPARSER_HPP

# include "webserv.hpp"
# include "Request.hpp"
# include "HttpException.hpp"

class RequestUriParser
{
	private:
		enum uri_parsing_state
		{
			PATH,
			QUERY,
			FRAGMENT
		};

		uri_parsing_state	_state;
		Request::uri_t &	_uri;

	public:
		RequestUriParser(Request::uri_t & uri);
		RequestUriParser(RequestUriParser const & src);
		~RequestUriParser(void);

		bool				parse_char(char c);
		void				reset(void);

	private:
		RequestUriParser(void);
		RequestUriParser &  operator=(RequestUriParser const & src);

		size_t	uri_length(void) const;
};

#endif
