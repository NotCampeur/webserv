#ifndef WEBSERV_POSTMETHOD_H
# define WEBSERV_POSTMETHOD_H

# include "IHttpMethod.hpp"
# include "Singleton.hpp"
# include "webserv.hpp"

class PostMethod : public IHttpMethod, public Singleton<PostMethod>
{
	public:
		PostMethod(void);
    	~PostMethod(void);

		void					handle(Request & req, Response & resp);
		bool					has_body(void);
		
		private:
			PostMethod(PostMethod const & src);
			PostMethod &  operator=(PostMethod const & src);
			
			void	add_cgi_handle(Request & req, Response & resp);
};

#endif
