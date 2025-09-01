#include "api_handler.h"
#include <iostream>
#include <fstream>
#include <sstream>

ApiHandler::ApiHandler(http::status status, unsigned version)
    : status_(status), version_(version)
{
    allowed_api_paths_ = {"/api/recipes/", "/api/tasks/"};
}

ApiHandler::~ApiHandler() = default;

bool ApiHandler::is_valid_request(const http::request<http::string_body> &req) const
{
    for (const auto &path : allowed_api_paths_)
    {
        if (req.target().rfind(path, 0) == 0)
        {
            return true;
        }
    }

    return false;
}

http::response<http::string_body> ApiHandler::generate_response(const http::request<http::string_body> &req) const
{
    std::stringstream buffer;
    std::string filename = req.target();
    const std::string api_prefix = "/api/recipes/";

    if (filename.rfind(api_prefix, 0) == 0)
    {
        filename = "res/" + filename.substr(api_prefix.length());
    }

    std::ifstream file(filename);
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
    std::cout << "Sent response: " << res.body() << std::endl;
    return res;
}