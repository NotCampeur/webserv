#include "RequestBodyParser.hpp"

RequestBodyParser::RequestBodyParser(Request & req) :
_state(START),
_request(req)
{}

RequestBodyParser::~RequestBodyParser(void) {}

bool
RequestBodyParser::parse_body(char *buf, size_t len)
{
	switch (_state)
	{
	case START :
	{
		if (_request.headers().find("content-length") != _request.headers().end())
		{
			_state = NORMAL;
			_size = std::strtol(_request.headers().find("content-length")->second.c_str(), NULL, 10);
			if (_size > MAX_CLIENT_BODY_SIZE || _size == LONG_MAX)
			{
				
			}
			if (_size > LONG_MAX || _size == LONG_MIN)
			{

			}
		}
		if (_request.headers().find("transfer-encoding") != _request.headers().end())
		{
			if (_request.headers().find("transfer-encoding")->second == std::string("chunked"))
				_state = CHUNK_SIZE;
		}
	}
		break;
	
	default:
		break;
	}

	if ((len + _request.bodysize()) <= _size)
	{
		try {
			_request.addbody(buf, len);
		}
		catch(std::exception & e)
		{
			throw e; // TBU
		}
	}
	else
	{
		throw Exception("Max client body size reached"); // TBU
	}
	if ((len + _request.bodysize()) == _size)
		return true;
	return false;
}

bool	parse_chunk(char *buf, size_t len);

bool
RequestBodyParser::parse_char(char c)
{
	switch (_state)
	{
	case START 
		break;
	
	default:
		break;
	}
}

