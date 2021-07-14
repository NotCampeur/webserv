#ifndef WEBSERV_DELETEMETHOD_H
# define WEBSERV_DELETEMETHOD_H

# include "IHttpMethod.hpp"
# include "webserv.hpp"
# include "ClientSYSException.hpp"

class DeleteMethod : public IHttpMethod
{
	private:
		std::string	_path = "tst/hihi";

	public:

    	DeleteMethod(void);
    	DeleteMethod(DeleteMethod const & src);
    	~DeleteMethod(void);

		DeleteMethod &  operator=(DeleteMethod const & src);

		StatusCodes::status_index_t	handle(void);
		bool						has_body(void);
		static IHttpMethod			*create_s(void);
		IHttpMethod					*create_v(void);

		void						set_path(const std::string & path);
};

#endif
