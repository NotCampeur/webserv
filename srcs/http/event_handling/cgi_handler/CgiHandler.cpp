#include "CgiHandler.hpp"
#include "InitiationDispatcher.hpp"

CgiHandler::CgiHandler(const Request & req, Response & resp) :
_request(req),
_response(resp),
_event_flag(POLLIN)
{
	// Needs CGI path!!
	set_environment();
}

CgiHandler::~CgiHandler(void)
{}



void 
CgiHandler::readable(void)
{}

void
CgiHandler::writable(void)
{}

bool
CgiHandler::is_timeoutable(void) const
{
	return false;
}

bool
CgiHandler::is_timeout(void) const
{
	return false;
}

int
CgiHandler::get_event_flag(void) const
{
	return _event_flag;
}

void
CgiHandler::set_environment(void)
{
	// Content Lenght
	if _request.bodu
}


// void
// CgiHandler::manage_error(void)
// {
// 	if (!_response.metadata_sent())
// 		_response.http_error(StatusCodes::INTERNAL_SERVER_ERROR_500);
// }

// void
// CgiHandler::response_complete(void)
// {
// 	_response.ready_to_send() = true;
// 	_response.complete() = true;
// }
