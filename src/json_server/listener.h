#pragma once

#include <boost/beast/version.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <memory>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

http::response<http::string_body> handle_request(http::request<http::string_body> const &req);

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

class Listener : public std::enable_shared_from_this<Listener>
{
    net::io_context &ioc_;
    tcp::acceptor acceptor_;

public:
    Listener(net::io_context &ioc, tcp::endpoint endpoint);

private:
    void do_accept();
};