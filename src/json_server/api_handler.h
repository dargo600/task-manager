
#include <boost/beast/http.hpp>

namespace beast = boost::beast;
namespace http = beast::http;

class ApiHandler
{
public:
    ApiHandler(http::status status, unsigned version);
    ~ApiHandler();
    bool is_valid_request(const http::request<http::string_body> &req) const;
    http::response<http::string_body> generate_response(const http::request<http::string_body> &req) const;

private:
    http::status status_;
    unsigned version_;
    std::vector<std::string> allowed_api_paths_;
};
