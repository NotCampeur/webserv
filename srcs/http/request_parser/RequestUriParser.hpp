#ifndef REQUESTURIPARSER_H
# define REQUESTURIPARSER_H

# include "webserv.hpp"

class RequestUriParser
{
	private:

		typedef enum uri_parsing_state {
			PATH,
			QUERY,
			FRAGMENT
		};

		std::string 		_path;
		std::string 		_query;
		std::string 		_fragment;
		uri_parsing_state	_state;

	public:

		RequestUriParser(void);
		RequestUriParser(RequestUriParser const & src);
		~RequestUriParser(void);

		RequestUriParser &  operator=(RequestUriParser const & src);

		bool			parse_char(char c);
		std::string &	getpath(void) const;
		std::string &	getquery(void) const;
		std::string &	getfragment(void) const;
		void			reset(void);

};

#endif
