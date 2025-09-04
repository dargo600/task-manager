/**
 * Copyright 2025 David Turgeon
 * Use of this source code is goverened by a MIT-style license that can be
 * found in the LICENSE file.
 */
#ifndef API_HANDLER_H
#define API_HANDLER_H

#include <boost/beast/http.hpp>

namespace api
{
    namespace
    {
        namespace beast = boost::beast;
        namespace http = beast::http;
    }
    class Handler
    {
    public:
        Handler(http::status status, unsigned version);
        ~Handler() = default;

        // Item 11 Effective Modern C++: Disable copy and assignment
        Handler(const Handler &) = delete;
        Handler &operator=(const Handler &) = delete;

        bool is_valid_request(const http::request<http::string_body> &req) const;
        std::string md_to_html(const std::string &md_filename, const std::string &html_filename) const;

        http::response<http::string_body> generate_response(const http::request<http::string_body> &req) const;

    private:
        http::status status_;
        unsigned version_;
        std::vector<std::string> allowed_paths_;
    };
}

#endif