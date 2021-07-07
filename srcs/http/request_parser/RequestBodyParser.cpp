#include "RequestBodyParser.hpp"

RequestBodyParser::RequestBodyParser(Request & req) :
_state(CHUNK_SIZE),
_request(req)
{}

RequestBodyParser::~RequestBodyParser(void) {}

bool
RequestBodyParser::parse_body(char *buf, size_t len)
{
	if ((len + _request.bodysize()) <= _size)
	{
		try {
			_request.addbody(buf, len);
		}
		catch(std::exception)
		{
			throw EXCEPTION() // TBU
		}
		_request
	}
	else
	{
		throw EXCEPTION() // TBU
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

