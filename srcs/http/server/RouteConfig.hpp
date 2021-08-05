#ifndef WEBSERV_ROUTE_CONFIG_HPP
# define WEBSERV_ROUTE_CONFIG_HPP

# include <string>

class RouteConfig
{
    private:
        std::string _path;
        std::string _accepted_method;
        std::string _redirection;
        std::string _root;
        bool        _auto_index;
        std::string _default_file_dir;
        //For the moment the cgi will be stored as a string.
        std::string cgi;
        std::string _upload_path;

    public:
        RouteConfig(std::string path);
        RouteConfig(const RouteConfig & to_copy);
        ~RouteConfig();

        RouteConfig & operator=(const RouteConfig & to_assign);
};

#endif
