#include "RequestBodyParser.hpp"

RequestBodyParser::RequestBodyParser(Request & req) :
_state(START),
_request(req)
{}

RequestBodyParser::RequestBodyParser(RequestBodyParser const & src) :
_state(src._state),
_size(src._size),
_request(src._request),
_hex(src._hex)
{}

RequestBodyParser::~RequestBodyParser(void) {}

bool
RequestBodyParser::parse_char(char c)
{
	std::cerr << "In body parser\n";
	switch (_state)
	{
		case START :
		{
			// if (_request.headers().find("transfer-encoding") != _request.headers().end())
			// {
			// 	if (_request.headers().find("transfer-encoding")->second == std::string("chunked"))
			// 		_state = CHUNK_SIZE;
			// }
			// else
			if (_request.headers().find("content-length") != _request.headers().end())
			{
				_state = CONTENT_LEN;
				_size = std::strtoul(_request.headers().find("content-length")->second.c_str(), NULL, 10);
				if (_size > MAX_CLIENT_BODY_SIZE || _size == ULONG_MAX)
				{
					throw HttpException(HttpException::REQUEST_ENTITY_TOO_LARGE_413);
				}
				else if (_size == 0)
				{
					throw HttpException(HttpException::BAD_REQUEST_400);
				}
			}
			else
			{std::cerr << "Throwing 411\n";
				throw HttpException(HttpException::LENGTH_REQUIRED_411);}
			break;
		}
		case CONTENT_LEN :
		{
			_request.add_char_to_body(c);
			if (_request.bodysize() == _size)
				return true;
			break ;
		}
	}
	return false;
}

void
RequestBodyParser::reset(void)
{
	_state = START;
	_size = 0;
	_hex.clear();
}