#include "RequestParser.hpp"

RequestParser::RequestParser(void)
{
    reset();
}

// RequestParser::RequestParser(RequestParser const & src) :
// _request(src._request),
// _offset(src._offset)
// {}

RequestParser::~RequestParser(void) {}

// RequestParser &
// RequestParser::operator=(RequestParser const & src)
// {
//     return (*this);
// }

void
RequestParser::parse(const char *buffer, size_t len)
{
	std::cerr << "Buffer content: " << std::string(buffer, len) << '\n';

	for (size_t i = 0; i < len; i++)
	{
		parse_char(buffer[i]);

		if (_request_state == ERROR)
		{
			_complete = true;
			_buffer_leftovers.clear(); // In case of an error, flush buffer

			std::cerr << "***Request error nb: " << _debug_code << '\n';
			break ;
		}
		else if (_request_state == DONE) // Should set request to Complete here
		{
			_complete = true;
			_buffer_leftovers = std::string(&buffer[i], len - i - 1);

			std::cerr << "\n### PARSED REQUEST ###\n"
			<< "Method: " << _http_method << '\n'
			<< "Uri (path): " << _uri_parser.getpath() << '\n'
			<< "Uri (query): " << _uri_parser.getquery() << '\n'
			<< "Uri (fragment): " << _uri_parser.getfragment() << '\n'
			<< "Http version: " << _http_version << '\n';

			for (std::map<std::string, std::string>::iterator it = _headers.begin(); it != _headers.end(); it++)
			{
				std::cerr << "Header name: " << (*it).first << '\t'
				<< "Header value: " << (*it).second << '\n';
			}
			break ;
		}
	}
}

void
RequestParser::parse_char(char c)
{
	switch (_request_state)
	{
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
        "POST",
        "DELETE"
    };
    static size_t 		method_count = 3;    

	if (c == ' ')
	{
        for (size_t i = 0; i < method_count; i++)
        {
            if (available_methods[i] == _http_method)
            {
                // _request->setmethod(static_cast<Request::http_method>(i));
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
			request_error(7); // Error code TBC
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
	_headers.insert(std::pair<std::string, std::string>(_header_parser.get_header_name(), _header_parser.get_header_value()));
	_header_parser.reset();
}

bool
RequestParser::iscomplete(void) const
{
	return _complete;
}

void
RequestParser::reset(void)
{
	_complete = false;
    _request_state = METHOD;
    _http_method.clear();
	_http_version.clear();
    _uri_parser.reset();
	_header_parser.reset();
}

void
RequestParser::next_request(void)
{
	reset();
	parse(_buffer_leftovers.c_str(), _buffer_leftovers.size());
	std::cerr << "* Buffer Leftovers: *\n" << _buffer_leftovers << '\n';
}