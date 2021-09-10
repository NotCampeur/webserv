#include "CgiParser.hpp"
#include "HttpException.hpp"

CgiParser::CgiParser(Response & resp) :
_resp(resp),
_request_state(HEADERS)
{}

CgiParser::~CgiParser(void) {}

void
CgiParser::parse(char * buf, size_t len)
{	
	// write(2, "Cgi read buf content:\n", 22);
	// write(2, buf, len);
	// write(2, "\n", 1);
	for (size_t i = 0; i < len; i++)
	{
		char c = buf[i];

		switch (_request_state)
		{
			case HEADERS :
			{
				if (c == '\n' && _header_parser.get_header_name().empty()) // There are no more headers, move to Final NL
				{
					_request_state = FINAL_NL;
					break ;
				}
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
			case FINAL_NL :
			{
				std::cerr << "\n### PARSED CGI REQUEST HEADERS###\n";
				for (std::map<std::string, std::string>::iterator it = _headers.begin(); it != _headers.end(); it++)
				{
					std::cerr << "Header name: " << (*it).first << '\t'
					<< "Header value: " << (*it).second << '\n';
				}
				try {
					set_resp_params();
					_request_state = BODY; //No break here --> we fall directly in case BODY
				}
				catch (const HttpException & e)
				{
					throw e;
				}
			}
			case BODY :
			{
				_resp.set_payload(&buf[i], len - i);
				// std::cerr << "Payload set with:\n" << std::string(&buf[i], len - i) << '\n';
				_resp.ready_to_send() = true;
				return ;
			}
			default :
			{
				Logger(LOG_FILE, error_type, error_lvl) << "Request parser - unusual event (400 sent to client)";
				return ;
			}
		}
	}
}

void
CgiParser::add_header(void)
{
	std::pair<std::string, std::string> p(_header_parser.get_header_name(), _header_parser.get_header_value());
	_headers.insert(p);
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
void
CgiParser::set_resp_params(void)
{
	if (_headers.find("content-type") == _headers.end())
	{
		// handle_error(StatusCodes::INTERNAL_SERVER_ERROR_500); // But most likely that's a CGI error..
		Logger(LOG_FILE, error_type, error_lvl) << "Missing 'content-type' header in cgi response";
		throw HttpException(StatusCodes::INTERNAL_SERVER_ERROR_500);
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
			throw HttpException(StatusCodes::INTERNAL_SERVER_ERROR_500);
		}
		_resp.set_http_code(StatusCodes::OK_200);
		_headers.erase("status");
	}

	if (_headers.find("content-length") != _headers.end())
	{
		_resp.add_header("Content-Length", _headers.find("content-length")->second);
		_headers.erase("content-length");	
	}
	else
	{
		_resp.send_chunks();
	}

	//Add protocol specific headers that might have been returned by the cgi
	for (str_map::iterator it = _headers.begin(); it != _headers.end(); it++)
	{
		_resp.add_header(it->first, it->second);
	}
}