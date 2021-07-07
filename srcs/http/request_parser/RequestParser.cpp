#include "RequestParser.hpp"

RequestParser::RequestParser(Request & req) :
_request(req),
_uri_parser(req.uri()),
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

		if (_request_state == ERROR)
		{
			_request.complete() = true;
			_buffer_leftovers.clear(); // In case of an error, flush buffer

			std::cerr << "***Request error nb: " << _debug_code << " ***\n";
			break ;
		}
		else if (_request_state == DONE) // Should set request to Complete here
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
				request_error(1); // Request nb TBC
			}
			break ;
		}
		case HEADERS :
		{
			if (c == '\r' && _header_parser.get_header_name().empty())
			{
				_request_state = FINAL_CRLF;
				break ;
			}
			try
			{
				if (_header_parser.parse_char(c))
					_request_state = HEADER_CRLF;
			}
			catch(int error_code)
			{
				request_error(error_code);
			}
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
				request_error(2); // Code TBC
			}
			break ;
		}
		case FINAL_CRLF :
		{
			if (c == '\n')
				_request_state = DONE;
			else
			{
				request_error(3); // Req nb TBC
			}
		}
		case BODY :
		{
			break;
		}
		case DONE :	// Apparently I need to handle all enumeration variables within switch
			break ;
		case ERROR :
			break ;
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
        request_error(4); // Error code TBC
    }
	else
	{
        _http_method += c;
		if (_http_method.size() > 6)
		{
			request_error(5); // Code 500
			return ;
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
			request_error(6); // Code 505
			return ;
		}
	}
	else
	{
		_http_version += c;
		if (_http_version.size() > correct_version.size())
		{
			request_error(7); // Error code TBC - Should not be a bad_version error, but a bad_request_line error (bad spacing errors fall here)
		}
	}
}

void
RequestParser::request_error(int code)
{
    _request_state = ERROR;
	_debug_code = code;
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