#include "RequestUriParser.hpp"

RequestUriParser::RequestUriParser(Request::uri_t & uri) :
_state(PATH),
_uri(uri)
{}

RequestUriParser::RequestUriParser(RequestUriParser const & src) :
_state(src._state),
_uri(src._uri)
{}

RequestUriParser::~RequestUriParser(void) {}

void
RequestUriParser::reset(void)
{
	_state = PATH;
}

bool
RequestUriParser::parse_char(char c)
{
	switch (_state)
	{
		case PATH :
		{
			if (c == '?')
			{
				_state = QUERY;
			}
			else if (c == '#')
			{
				_state = FRAGMENT;
			}
			else if (c == ' ')
			{
				return true;
			}
			else
			{
				_uri.path += c;
			}
			break ;
		}
		case QUERY :
		{
			if (c == '#')
			{
				_state = FRAGMENT;
			}
			else if (c == ' ')
			{
				return true;
			}
			else
			{
				_uri.query += c;
			}
			break ;
		}
		case FRAGMENT :
		{
			if (c == ' ')
			{
				return true;
			}
			else
			{
				_uri.fragment += c;
			}
			break ;
		}
	}
	if (uri_length() > MAX_URI_SIZE)
		throw HttpException(HttpException::REQUEST_URI_TOO_LONG_414);
	return false;
}


size_t
RequestUriParser::uri_length(void) const
{
	return (_uri.path.size() + _uri.query.size() + _uri.fragment.size());
}