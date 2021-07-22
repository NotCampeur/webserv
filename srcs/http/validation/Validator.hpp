#ifndef VALIDATOR_H
# define VALIDATOR_H


// Validator -> Verify request inputs based on request server settings
// Set Http Error pages locations in response: on error, Http response adds a read handler for that location
// 		Not so sure about this yet: could maybe use Error Manager obj: validator would set Http error Pages locations there
// If something is wrong, throw HttpException
// Is method allowed?
// uri: is path ok?
// 	If yes: set location header, content-length (except for post), content-type (except for post)

class Validator
{
	public:
    	Validator(void);
    	Validator(Validator const & src);
    	~Validator(void);
		
		Validator &  operator=(Validator const & src);

	private:
};

#endif
