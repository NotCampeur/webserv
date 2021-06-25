#include "RequestHeaderParser.hpp"

RequestHeaderParser::RequestHeaderParser(void) :
_state(FIELD_NAME)
{}

RequestHeaderParser::RequestHeaderParser(RequestHeaderParser const & src)
{
    (void)src;
}

RequestHeaderParser::~RequestHeaderParser(void) {}

RequestHeaderParser &
RequestHeaderParser::operator=(RequestHeaderParser const & src)
{
    return (*this);
}

void
RequestHeaderParser::reset(void)
{
	_state = FIELD_NAME;
	_field_name.empty();
	_field_value.empty();
}

bool
RequestHeaderParser::parse_char(char c) throw()
{
	switch (_state)
	{
		case FIELD_NAME :
		{
			// if (c == '\r')
			// {
			// 	_request_state = FINAL_CRLF;
			// 	return ;
			// }
			if(c == ':')
			{
				if (!_field_name.empty() && iswhitespace(_field_name[_field_name.size() - 1])) // Must not be a WP between header name and ':'
				{
					throw(400);
				}
				_state = COLON;
			}
			else
			{
				_field_name += c;
			}
			break ;
		}
		case COLON :
		{
			if (!iswhitespace(c)) // This condition does not break. If we have something else than a WP, we need to store this char (falling into FIELD_VALUE)
			{
				_state = FIELD_VALUE;
				_field_value += c;
			}
			break ;
		}
		case FIELD_VALUE :
		{
			if (iswhitespace(c))
			{
				_state = TRAILING_WP;
			}
			else if (c == '\r')
			{
				_state = HEADER_CRLF;
			}
			else
			{
				_field_value += c;
			}
			break ;
		}
		case TRAILING_WP :
		{
			if (!iswhitespace(c))
			{
				if (c == '\r')
				{
					_state = HEADER_CRLF;
				}
				else
				{
					throw(400); //Error code TBC
				}
			}
			break ;
		}
		case HEADER_CRLF :
		{
			if (c != '\n')
			{
				throw(400); // Code TBC
			}
			return true;
		}
	}
}

bool
RequestHeaderParser::iswhitespace(char c)
{
	if (c == ' ' || c == '\t')
		return true;
	return false;
}