#include "StatusCodes.hpp"

StatusCodes::StatusCodes(void)
{}

StatusCodes::StatusCodes(StatusCodes const & src)
{
	(void)src;
}

StatusCodes::~StatusCodes()
{}

StatusCodes &
StatusCodes::operator=(StatusCodes const & src)
{
	(void)src;
	return (*this);
}

std::string &
StatusCodes::get_code_msg_from_index(status_index_t index)
{
	static std::string error_msg[] =
	{
		"100 Continue",
		"101 Switching Protocols",
		"200 OK",
		"201 Created",
		"202 Accepted",
		"203 Non-Authoritative Information",
		"204 No Content",
		"205 Reset Content",
		"206 Partial Content",
		"300 Multiple Choices",
		"301 Moved Permanently",
		"302 Found",
		"303 See Other",
		"304 Not Modified",
		"305 Use Proxy",
		"307 Temporary Redirect",
		"400 Bad Request",
		"401 Unauthorized",
		"402 Payment Required",
		"403 Forbidden",
		"404 Not Found",
		"405 Method Not Allowed",
		"406 Not Acceptable",
		"407 Proxy Authentication Required",
		"408 Request Timer",
		"409 Conflict",
		"410 Gone",
		"411 Length Required",
		"412 Precondition Failed",
		"413 Request Entity Too Large",
		"414 Request-URI Too Long",
		"415 Unsupported Media Type",
		"416 Requested Range Not Satisfiable",
		"417 Expectation Failed",
		"500 Internal Server Error",
		"501 Not Implemented",
		"502 Bad Gateway",
		"503 Service Unavailable",
		"504 Gateway Timer",
		"505 HTTP Version Not Supported"
	};
	return error_msg[index];
}

int			
StatusCodes::get_code_value(status_index_t index)
{
	static int values[] = {
		100,
		101,
		200,
		201,
		202,
		203,
		204,
		205,
		206,
		300,
		301,
		302,
		303,
		304,
		305,
		307,
		400,
		401,
		402,
		403,
		404,
		405,
		406,
		407,
		408,
		409,
		410,
		411,
		412,
		413,
		414,
		415,
		416,
		417,
		500,
		501,
		502,
		503,
		504,
		505
	};
	return values[index];
}

StatusCodes::status_index_t
StatusCodes::get_code_index_from_value(int val)
{
	for (int i = 0; i <= HTTP_VERSION_NOT_SUPPORTE_505; ++i)
	{
		if (get_code_value(static_cast<StatusCodes::status_index_t>(i)) == val)
		{
			return (static_cast<StatusCodes::status_index_t>(i));
		}
	}
	Logger(error_type, error_lvl) << "Unexpected value passed to function get_code_index_from_value(): value is not an http code: " << val << " : function returned default OK_200 value";
	return OK_200;
}