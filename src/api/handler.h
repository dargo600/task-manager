/**
 * Copyright 2025 David Turgeon
 * Use of this source code is governed by a MIT-style license that can be
 * found in the LICENSE file.
 */
#ifndef API_HANDLER_H
#define API_HANDLER_H

#include <boost/beast/http.hpp>
#include <string>

#include "imarkdown_parser.h"
#include "non_copyable.h"

namespace api {
namespace {
namespace beast = boost::beast;
namespace http = beast::http;
}  // namespace

class Handler : public NonCopyable {
   public:
    Handler(const http::status status, const unsigned version,
            IMarkDownParser &parser);
    ~Handler() = default;
    // inherited from NonCopyable
    // Handler(const Handler &) = delete;
    // Handler &operator=(const Handler &) = delete;
    bool is_valid_request(const http::request<http::string_body> &req) const;
    http::response<http::string_body> generate_response(
        const http::request<http::string_body> &req);

   private:
    void generate_html_file(const std::string &filename,
                            std::string &html_content);
    void get_html_response_contents(const std::string &filename,
                                    std::string &html_content);
    http::status status_;
    unsigned version_;
    std::vector<std::string> allowed_paths_;
    IMarkDownParser &md_parser_;
};
}  // namespace api

#endif
