/**
 * Copyright 2025 David Turgeon
 * Use of this source code is governed by a MIT-style license that can be
 * found in the LICENSE file.
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "pandoc_md_parser.h"

namespace api
{

    PandocMdParser& PandocMdParser::getInstance(void)
    {
        static PandocMdParser instance;

        return instance;
    }

    /**
    * Converts a Markdown file to HTML using Pandoc.
    * @param[in] md_filename The name of the Markdown file to convert.
    * @param[in] html_filename The name of the output HTML file.
    * @param[out] html_content The generated HTML content otherwise html_content is
    *                           left uninitialized.
    */
    void PandocMdParser::create_html(const std::string &md_filename, const std::string &html_filename, std::string &html_content)
    {
        // Run pandoc to convert markdown to HTML
        std::cout << "PandocMdParser parsing " << reinterpret_cast<std::uintptr_t>(this);
        std::string cmd = "pandoc " + md_filename + " -f markdown -t html -o " + html_filename;
        int ret = std::system(cmd.c_str());
        if (ret == 0) {
            std::ifstream ifs(html_filename);
            std::stringstream buffer;
            buffer << ifs.rdbuf();
            html_content = buffer.str();
        } else {
            std::cout << "Failed to create html file using pandoc." << std::endl;
        }
    }

    PandocMdParser::PandocMdParser()
    {
        std::cout << "Address in PandocMdParser " + std::to_string(reinterpret_cast<std::uintptr_t>(this));
    }
}
