#include "RequestUriParser.hpp"

RequestUriParser::RequestUriParser(Request::uri_t & uri) :
_state(PATH),
_uri(uri)
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
	return false;
}
