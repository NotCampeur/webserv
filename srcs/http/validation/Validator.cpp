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
	try
	{
		std::string path = resolve_relative_path(req.uri().path);
		set_request_config(req, path);
		set_full_path(req, resp, path);
		is_method_allowed(req);
		verify_path(req, resp);
	}
	catch (HttpException & e)
	{
		throw (e);
	}
}

void
Validator::set_request_config(Request & req, std::string & path)
{
	const ServerConfig & serv_conf = req.server_config();
	const LocationConfig & loc_conf = find_location_config(req, path);
	req.set_config(new RequestConfig(serv_conf, loc_conf));
	Logger(basic_type, debug_lvl) << "Server Config Set, location found : " << loc_conf.path();
}

void
Validator::is_method_allowed(Request & req)
{
	HTTPMethod method = req.get_config()->accepted_method();
	if (dynamic_cast<GetMethod *>(&req.method()) != NULL)
		if ((GET & method) != 0)
			return ;
	if (dynamic_cast<HeadMethod *>(&req.method()) != NULL)
		if ((HEAD & method) != 0)
			return ;
	if (dynamic_cast<PostMethod *>(&req.method()) != NULL)
		if ((POST & method) != 0)
			return ;
	if (dynamic_cast<DeleteMethod *>(&req.method()) != NULL)
		if ((DELETE & method) != 0)
			return ;
	throw (HttpException(StatusCodes::METHOD_NOT_ALLOWED_405));
}

void
Validator::set_full_path(Request & req, Response & resp, std::string & path)
{
	std::string root = req.get_config()->root();
	if (*path.begin() == '/')
	{
		path.erase(path.begin()); // Remove as we don't want it if we're dealing with a relative path
	}
	if (root.empty() == false)
	{
		if (*(root.end() - 1) != '/')
			path.insert(path.begin(), '/');
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
	// std::cerr << "CGI EXT:\n";
	// std::map<std::string, std::string>::iterator it = req.get_config()->cgi().begin();
	// for (; it != req.get_config()->cgi().end() ; ++it)
	// {
	// 	std::cerr << "Address: " << &it->first << " value: " << it->first << '\n';
	// }
	// std::cerr << "Req ext: " << Utils::get_file_ext(resp.get_path()) << '\n';
	// it = req.get_config()->cgi().find(Utils::get_file_ext(resp.get_path()));
	// std::cerr << "Find: " << &it->first << " : " << it->first << '\n';
	if (req.get_config()->cgi().find(Utils::get_file_ext(resp.get_path())) !=
		req.get_config()->cgi().end())
	{
		std::cerr << "Cgi needed\n";
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

std::string
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
					throw HttpException(StatusCodes::BAD_REQUEST_400);
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
	return resolved_path;
}

void
Validator::remove_last_path_elem(std::string & path)
{
	
	std::string::reverse_iterator rit = path.rbegin();
	for (; rit != path.rend(); rit++)
	{
		if (*rit == '/')
		{
			if (rit == path.rbegin()) //Trailing slash
			{
				continue ;
			}
			else
			{
				path.erase(rit.base(), path.end());
				return ;
			}
		}
	}
	path.clear();
}

const LocationConfig &
Validator::find_location_config(Request & req, std::string & path)
{
	std::string req_path = path;
	const std::vector<LocationConfig *> & server_locations = req.server_config().locations();//		server_conf->locations(); //Consider using public typedef inside RouteConfig
	while (!path.empty())
	{
		for (size_t i = 0; i < server_locations.size(); i++)
		{
			if (server_locations[i]->path() == req_path)
			{
				return *server_locations[i];
				// *server_conf = *server_routes[i];
			}
		}
		remove_last_path_elem(req_path);
	}
	throw HttpException(StatusCodes::NOT_FOUND_404);
}