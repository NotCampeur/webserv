#include "RequestParser.hpp"

RequestParser::RequestParser(Request & req) :
_request(req),
_uri_parser(req.uri()),
_body_parser(req),
_request_state(START)
{}

RequestParser::RequestParser(RequestParser const & src) :
_request(src._request),
_uri_parser(src._uri_parser),
_header_parser(src._header_parser),
_body_parser(src._body_parser),
_request_state(src._request_state),
_buffer_leftovers(src._buffer_leftovers),
_http_method(src._http_method),
_http_version(src._http_version)
{}


RequestParser::~RequestParser(void) {}

void
RequestParser::setbuffer(char *buf, size_t len)
{
	_buffer.clear();
	_buffer.insert(_buffer.begin(), buf, buf + len);
}

// void
// RequestParser::setbuffer(std::string & str)
// {
// 	_buffer = str;
// }

void
RequestParser::parse(void)
{
	// std::cerr << "Buffer content: " << _buffer << '\n';
	
	size_t i = 0;
	for (; i < _buffer.size(); i++)
	{
		parse_char(_buffer[i]);
		if (_request_state == DONE)
		{
			_request.complete() = true;
			_buffer_leftovers.clear();
			_buffer_leftovers.insert(_buffer_leftovers.begin(), &_buffer[i + 1], &_buffer[_buffer.size()]);

			// std::cerr << "\n### PARSED REQUEST ###\n"
			// << "Method: " << _http_method << '\n'
			// << "Uri (path): " << _request.uri().path << '\n'
			// << "Uri (query): " << _request.uri().query << '\n'
			// << "Uri (fragment): " << _request.uri().fragment << '\n'
			// << "Http version: " << _http_version << '\n';

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
	}
	_buffer.clear();
}

void
RequestParser::parse_char(char c)
{

	switch (_request_state)
	{
		case START :
		{
			if (c != '\r' && c != '\n')
			{
				_request_state = METHOD;
				_http_method += c;
			}
			break ;
		}
		case METHOD :
		{
			parse_method(c);
			break ;
		}
		case URI :
		{
			if (_uri_parser.parse_char(c))
				_request_state = VERSION;
			break ;
		}
		case VERSION :
		{
			check_version(c);
			break ;
		}
		case REQ_LINE_CRLF :
		{
			if (c == '\n')
			{
				_request_state = HEADERS;
			}
			else
			{
				throw HttpException(StatusCodes::BAD_REQUEST_400);
			}
			break ;
		}
		case HEADERS :
		{
			if (c == '\r' && _header_parser.get_header_name().empty()) // There are no more headers, move to Final CRLF
			{
				_request_state = FINAL_CRLF;
				break ;
			}
			if (_header_parser.parse_char(c))
				_request_state = HEADER_CRLF;
			break ;
		}
		case HEADER_CRLF :
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
		case FINAL_CRLF :
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
			if (_body_parser.parse_char(c))
				_request_state = DONE;
			break;
		}
		case DONE :
			break ;
		default :
		{
			Logger(LOG_FILE, error_type, error_lvl) << "Request parser - unusual event (400 sent to client)";
			throw HttpException(StatusCodes::BAD_REQUEST_400); // Defensive: in case something odd happens, send a bad request
		}
	}
}

void
RequestParser::parse_method(char c)
{
    static std::string	available_methods[] = {
        "GET",
		"HEAD",
        "POST",
        "DELETE"
    };

    static size_t 		method_count = 4;

	// static IHttpMethod * (*create[4])(void) =
	// {
	// 	GetMethod::create_s,
	// 	HeadMethod::create_s,
	// 	PostMethod::create_s,
	// 	DeleteMethod::create_s
	// };

	static IHttpMethod* method[4] = {
		&GetMethod::get_instance(),
		&HeadMethod::get_instance(),
		&PostMethod::get_instance(),
		&DeleteMethod::get_instance()
	};

	if (c == ' ')
	{
        for (size_t i = 0; i < method_count; i++)
        {
            if (available_methods[i] == _http_method)
            {
				std::cout << "Method: " << i << " created\n";
				_request.set_method(method[i]);
				_request_state = URI;
				return ;
            }
        }
		throw HttpException(StatusCodes::METHOD_NOT_ALLOWED_405);
    }
	else
	{
        _http_method += c;
		if (_http_method.size() > 6)
		{
			throw HttpException(StatusCodes::METHOD_NOT_ALLOWED_405);
		}
	}
}

void
RequestParser::check_version(char c)
{
    static std::string	correct_version("HTTP/1.1");

	if (c == '\r')
	{
		if (_http_version == correct_version)
		{
			_request_state = REQ_LINE_CRLF;
			return ;
		}
		else
		{
			if (correct_version_format())
			{
				throw HttpException(StatusCodes::HTTP_VERSION_NOT_SUPPORTE_505);
			}
			else
			{
				throw HttpException(StatusCodes::BAD_REQUEST_400);
			}
		}
	}
	else
	{
		_http_version += c;
		if (_http_version.size() > correct_version.size())
		{
			throw HttpException(StatusCodes::BAD_REQUEST_400); // Not be a bad_version error, but a bad_request error as the size exceeds that of version syntax standard
		}
	}
}


bool
RequestParser::correct_version_format(void)
{
	if (_http_version.size() == 8)
	{
		if (
			_http_version[0] == 'H' &&
			_http_version[1] == 'T' &&
			_http_version[2] == 'T' &&
			_http_version[3] == 'P' &&
			_http_version[4] == '/' &&
			std::isdigit(_http_version[5]) &&
			_http_version[6] == '.' &&
			std::isdigit(_http_version[7])
		)
			return true;
	}
	return false;
}

void
RequestParser::add_header(void)
{
	_request.add_header(_header_parser.get_header_name(), _header_parser.get_header_value());
	_header_parser.reset();
}

void
RequestParser::reset(void)
{
    _request_state = START;
    _uri_parser.reset();
	_header_parser.reset();
	_body_parser.reset();
	_http_method.clear();
	_http_version.clear();
}

void
RequestParser::next_request(void)
{
	reset();
	_request.reset();
	_buffer.insert(_buffer.begin(), _buffer_leftovers.begin(), _buffer_leftovers.end());
	_buffer_leftovers.clear();
	std::cerr << "* Buffer Leftovers: *\n" << std::string(&_buffer_leftovers[0], _buffer_leftovers.size()) << '\n';
}