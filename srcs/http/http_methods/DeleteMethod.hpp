#ifndef WEBSERV_DELETEMETHOD_H
# define WEBSERV_DELETEMETHOD_H

# include "IHttpMethod.hpp"

class DeleteMethod : public IHttpMethod
{
	public:

    	DeleteMethod(void);
    	~DeleteMethod(void);

		void		handle(void);
		bool		has_body(void);
		static IHttpMethod	*create(void);

	private:
    	DeleteMethod(DeleteMethod const & src);
		DeleteMethod &  operator=(DeleteMethod const & src);
};

#endif
