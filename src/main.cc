/**
 * Copyright 2025 David Turgeon
 * Use of this source code is governed by a MIT-style license that can be
 * found in the LICENSE file.
 */
#include <syslog.h>
#include <unistd.h>

#include <iostream>

#include "api/handler.h"
#include "api/listener.h"
#include "non_copyable.h"

using Listener = api::Listener;
namespace net = boost::asio;
using tcp = net::ip::tcp;

int main() {
    auto const address = net::ip::make_address("0.0.0.0");
    unsigned short port = 8080;
/**
FIXME remove test code as this is expected to not compile
*/
#if 0
    api::Handler test1;
    api::Handler test2 = test1; // should fail to compile
    std::cout << "Confirming test2 does not compile: " << &test2 << std::endl;
#endif

    setlogmask(LOG_UPTO(LOG_DEBUG));
    openlog("task-mgr", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL0);
    syslog(LOG_INFO, "Starting task-mgr server...");
    net::io_context ioc{1};
    auto listener =
        std::make_shared<Listener>(ioc, tcp::endpoint{address, port});
    ioc.run();
    syslog(LOG_INFO, "Stopping task-mgr server...");
    closelog();
    return 0;
}
