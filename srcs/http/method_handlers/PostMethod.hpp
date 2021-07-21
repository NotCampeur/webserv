#ifndef WEBSERV_POSTMETHOD_H
# define WEBSERV_POSTMETHOD_H

# include "IHttpMethod.hpp"
# include "Singleton.hpp"

class PostMethod : public IHttpMethod, public Singleton<PostMethod>
{
	public:
		PostMethod(void);
    	~PostMethod(void);

		void					handle(Request & req, Response & resp);
		bool					has_body(void);
		// static IHttpMethod		*create_s(void);
		// IHttpMethod				*create_v(void);
		
		private:
			PostMethod(PostMethod const & src);
			PostMethod &  operator=(PostMethod const & src);
};

#endif
