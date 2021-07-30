#ifndef WEBSERV_GETMETHOD_H
# define WEBSERV_GETMETHOD_H

# include "IHttpMethod.hpp"
# include "SystemException.hpp"
# include "Singleton.hpp"

class GetMethod : public IHttpMethod, public Singleton<GetMethod>
{
	public:
		GetMethod(void);
    	~GetMethod(void);

		
		void				handle(Request & req, Response & resp);
		bool				has_body(void);
		// static IHttpMethod	*create_s(void);
		// IHttpMethod			*create_v(void);

	private:
    	GetMethod(GetMethod const & src);
		GetMethod &  operator=(GetMethod const & src);

		void	set_content_length_header(Response & resp);
		void	set_content_type_header(Response & resp);
		// void	set_content_location_header(Response & resp);
		off_t	get_file_size(const std::string & path);
};

#endif
