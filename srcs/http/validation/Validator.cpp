#include "Validator.hpp"
#include "HttpException.hpp"
#include "SystemException.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "PostMethod.hpp"

Validator::Validator(void) {}

Validator::~Validator(void) {}

void
Validator::validate_request_inputs(Request & req, Response & resp)
{
	try {
		is_method_allowed();
		set_full_path(req, resp);
		verify_path(req, resp);
	}
	catch (HttpException & e)
	{
		throw (e);
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
	parse_hexa(path);
	resp.set_path(path);
}

void
Validator::parse_hexa(std::string & path)
{
	for (size_t i = 0; i < path.size(); i++)
	{
		if (path[i] == '%')
		{
			if ((i + 3) > path.size())
			{
				throw (HttpException(StatusCodes::BAD_REQUEST_400));
			}
			else
			{
				char c = std::strtol(path.substr(i + 1, 2).c_str(), NULL, 16);
				path[i] = c;
				path.erase(i + 1, 2);
			}
		}
	}
}

void
Validator::verify_path(Request & req, Response & resp)
{
	/* ADDED HERE FOR NOW BUT COULD BE MOVED TO A MORE SUITABLE ROUTINE */
	if (resp.get_path().substr(resp.get_path().find(".")) == ".py")
	{
		resp.need_cgi() = true;
	}
	/* .PY FOR TESTING PURPOSES, WILL BE IN CONFIG FILE */

	struct stat buf; 
	int ret = stat(resp.get_path().c_str(), &buf);

	if (ret < 0)
	{
		switch (errno)
		{
			case EACCES :
			{
				throw (HttpException(StatusCodes::FORBIDDEN_403)); // Using 403 for debug purposes, for security, better to use 404
				break;
			}
			case ENOENT :
			{
				PostMethod *method = dynamic_cast<PostMethod *>(&req.method());
				if (method == NULL)
					throw (HttpException(StatusCodes::NOT_FOUND_404));
				break ;
			}
			case EIO :
			{
				std::cerr << "Stat error val: " << errno << '\n';
				throw (SystemException("Error on stat call"));
			}
			case EOVERFLOW :
			{
				std::cerr << "Stat error val: " << errno << '\n';
				throw (SystemException("Error on stat call"));
			}
			default :
			{
				throw (HttpException(StatusCodes::NOT_FOUND_404));
				break ;
			}
		}
	}
	else
	{ // Structure to be improved during further development
		if (is_dir(buf.st_mode))
		{
			resp.path_is_dir() = true;
		}
		else if (!is_file(buf.st_mode))
		{
			throw (HttpException(StatusCodes::NOT_FOUND_404));
		}
		else
		{
			resp.path_is_dir() = false;
		}
	}
}

bool
Validator::is_dir(mode_t mode)
{
	if ((S_IFMT & mode) == S_IFDIR)
	{
		return true;
	}
	return false;
}

bool
Validator::is_file(mode_t mode)
{
	if ((S_IFMT & mode) == S_IFREG)
	{
		return true;
	}
	return false;
}