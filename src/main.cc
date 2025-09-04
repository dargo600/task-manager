/**
 * Copyright 2025 David Turgeon
 * Use of this source code is goverened by a MIT-style license that can be
 * found in the LICENSE file.
 */
#include "api/listener.h"

#include <iostream>

// namespace beast = boost::beast;
// namespace http = beast::http;
using Listener = api::Listener;
namespace net = boost::asio;
using tcp = net::ip::tcp;

int main()
{
    auto const address = net::ip::make_address("0.0.0.0");
    unsigned short port = 8080;

    net::io_context ioc{1};
    auto listener = std::make_shared<Listener>(ioc, tcp::endpoint{address, port});
    ioc.run();
}