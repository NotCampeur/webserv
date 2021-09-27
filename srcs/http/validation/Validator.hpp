#ifndef VALIDATOR_H
# define VALIDATOR_H

# include <string>
# include "Singleton.hpp"
# include "webserv.hpp"
# include "RequestConfig.hpp"
class Request;
class Response;
class ServerConfig;
class RouteConfig;

class Validator : public Singleton<Validator>
{
	public:
		Validator(void);
    	~Validator(void);

		void	validate_request_inputs(Request & req, Response & resp);

	private:
		Validator(Validator const & src);
		Validator &  operator=(Validator const & src);

		void	set_request_config(Request & req, std::string & path);
		void	is_method_allowed(Request & req);
		void	set_full_path(Request & req, Response & resp, std::string & path);
		void	verify_path(Request & req, Response & resp);
		bool	is_dir(mode_t mode);
		bool	is_file(mode_t mode);
		void	parse_hexa(std::string & path);
		std::string	resolve_relative_path(std::string & path);
		void	remove_last_path_elem(std::string & path);

		//Takes the path after relative resolution has been performed, and returns the associated Location config, or NULL if none is found
		const LocationConfig & find_location_config(Request & req, std::string & path);
		bool	file_accessible(const std::string & path);
};

#endif