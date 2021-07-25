#include "Validator.hpp"
#include "HttpException.hpp"
#include "Request.hpp"
#include "Response.hpp"

Validator::Validator(void) {}

Validator::Validator(Validator const & src)
{
    (void)src;
}

Validator::~Validator(void) {}

Validator &
Validator::operator=(Validator const & src)
{
    return (*this);
}

void
Validator::validate_request(Request & req, Response & resp)
{
	try {
		is_method_allowed();
	}
	catch (HttpException & e)
	{
		resp.http_error(e.get_error_index());
	}
}

void
Validator::is_method_allowed()
{
	return ;
}

void
Validator::set_full_path(Request & req, Response & resp)
{
	std::string path = req.uri().path;
	std::string root = req.get_server_config().get_root_dir();

	if (root.empty())
	{
		// char * workdir = getcwd(NULL, 0);
		// path.insert(0, workdir);
		// free(workdir);
		path.erase(path.begin()); // Relative path
	}
	else
	{
		path.insert(0, root);
	}

	resp.set_path(path);

}

bool is_dir(const std::string & path)
{

}

/*
	Request_parser:
		- Max client body size

	Validator:
		- Server blocks
		- Allowed methods
		- Root -> set full path
		- Autoindex: if path leads to a directory:
			if ON, do nothing
			if OFF:
				if default file provided:
					- set file path to this default path
				else: 404

	Method handlers:
		- Verify file path (for Post, file does not need to exist)
		- Nothing (if file is a directory, generate autoindex, as error cases have been delt with in validator)

	Response:
		- Need to know error files location
*/