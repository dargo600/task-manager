/**
 * Copyright 2025 David Turgeon
 * Use of this source code is governed by a MIT-style license that can be
 * found in the LICENSE file.
 */
#ifndef API_HANDLER_H
#define API_HANDLER_H

#include <string>
#include <boost/beast/http.hpp>

#include "imarkdown_parser.h"

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
        Handler(const http::status status, const unsigned version, IMarkDownParser &parser);
        ~Handler() = default;

        // Item 11 Effective Modern C++: Disable copy and assignment
        Handler(const Handler &) = delete;
        Handler &operator=(const Handler &) = delete;
        
        bool is_valid_request(const http::request<http::string_body> &req) const;
        http::response<http::string_body> generate_response(const http::request<http::string_body> &req);

    private:
        void generate_html_file(const std::string &filename, std::string &html_content);
        void get_html_response_contents(const std::string &filename, std::string &html_content);
        http::status status_;
        unsigned version_;
        std::vector<std::string> allowed_paths_;
        IMarkDownParser &md_parser_;
    };
}

#endif
