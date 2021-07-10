#ifndef WEBSERV_POSTMETHOD_H
# define WEBSERV_POSTMETHOD_H

# include "IHttpMethod.hpp"

class PostMethod : public IHttpMethod
{
	public:
    	PostMethod(void);
    	~PostMethod(void);

		void		handle(void);
		bool		has_body(void);
		static IHttpMethod	*create(void);

	private:
    	PostMethod(PostMethod const & src);
		PostMethod &  operator=(PostMethod const & src);
};

#endif
