#include "RequestHeaderParser.hpp"

RequestHeaderParser::RequestHeaderParser(void) :
_state(FIELD_NAME)
{}

RequestHeaderParser::~RequestHeaderParser(void) {}

void
RequestHeaderParser::reset(void)
{
	_state = LEADING_WP;
	_field_name.clear();
	_field_value.clear();
}

bool
RequestHeaderParser::parse_char(char c)
{
	switch (_state)
	{
		case LEADING_WP :
		{
			if (!iswhitespace(c))
			{
				_state = FIELD_NAME;
				addto_fieldname(c);
			}
			break ;
		}
		case FIELD_NAME :
		{
			if(c == ':')
			{
				if (!_field_name.empty() && iswhitespace(_field_name[_field_name.size() - 1])) // Must not be a WP between header name and ':'
				{
					throw(HttpException::BAD_REQUEST_400);
				}
				_state = COLON;
			}
			else
			{
				addto_fieldname(c);
			}
			break ;
		}
		case COLON :
		{
			if (!iswhitespace(c)) // Remove WP
			{
				_state = FIELD_VALUE;
				addto_fieldvalue(c);
			}
			break ;
		}
		case FIELD_VALUE :
		{
			if (c == '\r')
			{
				remove_trailing_wp(_field_value);
				return true;
			}
			else
			{
				addto_fieldvalue(c);
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

std::string &
RequestHeaderParser::get_header_name(void)
{
	return _field_name;
}

void	
RequestHeaderParser::remove_trailing_wp(std::string & s)
{
	if (s.size() > 0)
	{
		size_t i = _field_value.size() - 1;
		while (iswhitespace(_field_value[i]))
		{
			i--;
		}
		_field_value.erase(i + 1);
	}
}

std::string &
RequestHeaderParser::get_header_value(void)
{
	return _field_value;
}

void
RequestHeaderParser::addto_fieldname(char c)
{
	_field_name += std::tolower(c);
}

void
RequestHeaderParser::addto_fieldvalue(char c)
{
	_field_value += std::tolower(c);
}