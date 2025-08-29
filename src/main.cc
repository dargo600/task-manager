#include <iostream>
#if 0
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#endif
#include "json_server/listener.h"

namespace net = boost::asio; // from <boost/asio.hpp>

int main()
{
    try
    {
        auto const address = net::ip::make_address("0.0.0.0");
        unsigned short port = 8080;

        net::io_context ioc{1};
        auto listener = std::make_shared<Listener>(ioc, tcp::endpoint{address, port});
        ioc.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}