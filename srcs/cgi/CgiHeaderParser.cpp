#include "CgiHeaderParser.hpp"
#include "webserv_param.hpp"
#include "HttpException.hpp"
#include "StatusCodes.hpp"

CgiHeaderParser::CgiHeaderParser(void) :
_state(FIELD_NAME),
_size(0)
{}

CgiHeaderParser::CgiHeaderParser(CgiHeaderParser const & src) :
_state(src._state),
_field_name(src._field_name),
_field_value(src._field_value),
_size(src._size)
{}

CgiHeaderParser::~CgiHeaderParser(void) {}

void
CgiHeaderParser::reset(void)
{
	_state = LEADING_WP;
	_field_name.clear();
	_field_value.clear();
	_size = 0;
}

bool
CgiHeaderParser::parse_char(char c)
{
	_size++;
	if (_size > MAX_CGI_HEADER_SIZE)
	{
		Logger(error_type, error_lvl) << "Max cgi header file size reached";
		throw HttpException(StatusCodes::BAD_REQUEST_400);
	}
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
			if (std::iscntrl(c))
			{
				Logger(error_type, error_lvl) << "Cgi header parsing: control character found in cgi header field name with value: " << int(c) << '\n';
				throw HttpException(StatusCodes::BAD_REQUEST_400);
			}
			else if(c == ':')
			{
				if (!_field_name.empty() && iswhitespace(_field_name[_field_name.size() - 1])) // Must not be a WP between header name and ':'
				{
					Logger(error_type, error_lvl) << "Cgi header parsing: whitespace found in field name: \"" << _field_name << "\"";
					throw HttpException(StatusCodes::BAD_REQUEST_400);
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
			if (c == '\n')
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
CgiHeaderParser::iswhitespace(char c)
{
	if (c == ' ' || c == '\t')
		return true;
	return false;
}

std::string &
CgiHeaderParser::get_header_name(void)
{
	return _field_name;
}

std::string &
CgiHeaderParser::get_header_value(void)
{
	return _field_value;
}

void	
CgiHeaderParser::remove_trailing_wp(std::string & s)
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

void
CgiHeaderParser::addto_fieldname(char c)
{
	_field_name += std::tolower(c);
}

void
CgiHeaderParser::addto_fieldvalue(char c)
{
	_field_value += c;
}