#ifndef WEBSERV_DELETEMETHOD_H
# define WEBSERV_DELETEMETHOD_H

# include "IHttpMethod.hpp"
# include "webserv.hpp"
# include "ClientSystemException.hpp"
# include "Singleton.hpp"

class DeleteMethod : public IHttpMethod, public Singleton<DeleteMethod>
{
	public:
    	DeleteMethod(void);
    	~DeleteMethod(void);
		void				handle(Request & req, Response & resp);
		bool				has_body(void);

		private:
			DeleteMethod(DeleteMethod const & src);
			DeleteMethod &  operator=(DeleteMethod const & src);
<<<<<<< HEAD

			void	add_cgi_handle(Request & req, Response & resp);

=======
>>>>>>> main
};

#endif
