#include "api_handler.h"
#include <fstream>
#include <sstream>

ApiHandler::ApiHandler(http::status status, unsigned version)
    : status_(status), version_(version)
{
}

ApiHandler::~ApiHandler() = default;

http::response<http::string_body> ApiHandler::generate_response(const http::request<http::string_body> const &req)
{
    std::string filename = req.target();
    std::ifstream file(filename);
    std::stringstream buffer;
    if (file)
    {
        buffer << file.rdbuf();
    }
    else
    {
        buffer << "# 404 Not Found\nThe requested resource was not found.";
    }
    std::string md_content = buffer.str();

    http::response<http::string_body> res{status_, version_};
    res.set(http::field::server, "Beast");
    res.set(http::field::content_type, "text/markdown");
    res.keep_alive(req.keep_alive());
    res.body() = md_content;
    res.prepare_payload();

    return res;
}