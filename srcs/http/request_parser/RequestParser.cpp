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
        case METHOD:
        {
            parse_method();
            break ;
        }        
        case URI:
        {
            parse_uri();
            break ;
        }
        case HEADERS:
        
        default:
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

    while (_offset != _raw.end() && *_offset != ' ') // Computing "size" and "raw.end()"" every time could be a waste
    {
        _httpmethod += *_offset;
        if (_httpmethod.size() > 6)
        {
            std::cerr << "Error! Wrong method\n"; // Set response object with error code
        }
        _offset++;
    }

    if (*_offset == ' ')
    {
        for (int i = 0; i < HTTP_METHODS_COUNT; i++)
        {
            if (available_methods[i] == _httpmethod)
            {
                _request->setmethod(static_cast<Request::http_method>(i));
                _state = URI;
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

    std::string uri_path();
    std::string::iterator uri_it = _uri.begin();
    std::string::iterator uri_ite = _uri.end();

    while (uri_it != uri_ite && *uri_it != '?' && *uri_it != '#')
    {
        uri_path += *uri_it;
    }
}
