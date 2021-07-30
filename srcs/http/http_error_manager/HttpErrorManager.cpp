#include "HttpErrorManager.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "InitiationDispatcher.hpp"
#include "HttpException.hpp"

HttpErrorManager::HttpErrorManager(const ServerConfig & config, Response & resp) :
_fd(-1),
_config(config),
_resp(resp)
{}

HttpErrorManager::HttpErrorManager(HttpErrorManager const & src) :
_fd(src._fd),
_config(src._config),
_resp(src._resp)
{}

HttpErrorManager::~HttpErrorManager(void)
{}

void
HttpErrorManager::handle(StatusCodes::status_index_t error)
{
	_resp.set_http_code(error);
	const std::string * path = _config.get_error_page_path(StatusCodes::get_code_value(error));
	
	if (path != NULL)
	{
		std::cerr << "Error page found: " << *path << '\n';
		_resp.set_path(*path);
		_fd = open(_resp.get_path().c_str(), O_RDONLY);
		if (_fd >= 0)
		{
			try {
					off_t file_size = get_file_size(*path);
					set_content_length_header(file_size);
					set_content_type_header();
					_resp.ready_to_send() = false;
					_resp.complete() = false;
					_resp.set_handler_fd(_fd);
					InitiationDispatcher::get_instance().add_read_handle(file_size, _resp);
					return ;
			}
			catch (SystemException & e)
			{
				Logger(LOG_FILE, error_type, error_lvl) << e.what();
			}
		}
	}
	std::cerr << "Error page not found...\n";
	set_default_msg(error);
}

void
HttpErrorManager::set_default_msg(StatusCodes::status_index_t error)
{
	_resp.ready_to_send() = true;
	_resp.complete() = true;

	_resp.set_http_code(error);


	std::stringstream ss; 
	ss << set_payload_to_default_msg(error);
	
	_resp.add_header("Content-Length", ss.str().c_str());
	_resp.add_header("Content-Type", "text/html");
}

size_t
HttpErrorManager::set_payload_to_default_msg(StatusCodes::status_index_t error)
{
	static std::string err_msg_part_1("<html>\n<head><title>");
	static std::string err_msg_part_2("</title></head>\n<body bgcolor=\"white\">\n<center><h1>");
	static std::string err_msg_part_3("</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>");
	
	std::string full_msg = err_msg_part_1 + StatusCodes::get_code_msg_from_index(error) + err_msg_part_2 + StatusCodes::get_code_msg_from_index(error) + err_msg_part_3;
	_resp.set_payload(full_msg);
	
	return full_msg.size();
}

off_t
HttpErrorManager::get_file_size(const std::string & path)
{
	struct stat stat_buf;

	int ret = stat(path.c_str(), &stat_buf);
	if (ret != 0)
	{
		throw SystemException("Error on stat call");
	}

	return stat_buf.st_size;
}

void
HttpErrorManager::set_content_length_header(off_t len)
{
	std::stringstream ss;
	ss << len;
	_resp.add_header("Content-Length", ss.str());
}

void
HttpErrorManager::set_content_type_header(void)
{
	const std::string & path = _resp.get_path();
	int i = path.size() - 1;
	for(; i >= 0; i--)
	{
		if (path[i] == '.')
			break;
	}
	if (i >= 0)
	{
		std::string file_ext = path.substr(i);
		const std::string * mime_ext = Mime::get_content_type(file_ext);
		if (mime_ext != NULL)
			_resp.add_header("Content-Type", *mime_ext);
	}
}