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

    Handler::Handler(http::status status, unsigned version)
        : status_(status), version_(version)
    {
        allowed_paths_ = {"/data/", "/api/tasks/"};
    }

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

    // Helper function to convert markdown to HTML using pandoc
    std::string Handler::md_to_html(const std::string &md_filename, const std::string &html_filename) const
    {
        std::string html;
        // Run pandoc to convert markdown to HTML
        std::string cmd = "pandoc " + md_filename + " -f markdown -t html -o " + html_filename;
        int ret = std::system(cmd.c_str());
        if (ret == 0)
        {
            std::ifstream ifs(html_filename);
            std::stringstream buffer;
            buffer << ifs.rdbuf();
            html = buffer.str();
        }
        else
        {
            html = "<html><head><title>Error</title></head><body><p>Error Locating html page.</p></body></html>";
            std::ofstream ofs(html_filename);
            ofs << html;
        }
        return html;
    }

    http::response<http::string_body> Handler::generate_response(const http::request<http::string_body> &req) const
    {
        std::stringstream buffer;
        std::string filename = req.target();
        const std::string api_prefix = "/data/";

        if (filename.rfind(api_prefix, 0) == 0)
        {
            filename = "res/" + filename.substr(api_prefix.length());
        }

        std::string html_content;
        if (!std::filesystem::exists(filename))
        {
            int pos = filename.find(".html");
            if (pos != std::string::npos)
            {
                std::string md_file = filename.substr(0, pos) + ".md";
                buffer << md_to_html(md_file, filename);
                html_content = buffer.str();
            }
        }
        else
        {
            std::ifstream ifs(filename);
            std::stringstream buffer;
            buffer << ifs.rdbuf();
            html_content = buffer.str();
        }
        if (html_content.empty())
        {
            html_content = "<html><head><title>Not Found</title></head><body><p>The resource '" + std::string(req.target()) + "' was not found.</p></body></html>";
        }

        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, "Beast");
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = html_content;
        res.prepare_payload();
        return res;
    }

}