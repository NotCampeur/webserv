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
	try {
		const LocationConfig & loc_conf = find_location_config(req, path);
		req.set_config(new RequestConfig(serv_conf, loc_conf));
		Logger(basic_type, debug_lvl) << "Server Config Set";
	}
	catch (const HttpException & e)
	{
		req.set_config(new RequestConfig(serv_conf, *req.server_config().locations()[0])); // Setting the first location block, but actually it won't matter which Location Block is set as there'll only be a lookup on error_pages
		throw (e);
	}
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

//Remplace first path section with "path" variable with "root"
void
Validator::set_full_path(Request & req, Response & resp, std::string & path)
{
	std::string root = req.get_config()->root();
	std::string full_path = path;

	full_path.erase(0, req.get_config()->location_path().size());

	bool root_missing_end_slash = (!root.empty() && *(root.end() - 1) != '/' && root != "/");
	bool path_missing_begin_slash = (!full_path.empty() && *full_path.begin() != '/');
	if (root_missing_end_slash && path_missing_begin_slash)
	{
		root += '/';
	}
	full_path.insert(0, root);

	parse_hexa(full_path);
	resp.set_path(full_path);
	std::cerr << "Final path: " << full_path << '\n';
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
	if (req.get_config()->redirection().first != 0)
	{
		throw HttpException(StatusCodes::get_code_index_from_value(req.get_config()->redirection().first), req.get_config()->redirection().second);
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
			}
		}
	}
	else
	{ // Structure to be improved during further development
		if (is_dir(buf.st_mode))
		{
			// bool missing_trailing_bkslash = resp.get_path()[resp.get_path().size() - 1] != '/';
			bool missing_trailing_bkslash = (!req.uri().path.empty() && (req.uri().path[req.uri().path.size() - 1] != '/') && (req.uri().path != "/"));
			if (missing_trailing_bkslash)
			{
				std::string redir_path(req.uri().path);
				redir_path += '/';
				throw (HttpException(StatusCodes::MOVED_PERMANENTLY_301, redir_path));
			}
			else if (!req.get_config()->default_file_dir().empty())
			{
				
				std::string file_path = resp.get_path();
				// if (missing_trailing_bkslash)
				// 	file_path += '/';
				
				file_path += req.get_config()->default_file_dir();
				
				if (file_accessible(file_path))
				{
					std::cerr << "Path set to default file dir: " << file_path << '\n';
					resp.set_path(file_path);
					// req.uri().path += req.get_config()->default_file_dir(); // TRYING SOMETHING (DELETE IF NOT WORKING)
				}
				else
				{
					resp.path_is_dir() = true;
				}
			}
			else
				resp.path_is_dir() = true;
		}
		else if (!is_file(buf.st_mode))
		{
			throw (HttpException(StatusCodes::NOT_FOUND_404));
		}
	}
	bool cgi_needed = (req.get_config()->cgi().find(Utils::get_file_ext(resp.get_path())) != req.get_config()->cgi().end());
	if (cgi_needed)
	{
		std::cerr << "Cgi needed\n";
		resp.need_cgi() = true;
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
	while (!req_path.empty())
	{
		for (size_t i = 0; i < server_locations.size(); i++)
		{
			if (server_locations[i]->path() == req_path)
			{
				Logger(basic_type, minor_lvl) << "Location found: " << server_locations[i]->path() << '\n';
				return *server_locations[i];
			}
			else if (req_path[req_path.size() - 1] != '/') //Handling of client path missing trailing '/'
			{
				if (server_locations[i]->path() == (req_path + '/'))
				{
					Logger(basic_type, minor_lvl) << "Location found: " << server_locations[i]->path() << '\n';
					return *server_locations[i];
					// throw HttpException(StatusCodes::MOVED_PERMANENTLY_301, server_locations[i]->path());
				}
			}
		}
		remove_last_path_elem(req_path);
	}
	throw HttpException(StatusCodes::NOT_FOUND_404);
}

bool
Validator::file_accessible(const std::string & path)
{
	struct stat buf; 
	int ret = stat(path.c_str(), &buf);

	if (ret < 0)
	{
		return false;
	}
	if (is_file(buf.st_mode))
	{
		return true;
	}
	return false;
}

/*
	REDIRECTIONS HANDLING:

	1 - Directory redirections (when missing trailing '/'
		Need something clean, somthing that could be set or unset.. actually not, just redir to uri() + '/'
	2 - Config redirections: when the config provides a redirection
		Can only be done after LocationConfig is set, but should be done before checking if file exists
	3 - Cgi redirections: 
		Handle like 200: set status code and headers (use CGI output headers): how do I know if there's a body??? Cgi could return redir with body --> check status code, not all redir include body

*/