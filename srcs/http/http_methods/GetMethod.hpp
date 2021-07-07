#ifndef WEBSERV_GETMETHOD_H
# define WEBSERV_GETMETHOD_H

# include "IHttpMethod.hpp"

class GetMethod : public IHttpMethod
{
	public:

    	GetMethod(void);
    	~GetMethod(void);

		virtual void		handle(void);
		virtual bool		has_body(void);
		static IHttpMethod	*create(void);
	private:
    	GetMethod(GetMethod const & src);
		GetMethod &  operator=(GetMethod const & src);

};

#endif
