/**
 * Copyright 2025 David Turgeon
 * Use of this source code is governed by a MIT-style license that can be
 * found in the LICENSE file.
 */
#ifndef API_PANDOC_MD_PARSER_H
#define API_PANDOC_MD_PARSER_H

#include "imarkdown_parser.h"
#include <string>

namespace api
{
    class PandocMdParser : public IMarkDownParser
    {
    public:
        std::string md_to_html(const std::string &md_filename, const std::string &html_filename) override;
    };
}

#endif
