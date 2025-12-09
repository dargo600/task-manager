/**
 * Copyright 2025 David Turgeon
 * Use of this source code is governed by a MIT-style license that can be
 * found in the LICENSE file.
 */


#include "MockMarkDownParser.h"
 #include "handler.h"

#include <boost/beast/http.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <filesystem>
#include <fstream>

namespace http = boost::beast::http;
using namespace api;

class HandlerTest : public ::testing::Test
{
protected:
    std::string md_file = "res/test.md";
    std::string html_file = "res/test.html";

    void SetUp() override
    {
        mode_t mode = 0755;
        if (mkdir("res", mode) == 0) {
            std::cout << "Created directory: res" << std::endl;
        } else if (errno == EEXIST) {
            std::cout << "Directory already exists: res" << std::endl;
        } else {
            std::cerr << "Error creating directory: " << strerror(errno) << std::endl;
        }
        // Create a test markdown file
        std::ofstream("res/test.md") << "# Test Title\nThis is a test.";
    }
    void TearDown() override
    {
        std::remove("res/test.md");
    }
};

TEST_F(HandlerTest, GeneratesResponseForMarkdown)
{
    api::MockMarkDownParser mockParser;
    Handler handler(boost::beast::http::status::ok, 11, mockParser);
    const std::string md_filename = "res/test.md";
    const std::string html_filename = "res/test.html";
    const std::string get_html_filename = "/data/test.html";
    EXPECT_CALL(mockParser, create_html(md_filename, html_filename, ::testing::_))
        .WillOnce(::testing::Invoke([](const std::string& /*md*/, const std::string& /*html*/, std::string& out) {
            out = "<h1>Test Title</h1>\n<p>This is a test.</p>";
        }));

    int version = 11; // http version 1.1
    http::request<http::string_body> req{http::verb::get, get_html_filename, version};
    auto res = handler.generate_response(req);

    // Check that response is OK and contains HTML content
    EXPECT_EQ(res.result(), http::status::ok);
    EXPECT_EQ(res[http::field::content_type], "text/html");
    EXPECT_NE(res.body().find("<h1>Test Title</h1>"), std::string::npos);
    EXPECT_NE(res.body().find("<p>This is a test.</p>"), std::string::npos);
}

TEST_F(HandlerTest, HandlesMissingMarkdownFile)
{
    api::MockMarkDownParser mockParser;
    Handler handler(boost::beast::http::status::ok, 11, mockParser);
    const std::string md_filename = "res/test2.md";
    const std::string get_html_filename = "/data/test2.html";

    int version = 11; // http version 1.1
    http::request<http::string_body> req{http::verb::get, get_html_filename, version};
    auto res = handler.generate_response(req);

    // Check that response is OK and contains HTML content
    EXPECT_EQ(res.result(), http::status::not_found);
    EXPECT_EQ(res[http::field::content_type], "text/html");
    EXPECT_NE(res.body().find("Error Locating html page"), std::string::npos);
}

TEST_F(HandlerTest, HTMLReturnsNoData)
{
    api::MockMarkDownParser mockParser;
    Handler handler(boost::beast::http::status::ok, 11, mockParser);
    const std::string md_filename = "res/test2.md";
    const std::string html_filename = "res/test2.html";
    const std::string get_html_filename = "/data/test2.html";
    int version = 11; // http version 1.1
    http::request<http::string_body> req{http::verb::get, get_html_filename, version};
    auto res = handler.generate_response(req);

    // Check that HTML errors appropriately if it has no data
    EXPECT_EQ(res.result(), http::status::not_found);
    EXPECT_EQ(res[http::field::content_type], "text/html");
    EXPECT_NE(res.body().find("<title>Not Found</title>"), std::string::npos);
    EXPECT_NE(res.body().find("Error Locating html page"), std::string::npos);
}

