#include "handler.h"
#include <iostream>
#include <fstream>
#include <sstream>

Handler::Handler(http::status status, unsigned version)
    : status_(status), version_(version)
{
    allowed_paths_ = {"/data/", "/api/tasks/"};
}

Handler::~Handler() = default;

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
std::string Handler::md_to_html(const std::string &tmp_md) const
{
    std::string html;
    // Write markdown to a temporary file
    std::string tmp_html = "/tmp/tmp_html_file.html";
    {
        std::ofstream ofs(tmp_md);
        ofs << md_content;
    }
    // Run pandoc to convert markdown to HTML
    std::string cmd = "pandoc " + tmp_md + " -f markdown -t html -o " + tmp_html;
    int ret = std::system(cmd.c_str());
    if (ret == 0)
    {
        std::ifstream ifs(tmp_html);
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        html = buffer.str();
    }
    else
    {
        html = "<p>Error converting markdown to HTML.</p>";
    }
    // Optionally, remove temp files
    std::remove(tmp_md.c_str());
    std::remove(tmp_html.c_str());
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

    if (std::filesystems::exists(filename))
    {
        buffer << md_to_html(filename);
    }
    else
    {
        buffer << "# 404 Not Found\nThe requested resource was not found.";
    }
    std::string html_content = buffer.str();

    http::response<http::string_body> res{status_, version_};
    res.set(http::field::server, "Beast");
    res.set(http::field::content_type, "text/html");
    res.keep_alive(req.keep_alive());
    res.body() = html_content;
    res.prepare_payload();
    std::cout << "Sent response: " << res.body() << std::endl;
    return res;
}