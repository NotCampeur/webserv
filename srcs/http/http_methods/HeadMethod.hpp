#ifndef WEBSERV_HEADMETHOD_H
# define WEBSERV_HEADMETHOD_H

# include "IHttpMethod.hpp"

class HeadMethod : public IHttpMethod
{
	public:

    	HeadMethod(void);
    	~HeadMethod(void);

		virtual void	handle(void);

	private:
    	HeadMethod(HeadMethod const & src);
		HeadMethod &  operator=(HeadMethod const & src);

};

#endif
