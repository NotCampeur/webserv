#include "RequestParser.hpp"

RequestParser::RequestParser(void) :
{
    reset();
}

// RequestParser::RequestParser(RequestParser const & src) :
// _request(src._request),
// _offset(src._offset)
// {}

RequestParser::~RequestParser(void) {}

RequestParser &
RequestParser::operator=(RequestParser const & src)
{
    return (*this);
}

void
RequestParser::parse(void)
{
    while (_offset < _buffer.size())
    {
		char c = _buffer[_offset];

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
					request_error(500); // Request nb TBC
				}
				break ;
			}
            case HEADERS :
            {
				if (c == '\r')
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
				}
				else
				{
					request_error(400); // Code TBC
				}
				break ;
			}
			case FINAL_CRLF :
			{
				if (c == '\n')
					_request_state = DONE;
				else
				{
					request_error(400); // Req nb TBC
				}
			}
        }
        if (_request_state == DONE) // Could set request to Complete here
            return ;
		_offset++;
    }
}

void
RequestParser::reset(void)
{
    _buffer.empty();
    _request = nullptr;
    _offset = 0;
    _request_state = METHOD;
    _http_method.empty();
	_http_version.empty();
    _uri_parser.reset();
	_header_parser.reset();
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
                _request->setmethod(static_cast<Request::http_method>(i));
                _request_state = URI;
				return ;
            }
        }
        request_error(500); // Error code TBC
    }
	else
	{
        _http_method += c;
		if (_http_method.size() > 6)
		{
			request_error(500);
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
			request_error(505);
			return ;
		}
	}
	else
	{
		_http_version += c;
		if (_http_version.size() > correct_version.size())
		{
			request_error(500); // Error code TBC
		}
	}
}

void
RequestParser::request_error(int code)
{
    _request_state = DONE;
    (void)code;
}
