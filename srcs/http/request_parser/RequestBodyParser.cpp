#include "RequestBodyParser.hpp"

RequestBodyParser::RequestBodyParser(Request & req) :
_state(START),
_request(req),
_last_chunk(false)
{}

RequestBodyParser::RequestBodyParser(RequestBodyParser const & src) :
_state(src._state),
_size(src._size),
_request(src._request),
_hex(src._hex),
_last_chunk(false)
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
			if (_request.headers().find("transfer-encoding") != _request.headers().end())
			{
				if (_request.headers().find("transfer-encoding")->second == std::string("chunked"))
				{
					_state = CHUNK_SIZE;
				}
				else
				{
					throw HttpException(HttpException::NOT_ACCEPTABLE_406);
				}
			}
			else if (_request.headers().find("content-length") != _request.headers().end())
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
			{
				throw HttpException(HttpException::LENGTH_REQUIRED_411);
			}
			break;
		}
		case CONTENT_LEN :
		{
			_request.add_char_to_body(c);
			if (_request.bodysize() == _size)
			{
				return true;
			}
			break ;
		}
		case CHUNK_SIZE :
		{
			if (c == '\r')
			{
				_size = std::strtoul(_hex.c_str(), NULL, 16);
				if (_size > MAX_CLIENT_BODY_SIZE || _size == ULONG_MAX)
				{
					throw HttpException(HttpException::REQUEST_ENTITY_TOO_LARGE_413);
				}
				if (_size == 0)
					_last_chunk = true;
				_state = CHUNK_META_CRLF;
			}
			else
			{
				_hex += std::toupper(c);
			}
			break ;
		}
		case CHUNK_META_CRLF :
		{
			if (c == '\n')
			{
				_state = CHUNK_DATA;
			}
			else
			{
				throw HttpException(HttpException::BAD_REQUEST_400);
			}
		}
		case CHUNK_DATA :
		{
			if (_size == 0)
			{
				if (c == '\r')
				{
					_state = CHUNK_DATA_CRLF;
				}
				else
				{
					throw HttpException(HttpException::BAD_REQUEST_400);
				}
			}
			else
			{
				_request.add_char_to_body(c);
				_size--;
			}
			break ;
		}
		case CHUNK_DATA_CRLF :
		{
			if (c == '\n')
			{
				if (_last_chunk)
					return true;
				_state = CHUNK_SIZE;
			}
			else
			{
				throw HttpException(HttpException::BAD_REQUEST_400);
			}
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