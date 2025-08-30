/**
 * Copyright 2025 David Turgeon
 * Use of this source code is goverened by a MIT-style license that can be
 * found in the LICENSE file.
 */
#ifndef LISTENER_H
#define LISTENER_H

#include <boost/beast/version.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <memory>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

http::response<http::string_body> handle_request(http::request<http::string_body> const &req);

class Listener : public std::enable_shared_from_this<Listener>
{
    net::io_context &ioc_;
    tcp::acceptor acceptor_;

public:
    Listener(net::io_context &ioc, tcp::endpoint endpoint);

private:
    void do_accept();
};

#endif