#ifndef VALIDATOR_H
# define VALIDATOR_H

# include <string>
# include "Singleton.hpp"
# include "webserv.hpp"
# include "ValidatorConfig.hpp"
class Request;
class Response;
class ServerConfig;

// Check if method is allowed
// Verify uri and set file path: 
//	- (Not yet implemented): chose appropriate server block
//	- Add root from server config file
//	- Verify if file exists (if not and method is not POST, throw error)
//	- If path leads to a directory, check if autoindex is on or if a default file is provided (e.g. index.html)

class Validator : public Singleton<Validator>
{
	public:
		Validator(void);
    	~Validator(void);

		void	validate_request_inputs(Request & req, Response & resp);

	private:
		Validator(Validator const & src);
		Validator &  operator=(Validator const & src);

		void	load_desired_config(Request & req);
		void	is_method_allowed(Request & req);
		void	set_full_path(Request & req, Response & resp);
		void	verify_path(Request & req, Response & resp);
		bool	is_dir(mode_t mode);
		bool	is_file(mode_t mode);
		void	parse_hexa(std::string & path);
		void	resolve_relative_path(std::string & path);
		void	remove_last_path_elem(std::string & path);
};

#endif

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