/**
 * Copyright 2025 David Turgeon
 * Use of this source code is goverened by a MIT-style license that can be
 * found in the LICENSE file.
 */

#include "session.h"
#include "handler.h"

#include <nlohmann/json.hpp>

http::response<http::string_body> handle_request(http::request<http::string_body> const &req)
{
    Handler api{http::status::ok, req.version()};
    if (req.method() == http::verb::get && api.is_valid_request(req))
    {
        if (req.target() == "/api/tasks")
        {
            nlohmann::json json_response = {{"message", "Still a GET request for tasks"}};
            http::response<http::string_body> res{http::status::ok, req.version()};
            res.set(http::field::server, "Beast");
            res.set(http::field::content_type, "application/json");
            res.keep_alive(req.keep_alive());
            res.body() = json_response.dump();
            res.prepare_payload();
            return res;
        }
        else
        {
            return api.generate_response(req);
        }
    }
    else if (req.method() == http::verb::post && req.target() == "/api/tasks")
    {
        auto json_request = nlohmann::json::parse(req.body());
        std::string response_message = "Received: " + json_request.dump();
        nlohmann::json json_response = {{"message", response_message}};
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, "Beast");
        res.set(http::field::content_type, "application/json");
        res.keep_alive(req.keep_alive());
        res.body() = json_response.dump();
        res.prepare_payload();
        return res;
    }
    else if (req.method() == http::verb::put && req.target() == "/api/tasks")
    {
        auto json_request = nlohmann::json::parse(req.body());
        std::string response_message = "Updated: " + json_request.dump();
        nlohmann::json json_response = {{"message", response_message}};
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, "Beast");
        res.set(http::field::content_type, "application/json");
        res.keep_alive(req.keep_alive());
        res.body() = json_response.dump();
        res.prepare_payload();
        return res;
    }
    else if (req.method() == http::verb::delete_ && req.target() == "/api/tasks")
    {
        nlohmann::json json_response = {{"message", "Resource deleted"}};
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, "Beast");
        res.set(http::field::content_type, "application/json");
        res.keep_alive(req.keep_alive());
        res.body() = json_response.dump();
        res.prepare_payload();
        return res;
    }

    return http::response<http::string_body>{http::status::bad_request, req.version()};
}

// Session implementation
Session::Session(tcp::socket socket) : socket_(std::move(socket))
{
}

void Session::run()
{
    do_read();
}

void Session::do_read()
{
    auto self(shared_from_this());
    http::async_read(socket_, buffer_, req_, [this, self](beast::error_code ec, std::size_t)
                     {
                         if (!ec) {
                             do_write(handle_request(req_));
                         } });
}

void Session::do_write(http::response<http::string_body> res)
{
    auto self(shared_from_this());
    auto sp = std::make_shared<http::response<http::string_body>>(std::move(res));
    http::async_write(socket_, *sp, [this, self, sp](beast::error_code ec, std::size_t)
                      { socket_.shutdown(tcp::socket::shutdown_send, ec); });
}