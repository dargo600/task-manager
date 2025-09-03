/**
 * Copyright 2025 David Turgeon
 * Use of this source code is goverened by a MIT-style license that can be
 * found in the LICENSE file.
 */

#ifndef SESSION_H
#define SESSION_H

#include <sys/socket.h>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
    tcp::socket socket_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;

public:
    explicit Session(tcp::socket socket);
    void run();

private:
    void do_read();
    void do_write(http::response<http::string_body> res);
};

#endif