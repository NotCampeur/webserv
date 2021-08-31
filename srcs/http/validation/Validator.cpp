#include "Validator.hpp"
#include "HttpException.hpp"
#include "SystemException.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "DeleteMethod.hpp"
#include "GetMethod.hpp"
#include "HeadMethod.hpp"
#include "PostMethod.hpp"
#include "Utils.hpp"

Validator::Validator(void) {}

Validator::~Validator(void) {}

void
Validator::validate_request_inputs(Request & req, Response & resp)
{
	try {
		host_header_ok(req);
		load_desired_config(req);
		set_full_path(req, resp);
		is_method_allowed(req);
		verify_path(req, resp);
	}
	catch (HttpException & e)
	{
		throw (e);
	}
}

void
Validator::host_header_ok(Request & req)
{
	if (req.headers().find("host") == req.headers().end())
	{
		throw HttpException(StatusCodes::BAD_REQUEST_400);
	}
}

void
Validator::load_desired_config(Request & req)
{
	ValidatorConfig &					config = ValidatorConfig::get_instance();
	const std::vector<RouteConfig *>	routes = req.get_server_config().routes();

	for (std::vector<RouteConfig *>::const_iterator it = routes.begin();
			it != routes.end(); ++it)
	{
		if ((*it)->path() == req.uri().path)
		{
			config = *(*it);
			Logger(LOG_FILE, basic_type, debug_lvl) << "Route Config loaded";
			return ;
		}
	}
	Logger(LOG_FILE, basic_type, debug_lvl) << "Server Config loaded";
	config = req.get_server_config().begin()->second;
}

void
Validator::is_method_allowed(Request & req)
{
	RouteMethod method = ValidatorConfig::get_instance().accepted_method();
	if (dynamic_cast<GetMethod *>(&req.method()) != NULL)
	{
		if ((GET & method) != NOTHING)
			return ;
	}
	if (dynamic_cast<HeadMethod *>(&req.method()) != NULL)
		if (HEAD & method)
			return ;
	if (dynamic_cast<PostMethod *>(&req.method()) != NULL)
		if ((POST & method) != 0)
			return ;
	if (dynamic_cast<DeleteMethod *>(&req.method()) != NULL)
		if ((DELETE & method) != 0)
			return ;
	throw (HttpException(StatusCodes::METHOD_NOT_ALLOWED_405));
}

// Assumes that "root" from config is terminated with a '/'
void
Validator::set_full_path(Request & req, Response & resp)
{
	std::string path = req.uri().path;
	path.erase(path.begin()); // remove '/'
	resolve_relative_path(path);
	std::string root = ValidatorConfig::get_instance().root_dir();
	
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
	std::cerr << Utils::get_file_ext(resp.get_path()) << '\n';
	if (req.get_server_config().get_cgi_path(Utils::get_file_ext(resp.get_path())))
	{
		resp.need_cgi() = true;
		return ;
	}

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