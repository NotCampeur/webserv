#ifndef STATUSCODES_H
# define STATUSCODES_H

# include "webserv.hpp"

class StatusCodes
{
	public:

		typedef enum status_index_e {
			CONTINUE_100,
			SWITCHING_PROTOCOLS_101,
			OK_200,
			CREATED_201,
			ACCEPTED_202,
			NON_AUTHORITATIVE_INFORMATION_203,
			NO_CONTENT_204,
			RESET_CONTENT_205,
			PARTIAL_CONTENT_206,
			MULTIPLE_CHOICES_300,
			MOVED_PERMANENTLY_301,
			FOUND_302,
			SEE_OTHER_303,
			NOT_MODIFIED_304,
			USE_PROXY_305,
			TEMPORARY_REDIRECT_307,
			BAD_REQUEST_400,
			UNAUTHORIZED_401,
			PAYMENT_REQUIRED_402,
			FORBIDDEN_403,
			NOT_FOUND_404,
			METHOD_NOT_ALLOWED_405,
			NOT_ACCEPTABLE_406,
			PROXY_AUTHENTICATION_REQUIRED_407,
			REQUEST_timer_408,
			CONFLICT_409,
			GONE_410,
			LENGTH_REQUIRED_411,
			PRECONDITION_FAILED_412,
			REQUEST_ENTITY_TOO_LARGE_413,
			REQUEST_URI_TOO_LONG_414,
			UNSUPPORTED_MEDIA_TYPE_415,
			REQUESTED_RANGE_NOT_SATISFIABLE_416,
			EXPECTATION_FAILED_417,
			INTERNAL_SERVER_ERROR_500,
			NOT_IMPLEMENTED_501,
			BAD_GATEWAY_502,
			SERVICE_UNAVAILABLE_503,
			GATEWAY_timer_504,
			HTTP_VERSION_NOT_SUPPORTE_505
		} status_index_t;

    	StatusCodes(void);
    	StatusCodes(StatusCodes const & src);
    	~StatusCodes(void);
		
		StatusCodes &  operator=(StatusCodes const & src);

		static int				get_code_value(status_index_t index);
		static std::string &	get_error_msg_from_index(status_index_t index);
		// Consider removing if not used
		static std::string &	get_error_msg_from_value(int value);
};

#endif
