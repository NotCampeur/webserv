#ifndef WEBSERV_GETMETHOD_H
# define WEBSERV_GETMETHOD_H

# include "IHttpMethod.hpp"

class DeleteMethod : public IHttpMethod
{
	public:

    	DeleteMethod(void);
    	~DeleteMethod(void);

		virtual void	handle(void);

	private:
    	DeleteMethod(DeleteMethod const & src);
		DeleteMethod &  operator=(DeleteMethod const & src);

};

#endif
