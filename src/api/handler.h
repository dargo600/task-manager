#ifndef API_HANDLER_H
#define API_HANDLER_H

#include <boost/beast/http.hpp>

namespace beast = boost::beast;
namespace http = beast::http;

class Handler
{
public:
    Handler(http::status status, unsigned version);
    ~Handler();
    bool is_valid_request(const http::request<http::string_body> &req) const;
    std::string md_to_html(const std::string &md_content) const;
    http::response<http::string_body> generate_response(const http::request<http::string_body> &req) const;

private:
    http::status status_;
    unsigned version_;
    std::vector<std::string> allowed_paths_;
};

#endif