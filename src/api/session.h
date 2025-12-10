/**
 * Copyright 2025 David Turgeon
 * Use of this source code is governed by a MIT-style license that can be
 * found in the LICENSE file.
 */

#ifndef API_SESSION_H
#define API_SESSION_H

#include <sys/socket.h>

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

namespace api {
namespace {
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;
}  // namespace

class Session : public std::enable_shared_from_this<Session> {
   public:
    Session(tcp::socket socket);
    ~Session() = default;

    // Item 11 Effective Modern C++: Disable copy and assignment
    Session(const Session &) = delete;
    Session &operator=(const Session &) = delete;

    void run();

   private:
    void do_read();
    void do_write(http::response<http::string_body> res);
    tcp::socket socket_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;
};
}  // namespace api

#endif