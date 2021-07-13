#ifndef WEBSERV_DELETEMETHOD_H
# define WEBSERV_DELETEMETHOD_H

# include "IHttpMethod.hpp"

class DeleteMethod : public IHttpMethod
{
	public:

    	DeleteMethod(void);
    	DeleteMethod(DeleteMethod const & src);
    	~DeleteMethod(void);

		DeleteMethod &  operator=(DeleteMethod const & src);

		void				handle(void);
		bool				has_body(void);
		static IHttpMethod	*create_s(void);
		IHttpMethod			*create_v(void);
};

#endif
