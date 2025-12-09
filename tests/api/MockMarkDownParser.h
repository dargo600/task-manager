#ifndef MOCKMARKDOWNPARSER_H
#define MOCKMARKDOWNPARSER_H

#include "imarkdown_parser.h"
#include <gmock/gmock.h>

namespace api {
    class MockMarkDownParser : public IMarkDownParser {
    public:
        MOCK_METHOD(void, create_html, (const std::string &md_filename, const std::string &html_filename, std::string &html_content), (override));
    };
}

#endif // MOCKMARKDOWNPARSER_H