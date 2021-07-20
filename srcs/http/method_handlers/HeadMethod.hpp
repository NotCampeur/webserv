#ifndef WEBSERV_HEADMETHOD_H
# define WEBSERV_HEADMETHOD_H

# include "IHttpMethod.hpp"

class HeadMethod : public IHttpMethod
{
	public:
    	HeadMethod(void);
    	~HeadMethod(void);
    	HeadMethod(HeadMethod const & src);
		
		HeadMethod &  		operator=(HeadMethod const & src);

		void				handle(Request & req, Response & resp, InitiationDispatcher & idis);
		bool				has_body(void);
		static IHttpMethod	*create_s(void);
		IHttpMethod			*create_v(void);

	private:
		void				set_content_length_header(const std::string & path, Response & resp);
		off_t				get_file_size(const std::string & path);
};

#endif
