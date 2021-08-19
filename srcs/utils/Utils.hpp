#ifndef UTILS_H
# define UTILS_H

class string;

class Utils
{
	public:

    	Utils(void);
    	Utils(Utils const & src);
    	~Utils(void);
		
		Utils &  operator=(Utils const & src);

		static std::string	get_file_ext(const std::string & filename);

	private:

};

#endif
