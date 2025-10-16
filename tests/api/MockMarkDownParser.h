#ifndef MOCKMARKDOWNPARSER_H
#define MOCKMARKDOWNPARSER_H

#include "imarkdown_parser.h"
#include <gmock/gmock.h>

namespace api {
    class MockMarkDownParser : public IMarkDownParser {
    public:
        MOCK_METHOD(std::string, md_to_html, (const std::string &md_filename, const std::string &html_filename), (override));
    };
}

#endif // MOCKMARKDOWNPARSER_H