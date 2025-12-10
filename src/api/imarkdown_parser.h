/**
 * Copyright 2025 David Turgeon
 * Use of this source code is governed by a MIT-style license that can be
 * found in the LICENSE file.
 */
#ifndef API_IMARKDOWN_PARSER_H
#define API_IMARKDOWN_PARSER_H

#include <string>

#include "non_copyable.h"

namespace api {
class IMarkDownParser : public NonCopyable {
   public:
    virtual ~IMarkDownParser() = default;
    // this object is cheap so we allow default copy and assignment
    // IMarkDownParser(const IMarkDownParser &) = delete;
    // IMarkDownParser &operator=(const IMarkDownParser &) = delete;
    virtual void create_html(const std::string &md_filename,
                             const std::string &html_filename,
                             std::string &html_content) = 0;
};
}  // namespace api

#endif
