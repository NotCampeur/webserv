#include "CgiParser.hpp"
#include "HttpException.hpp"
#include "Utils.hpp"

CgiParser::CgiParser(Response & resp) :
_resp(resp),
_request_state(HEADERS)
{}

CgiParser::~CgiParser(void) {}

void
CgiParser::parse(char * buf, size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		char c = buf[i];
		switch (_request_state)
		{
			case HEADERS :
			{
				if (c == '\r')
					break ; //According to CGI doc, new line (NL) should only be \n (no \r), but apparently some CGI's use \r\n as NL
				
				if (c == '\n' && _header_parser.get_header_name().empty()) // There are no more headers, move to Final NL
				{
					try {
							set_resp_params();
					}
					catch (const HttpException & e)
					{
						throw e;
					}
					break ;
				}
				else
				{
					try {
						if (_header_parser.parse_char(c))
						{
							add_header();
						}
						break ;
					}
					catch(const HttpException & e)
					{
						throw e;
					}
				}
			}
			case BODY :
			{
				_resp.set_payload(&buf[i], len - i);
				_resp.ready_to_send() = true;
				return ;
			}
			default :
			{
				Logger(error_type, error_lvl) << "Request parser - unusual event (400 sent to client)";
				return ;
			}
		}
	}
}

void
CgiParser::add_header(void)
{
	std::pair<std::string, std::string> p(_header_parser.get_header_name(), _header_parser.get_header_value());
	if (p.first == "set-cookie")
	{
			_cookies.push_back(p.second);
	}
	else
	{
		_headers.insert(p);
	}
	_header_parser.reset();
}

void
CgiParser::reset(void)
{
	_request_state = HEADERS;
	_headers.clear();
	_cookies.clear();
	_header_parser.reset();
}

// Assume all header names are lowercase (responsibility of HeaderParser)
void
CgiParser::set_resp_params(void)
{
	if (_headers.find("content-type") == _headers.end())
	{
		Logger(error_type, error_lvl) << "Missing 'content-type' header in cgi response";
		throw HttpException(StatusCodes::INTERNAL_SERVER_ERROR_500);
	}

	if (_headers.find("status") == _headers.end())
	{
		_resp.set_http_code(StatusCodes::OK_200);
		_headers.erase("status");
	}
	else
	{
		std::string status = _headers.find("status")->second;
		_headers.erase("status");
		long int status_code = std::strtol(status.c_str(), NULL, 10);
		Logger(error_type, error_lvl) << "Cgi status code: " << status;
		
		
		if (status_code != 200)
		{
			Logger(error_type, error_lvl) << "CGI status code: " << status_code;
			if (status_code == 100) //Ignoring 100 responses
			{
				reset();
				return ;
			}
			if (Utils::is_redirect(status_code))
			{
				handle_cgi_redirect(status_code);
				_resp.ready_to_send() = true;
				_resp.complete() = true;
				return ;
			}
			throw HttpException(StatusCodes::INTERNAL_SERVER_ERROR_500);
		}
		else
		{
			_resp.set_http_code(StatusCodes::OK_200);
		}
	}

	if (_headers.find("content-length") == _headers.end())
	{
		_resp.send_chunks();
	}
	add_all_cgi_headers();
	_request_state = BODY;
}

void
CgiParser::handle_cgi_redirect(long int code)
{
	if (_headers.find("location") != _headers.end())
	{
		_resp.set_http_code(StatusCodes::get_code_index_from_value(code));
		add_all_cgi_headers();
	}
	else
	{
		throw HttpException(StatusCodes::INTERNAL_SERVER_ERROR_500);
	}
}

void
CgiParser::add_all_cgi_headers(void)
{	
	for (str_map::iterator it = _headers.begin(); it != _headers.end(); ++it)
	{
		_resp.add_header(it->first, it->second);
	}
	for (size_t i = 0; i < _cookies.size(); ++i)
	{
		_resp.add_header("Set-Cookie", _cookies[i]);
	}
}