#include "CgiParser.hpp"
#include "HttpException.hpp"

CgiParser::CgiParser(void) :
_request_state(START)
{}

CgiParser::~CgiParser(void) {}

void
CgiParser::setbuffer(char *buf, size_t len)
{
	_buffer.clear();
	_buffer.insert(_buffer.begin(), buf, buf + len);
}

void
CgiParser::parse(void)
{
	// std::cerr << "Buffer content: " << _buffer << '\n';
	size_t i = 0;
	for (; i < _buffer.size(); i++)
	{
		parse_char(_buffer[i]);
		if (_request_state == BODY)
		{
			if (i > 0)
			{
				_buffer.erase(&_buffer[0], &_buffer[i]);
			}
			return ;
		}
			// std::cerr << "\n### PARSED CGI REQUEST ###\n"
			// for (std::map<std::string, std::string>::iterator it = _request.headers().begin(); it != _request.headers().end(); it++)
			// {
			// 	std::cerr << "Header name: " << (*it).first << '\t'
			// 	<< "Header value: " << (*it).second << '\n';
			// }
			// if (_request.method().has_body())
			// {
			// 	std::cerr << _request.get_body();
			// 	std::cerr << "Buf leftovers: " << _buffer_leftovers << '\n';
			// }
			break ;
	}
	_buffer.clear();
}

void
CgiParser::parse_char(char c)
{

	switch (_request_state)
	{
		case START :
		{
			if (c != '\r' && c != '\n')
			{
				_request_state = HEADERS;
				_header_parser.parse_char(c);
			}
			break ;
		}
		case HEADERS :
		{
			if (c == '\n' && _header_parser.get_header_name().empty()) // There are no more headers, move to Final CRLF
			{
				_request_state = FINAL_NL;
				break ;
			}
			if (_header_parser.parse_char(c))
				_request_state = HEADER_NL;
			break ;
		}
		case HEADER_NL :
		{
			if (c == '\n')
			{
				_request_state = HEADERS;
				add_header();
			}
			else
			{
				throw HttpException(StatusCodes::BAD_REQUEST_400);
			}
			break ;
		}
		case FINAL_NL :
		{
			if (c == '\n')
			{
				if (_request.method().has_body())
					_request_state = BODY;
				else
				{
					_request_state = DONE;
					break ;
				}
			}
			else
			{
				throw HttpException(StatusCodes::BAD_REQUEST_400);
			}
		}
		case BODY :
		{
			break;
		}
		default :
		{
			Logger(LOG_FILE, error_type, error_lvl) << "Request parser - unusual event (400 sent to client)";
			throw HttpException(StatusCodes::BAD_REQUEST_400); // Defensive: in case something odd happens, send a bad request
		}
	}
}

void
CgiParser::add_header(void)
{
	_headers.insert(_header_parser.get_header_name(), _header_parser.get_header_value());
	_header_parser.reset();
}

void
CgiParser::reset(void)
{
	_request_state = START;
	_header_parser.reset();
}