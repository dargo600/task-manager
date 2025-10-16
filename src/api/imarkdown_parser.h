/**
 * Copyright 2025 David Turgeon
 * Use of this source code is governed by a MIT-style license that can be
 * found in the LICENSE file.
 */
#ifndef API_IMARKDOWN_PARSER_H
#define API_IMARKDOWN_PARSER_H

#include <string>

namespace api
{
    class IMarkDownParser
    {
    public:
        virtual std::string md_to_html(const std::string &md_filename, const std::string &html_filename) = 0;
    };
}

#endif
