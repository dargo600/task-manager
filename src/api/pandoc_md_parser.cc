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
    /**
    * Converts a Markdown file to HTML using Pandoc.
    * @param[in] md_filename The name of the Markdown file to convert.
    * @param[in] html_filename The name of the output HTML file.
    * @param[out] html_content The generated HTML content.
    */
    void PandocMdParser::create_html(const std::string &md_filename, const std::string &html_filename, std::string &html_content)
    {
        // Run pandoc to convert markdown to HTML
        std::string cmd = "pandoc " + md_filename + " -f markdown -t html -o " + html_filename;
        int ret = std::system(cmd.c_str());
        if (ret == 0) {
            std::ifstream ifs(html_filename);
            std::stringstream buffer;
            buffer << ifs.rdbuf();
            html_content = buffer.str();
        } else {
            std::stringstream ss;
            ss << "<html><head><title>Error</title></head><body><p>Error Locating the HTML page.</p></body></html>";
            std::ofstream ofs(html_filename);
            html_content = ss.str();
            ofs << html_content;
        }
    }
}
