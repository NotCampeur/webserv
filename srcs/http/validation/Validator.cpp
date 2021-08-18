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

// Assumes that "root" from config is terminated with a '/'
void
Validator::set_full_path(Request & req, Response & resp)
{
	std::string path = req.uri().path;
	path.erase(path.begin()); // remove '/'
	resolve_relative_path(path);

	std::string root = req.get_server_config().get_root_dir();
	
	if (!root.empty())
	{
		path.insert(0, root);
	}
	parse_hexa(path);
	resp.set_path(path);
	std::cerr << "Final path: " << path << '\n';
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

void
Validator::resolve_relative_path(std::string & path)
{
	std::string resolved_path;

	std::string fragment;
	for (size_t i = 0; i < path.size(); i++)
	{
		fragment += path[i];
		if ((path[i] == '/') || (i == path.size() - 1))
		{
			if ((fragment == "./") || (fragment == "."))
			{
				fragment.clear();
				continue ;
			}
			else if ((fragment == "../") || (fragment == ".."))
			{
				std::cerr << "Found ..: " << fragment << '\n';
				if (resolved_path.empty())
				{
					throw (HttpException(StatusCodes::BAD_REQUEST_400));
				}
				else
				{
					remove_last_path_elem(resolved_path);
				}
			}
			else
			{
				resolved_path += fragment;
			}
			fragment.clear();
		}
	}
	path = resolved_path;
}

// Assumes that the path passed as argument contain a trailing '/' due to semantics of path "fragments"
void
Validator::remove_last_path_elem(std::string & path)
{
	int i = static_cast<int>(path.size()) - 1;	// Cast is safe as URI size is limited and should never exceed max_int
	i--; // Don't start on last '/'

	std::cerr << "Path received: " << path << " ; Size: " << path.size() << '\n';
	for (; i >= 0; i--)
	{
		if (path[i] == '/')
		{
			std::cerr << "Path \\ index: " << i << '\n';
			path.erase(i, path.size() - i - 1);
			return ;
		}
	}
	path.clear();
}