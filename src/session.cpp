#include "http/connection.hpp"
#include "http/session.hpp"
#include "http/utils.hpp"

namespace http {

Session::Session() : m_ctx{ssl::context::tlsv12_client} {
    m_ctx.set_default_verify_paths();
    m_ctx.set_verify_mode(ssl::verify_peer);
}

std::string Session::get(const std::string& url) {
    const auto data = utils::getHostAndTarget(url);
    Connection conn{m_ioc, m_ctx}; 
    conn.open(data.host, "443");

    http::request<http::string_body> request{http::verb::get, data.target, 11};
    request.set(http::field::host, data.host);
    request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    auto response = conn.send(request);

    return beast::buffers_to_string(response.body().data());
}

std::string Session::post(const std::string& url, const std::string& str) {
    const auto data = utils::getHostAndTarget(url);
    Connection conn{m_ioc, m_ctx}; 
    conn.open(data.host, "443");

    http::request<http::string_body> request{http::verb::post, data.target + '?' + str, 11};
    request.set(http::field::host, data.host);
    request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    request.set(http::field::content_type, "application/x-www-form-urlencode");
    request.body() = str;
    request.prepare_payload();

    auto response = conn.send(request);

    return beast::buffers_to_string(response.body().data());
}

} // namespace http
