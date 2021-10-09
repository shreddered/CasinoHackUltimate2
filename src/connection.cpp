#include "http/connection.hpp"

namespace http {

Connection::Connection(net::io_context& ioc, ssl::context& ctx)
    : m_stream{ioc, ctx}, m_resolver{ioc} {}

void Connection::open(const std::string& host, const std::string& port) {
    if (!SSL_set_tlsext_host_name(m_stream.native_handle(), host.c_str())) {
        beast::error_code ec{static_cast<int>(
                    ERR_get_error()), net::error::get_ssl_category()};
        throw beast::system_error{ec};
    }
    const auto results = m_resolver.resolve(host, port);
    beast::get_lowest_layer(m_stream).connect(results);
    m_stream.handshake(ssl::stream_base::client);
}

http::response<http::dynamic_body> Connection::send(
        const http::request<http::string_body>& request) {
    http::write(m_stream, request);

    http::response<http::dynamic_body> response;
    http::read(m_stream, m_buf, response);

    return response;
}

Connection::~Connection() {
    beast::error_code ec;
    m_stream.shutdown(ec);
}

} // namespace http
