#include "RequestUriParser.hpp"

RequestUriParser::RequestUriParser(void) :
_state(PATH)
{}

// RequestUriParser::RequestUriParser(RequestUriParser const & src)
// {
//     (void)src;
// }

RequestUriParser::~RequestUriParser(void) {}

// RequestUriParser &
// RequestUriParser::operator=(RequestUriParser const & src)
// {
//     return (*this);
// }

void
RequestUriParser::reset(void)
{
	_state = PATH;
	_path.empty();
	_query.empty();
	_fragment.empty();
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
				_path += c;
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
				_query += c;
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
				_fragment += c;
			}
			break ;
		}
	}
	return false;
}