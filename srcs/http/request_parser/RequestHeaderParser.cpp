#include "RequestHeaderParser.hpp"

RequestHeaderParser::RequestHeaderParser(void) :
_state(FIELD_NAME)
{}

// RequestHeaderParser::RequestHeaderParser(RequestHeaderParser const & src)
// {
//     (void)src;
// }

RequestHeaderParser::~RequestHeaderParser(void) {}

// RequestHeaderParser &
// RequestHeaderParser::operator=(RequestHeaderParser const & src)
// {
//     return (*this);
// }

void
RequestHeaderParser::reset(void)
{
	_state = FIELD_NAME;
	_field_name.clear();
	_field_value.clear();
}

bool
RequestHeaderParser::parse_char(char c)
{
	switch (_state)
	{
		case FIELD_NAME :
		{
			if(c == ':')
			{
				if (!_field_name.empty() && iswhitespace(_field_name[_field_name.size() - 1])) // Must not be a WP between header name and ':'
				{
					throw(40); // Error code 400
				}
				_state = COLON;
			}
			else
			{
				_field_name += c; // Could use "to_lower" here as field names are case insensitive
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
			if (c == '\r')
			{
				return true;
			}
			else
			{
				_field_value += c;
			}
			break ;
		}
	}
	return false;
}

bool
RequestHeaderParser::iswhitespace(char c)
{
	if (c == ' ' || c == '\t')
		return true;
	return false;
}


std::string
RequestHeaderParser::get_header_name(void) const
{
	return _field_name;
}

std::string
RequestHeaderParser::get_header_value(void) const
{
	return _field_value;
}