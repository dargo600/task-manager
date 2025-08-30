
#include <boost/beast/http.hpp>

namespace beast = boost::beast;
namespace http = beast::http;

class ApiHandler
{
public:
    ApiHandler(http::status status, unsigned version);
    ~ApiHandler();
    http::response<http::string_body> generate_response(const http::request<http::string_body> const &req);

private:
    http::status status_;
    unsigned version_;
};
