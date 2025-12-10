/**
 * Copyright 2025 David Turgeon
 * Use of this source code is governed by a MIT-style license that can be
 * found in the LICENSE file.
 */
#ifndef API_LISTENER_H
#define API_LISTENER_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <memory>

namespace api {
namespace {
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;
}  // namespace
class Listener : public std::enable_shared_from_this<Listener> {
   public:
    Listener(net::io_context &ioc, tcp::endpoint endpoint);
    ~Listener() = default;

    // Item 11 Effective Modern C++: Disable copy and assignment
    Listener(const Listener &) = delete;
    Listener &operator=(const Listener &) = delete;

   private:
    void do_accept();
    net::io_context &ioc_;
    tcp::acceptor acceptor_;
};
}  // namespace api

#endif
