#ifndef VALIDATOR_H
# define VALIDATOR_H


// If something is wrong, throw HttpException
// Is method allowed?
// uri: is path ok? Select appropriate ressource based on server settings

// Method allowed? -> 405
// File Exists? -> 404
// Location is a directory? Default file is set for directory? -> set path || -> 404
// Set full file path

// Response needs to have access to error_pages

# include <string>
# include <map>
class Request;
class Response;
class ServerConfig;

class Validator
{
	public:
		Validator(void);
    	Validator(Validator const & src);
    	~Validator(void);
		
		Validator &  operator=(Validator const & src);

		void	validate_request(Request & req, Response & resp);

	private:
		void	is_method_allowed();
		void	set_full_path(Request & req, Response & resp);
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