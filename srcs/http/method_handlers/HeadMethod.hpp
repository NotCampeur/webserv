#ifndef WEBSERV_HEADMETHOD_H
# define WEBSERV_HEADMETHOD_H

# include "webserv.hpp"
# include "IHttpMethod.hpp"
# include "Singleton.hpp"

class HeadMethod : public IHttpMethod, public Singleton<HeadMethod>
{
	public:    	
		HeadMethod(void);
    	~HeadMethod(void);

		void				handle(Request & req, Response & resp);
		bool				has_body(void);
		// static IHttpMethod	*create_s(void);
		// IHttpMethod			*create_v(void);

	private:
    	HeadMethod(HeadMethod const & src);
		HeadMethod &  		operator=(HeadMethod const & src);

		void				set_content_length_header(const std::string & path, Response & resp);
		void				set_content_type_header(Response & resp);
		off_t				get_file_size(const std::string & path);
};

#endif
