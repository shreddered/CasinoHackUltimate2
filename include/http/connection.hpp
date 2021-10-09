#ifndef INCLUDE_HTTP_CONNECTION_HPP_
#define INCLUDE_HTTP_CONNECTION_HPP_

#include "http/http.hpp"

#include <string>

namespace http {

using tcp = net::ip::tcp;

class Connection {
public:
    Connection(net::io_context& ioc, ssl::context& ctx);
    void open(const std::string& host, const std::string& port);
    http::response<http::dynamic_body> send(const http::request<http::string_body>& request);
    virtual ~Connection() noexcept;
private:
    beast::ssl_stream<beast::tcp_stream> m_stream;
    beast::flat_buffer m_buf;
    tcp::resolver m_resolver;
}; // class Connection

} // namespace http

#endif // INCLUDE_HTTP_CONNECTION_HPP_
