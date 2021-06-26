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
	_path.clear();
	_query.clear();
	_fragment.clear();
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

const std::string &
RequestUriParser::getpath(void) const
{
	return _path;
}

const std::string &
RequestUriParser::getquery(void) const
{
	return _query;
}

const std::string &
RequestUriParser::getfragment(void) const
{
	return _fragment;
}
