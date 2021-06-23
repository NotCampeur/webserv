#include "RequestParser.hpp"

RequestParser::RequestParser(void) :
_raw(),
_httpmethod(), // Not sure if I need to do this
_uri()
{
    reset();
}

// RequestParser::RequestParser(RequestParser const & src) :
// _request(src._request),
// _offset(src._offset)
// {}

RequestParser::~RequestParser(void) {}

RequestParser &
RequestParser::operator=(RequestParser const & src)
{
    return (*this);
}

void
RequestParser::parse(void)
{
    switch (_state)
    {
        case METHOD :
        {
            parse_method();
        } 
        case URI :
        {
            parse_uri();
        }
        case VERSION :
        {
            check_version();
        }
        case HEADERS :
        {
            break ;
        }
        
        default :
            std::cerr << "Error: request parser should not get to default method\n";
    }
}

void
RequestParser::reset(void)
{
    _raw.empty();
    _request = nullptr;
    _offset = _raw.begin();
    _state = METHOD;
    _httpmethod.empty();
    _uri.empty();
}

void
RequestParser::parse_method()
{

    static std::string available_methods[] = {
        "GET",
        "POST",
        "DELETE"
    };
    static size_t method_count = 3;

    while (_offset != _raw.end() && *_offset != ' ') // Computing "size" and "raw.end()"" every time could be a waste
    {
        _httpmethod += *_offset;
        if (_httpmethod.size() > 6)
        {
            std::cerr << "Error 500: Not implemented\n"; // Set response object with error code 
        }
        _offset++;
    }

    if (*_offset == ' ')
    {
        for (size_t i = 0; i < method_count; i++)
        {
            if (available_methods[i] == _httpmethod)
            {
                _request->setmethod(static_cast<Request::http_method>(i));
                _state = URI;
                _offset++;
                return ;
            }
        }
        std::cerr << "Error! Wrong method\n"; // Set response object with error code
    }
}

void
RequestParser::parse_uri()
{

    while (_offset != _raw.end() && *_offset != ' ') // Computing "size" and "raw.end()"" every time could be a waste
    {
        _uri += *_offset;
        _offset++;
    }

    if (_uri.size() > MAX_REQUEST_SIZE)
        std::cerr << "Error! Request too long\n"; // Set response object with error code
    if (_offset == _raw.end())
        return ; // Will only parse the uri once it is complete

    std::string uri_path;
    std::string::iterator uri_it = _uri.begin();
    std::string::iterator uri_ite = _uri.end();

    while (uri_it != uri_ite && *uri_it != '?' && *uri_it != '#')
    {
        uri_path += *uri_it;
    }

    if (uri_it != uri_ite)
    {
        switch (*uri_it)
        {
            case '?' :
            {
                std::string uri_query;

                uri_it++;
                while (uri_it != uri_ite && *uri_it != '#')
                {
                    uri_query += *uri_it;
                }
                _request->seturi_query(uri_query);
                if (uri_it == uri_ite)
                    break ;
            }
            case '#' :
            {
                std::string uri_fragment;

                uri_it++;
                while (uri_it != uri_ite && *uri_it != '#')
                {
                    uri_fragment += *uri_it;
                }
                _request->seturi_fragment(uri_fragment);  
            }
        }
    }
    _request->seturi_path(uri_path);
    _state = VERSION;
    _offset++;
}

void
RequestParser::check_version(void)
{
    static std::string correct_version("HTTP/1.1");

    std::string http_version;

    while (_offset != _raw.end())
    {
        if (*_offset == '\r')
        {
            _offset++;
            if (*_offset == '\n')
            {
                _offset++;
                break ;
            }
        }
        
        http_version += *_offset;

        if (http_version.size() > correct_version.size())
        {
            std::cerr << "505: version not supported\n";
        }
    }
    
    if (_offset == _raw.end()) // Haven't read enough yet to compare
        return ;
    
    if (http_version == correct_version)
    {
        _state = HEADERS;
        return ;
    }
    else
    {
        std::cerr << "505: version not supported\n";
    }
}