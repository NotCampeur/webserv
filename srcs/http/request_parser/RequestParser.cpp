#include "RequestParser.hpp"

RequestParser::RequestParser(Request & req) :
_request(req),
_uri_parser(req.uri()),
_body_parser(req),
_request_state(START)
{}

RequestParser::~RequestParser(void) {}

void
RequestParser::parse(const char *buffer, size_t len)
{
	std::cerr << "Buffer content: " << std::string(buffer, len) << '\n';

	for (size_t i = 0; i < len; i++)
	{
		parse_char(buffer[i]);
		if (_request_state == DONE) // Should set request to Complete here
		{
			_request.complete() = true;
			_buffer_leftovers = std::string(&buffer[i], len - i - 1);

			std::cerr << "\n### PARSED REQUEST ###\n"
			<< "Method: " << _http_method << '\n'
			<< "Uri (path): " << _request.uri().path << '\n'
			<< "Uri (query): " << _request.uri().query << '\n'
			<< "Uri (fragment): " << _request.uri().fragment << '\n'
			<< "Http version: " << _http_version << '\n';

			for (std::map<std::string, std::string>::iterator it = _request.headers().begin(); it != _request.headers().end(); it++)
			{
				std::cerr << "Header name: " << (*it).first << '\t'
				<< "Header value: " << (*it).second << '\n';
			}
			std::cerr << _request.get_body();
			std::cerr << "Buf leftovers: " << _buffer_leftovers << '\n';
			break ;
		}
	}
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
				throw HttpException(HttpException::BAD_REQUEST_400);
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
				throw HttpException(HttpException::BAD_REQUEST_400);
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
					_request_state = DONE;
			}
			else
			{
				throw HttpException(HttpException::BAD_REQUEST_400);
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
			throw HttpException(HttpException::BAD_REQUEST_400); // Defensive: in case something odd happens, send a bad request
		}
	}
}

/*

HttpMethod {

    handle();

}

GetMethod : HttpMethod {


}

HttpMethod *method = find_method_by_name("GET")
if (!method) {

}

method->handle(req, res)

res.body()
res.status(200)
res.end()

*/

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

	static IHttpMethod * (*create[4])(void) =
	{
		GetMethod::create,
		HeadMethod::create,
		PostMethod::create,
		DeleteMethod::create
	};

	if (c == ' ')
	{
        for (size_t i = 0; i < method_count; i++)
        {
            if (available_methods[i] == _http_method)
            {
				_request.method() = *create[i]();
                _request_state = URI;
				return ;
            }
        }
		throw HttpException(HttpException::NOT_IMPLEMENTED_501);
    }
	else
	{
        _http_method += c;
		if (_http_method.size() > 6)
		{
			throw HttpException(HttpException::NOT_IMPLEMENTED_501);
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
			throw HttpException(HttpException::HTTP_VERSION_NOT_SUPPORTE_505);
		}
	}
	else
	{
		_http_version += c;
		if (_http_version.size() > correct_version.size())
		{
			throw HttpException(HttpException::BAD_REQUEST_400); // Not be a bad_version error, but a bad_request error as the size exceeds that of version syntax standard
		}
	}
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
	parse(_buffer_leftovers.c_str(), _buffer_leftovers.size());
	std::cerr << "* Buffer Leftovers: *\n" << _buffer_leftovers << '\n';
}