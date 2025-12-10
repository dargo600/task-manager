/**
 * Copyright 2025 David Turgeon
 * Use of this source code is governed by a MIT-style license that can be
 * found in the LICENSE file.
 */
#ifndef API_PANDOC_MD_PARSER_H
#define API_PANDOC_MD_PARSER_H

#include <string>

#include "imarkdown_parser.h"

namespace api {
class PandocMdParser : public IMarkDownParser {
   public:
    static PandocMdParser &getInstance(void);
    void create_html(const std::string &md_filename,
                     const std::string &html_filename,
                     std::string &html_content) override;

   private:
    PandocMdParser();
};
}  // namespace api

#endif
