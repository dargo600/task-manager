/**
 * Copyright 2025 David Turgeon
 * Use of this source code is governed by a MIT-style license that can be
 * found in the LICENSE file.
 */

#include "handler.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace api
{
    namespace
    {
        namespace beast = boost::beast;
        namespace http = beast::http;
        namespace net = boost::asio;
    }

    Handler::Handler(http::status status, unsigned version, IMarkDownParser &parser)
        : status_(status), version_(version), md_parser_(parser)
    {
        allowed_paths_ = {"/data/", "/api/tasks/"};
    }

    /**
     * Determines if the incoming HTTP request is valid based on allowed paths.
        * @param[in] req The incoming HTTP request.
        * @return True if the request is valid, false otherwise.
        */
    bool Handler::is_valid_request(const http::request<http::string_body> &req) const
    {
        for (const auto &path : allowed_paths_)
        {
            if (req.target().rfind(path, 0) == 0)
            {
                return true;
            }
        }

        return false;
    }

    void Handler::generate_html_file(const std::string &filename, std::string &html_content)
    {
        std::size_t pos = filename.find(".html");
        if (pos != std::string::npos) {
            std::string md_file = filename.substr(0, pos) + ".md";
            if (std::filesystem::exists(md_file))
            {
                md_parser_.create_html(md_file, filename, html_content);
            }
        }
    }

    /**
    * Generates an HTML response by initially checking to see if an HTML file
        * exists.  If it does not then it checks to see if the corresponding
        * markdown file exists and converts it to HTML.
        * @param[in] filename The name of the HTML file to retrieve or generate.
        * @return The HTML content as a string.
        */
    void Handler::get_html_response(const std::string &filename, std::string &html_content)
    {
        if (std::filesystem::exists(filename)) {
            std::ifstream ifs(filename);
            std::stringstream buffer;
            buffer << ifs.rdbuf();
            html_content = buffer.str();
        } else {
            generate_html_file(filename, html_content);
        }
        if (html_content.empty()) {
            html_content = "<html><head><title>Not Found</title></head><body><p>Error Locating html page.</p></body></html>";
        }
    }

    /**
     * Generates an HTTP response based on the incoming request.
        * @param[in] req The incoming HTTP request.
        * @return The generated HTTP response.
        */
    http::response<http::string_body> Handler::generate_response(const http::request<http::string_body> &req)
    {
        std::stringstream buffer;
        std::string filename = req.target();
        std::string html_content;
        const std::string api_prefix = "/data/";

        if (filename.rfind(api_prefix, 0) == 0) {
            filename = "res/" + filename.substr(api_prefix.length());
        }
        get_html_response(filename, html_content);
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, "Beast");
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = html_content;
        res.prepare_payload();
        return res;
    }

}
