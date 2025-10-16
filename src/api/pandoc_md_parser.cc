/**
 * Copyright 2025 David Turgeon
 * Use of this source code is governed by a MIT-style license that can be
 * found in the LICENSE file.
 */

#include "pandoc_md_parser.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace api
{
    // Helper function to convert markdown to HTML using pandoc
    std::string PandocMdParser::md_to_html(const std::string &md_filename, const std::string &html_filename)
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
}
