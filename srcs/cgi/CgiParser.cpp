#include "CgiParser.hpp"
#include "HttpException.hpp"

CgiParser::CgiParser(Response & resp) :
_resp(resp),
_request_state(HEADERS)
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
	for (size_t i = 0; i < _buffer.size(); i++)
	{
		char c = _buffer[i];

		switch (_request_state)
		{
			case HEADERS :
			{
				if (c == '\n' && _header_parser.get_header_name().empty()) // There are no more headers, move to Final NL
				{
					_request_state = FINAL_NL;
					break ;
				}
				if (_header_parser.parse_char(c))
				{
					add_header();
				}
				break ;
			}
			case FINAL_NL :
			{
				if (!set_resp_params())
				{
					return ;
				}
				else
				{
					_request_state = BODY;
				}
			}
			case BODY :
			{
				if (i > 0)
				{
					std::vector<char>::iterator it = _buffer.begin();
					_buffer.erase(it, it + i);
				}
			}
			default :
			{
				Logger(LOG_FILE, error_type, error_lvl) << "Request parser - unusual event (400 sent to client)";
				break;
			}
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
	}
	_buffer.clear();
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
	_request_state = HEADERS;
	_header_parser.reset();
}

// Assumes all header names are lowercase (responsibility of HeaderParser)
// Returns true if the response has a body, false otherwise
bool
CgiParser::set_resp_params(void)
{
	if (_headers.find("content-type") == _headers.end())
	{
		_resp.http_error(StatusCodes::INTERNAL_SERVER_ERROR_500); // But most likely that's a CGI error..
		Logger(LOG_FILE, error_type, error_lvl) << "Missing 'content-type' header in cgi response";
		return false;
	}
	else
	{
		_resp.add_header("Content-Type", _headers.find("content-type")->second);
		_headers.erase("content-type");
	}

	if (_headers.find("status") == _headers.end())
	{
		_resp.set_http_code(StatusCodes::OK_200);
		_headers.erase("status");
	}
	else
	{
		std::string status = _headers.find("status")->second;
		long int status_code = std::strtol(status.c_str(), NULL, 10);
		
		if (status_code != 200)
		{
			Logger(LOG_FILE, error_type, error_lvl) << "Cgi status code: " << status;
			_resp.http_error(StatusCodes::INTERNAL_SERVER_ERROR_500);
			return false;
		}
		_resp.set_http_code(StatusCodes::OK_200);
		_headers.erase("status");
	}
	//Add protocol specific headers that might have been returned by the cgi
	for (str_map::iterator it = _headers.begin(); it != _headers.end(); it++)
	{
		_resp.add_header(it->first, it->second);
	}
	if (_headers.find("content-length") != _headers.end())
	{

	}
	return true;
}