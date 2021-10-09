#ifndef INCLUDE_HTTP_HTTP_HPP_
#define INCLUDE_HTTP_HTTP_HPP_

// boost headers
// boost::asio
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
// boost::beast
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>

namespace http {

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;

} // namespace http

#endif // INCLUDE_HTTP_HTTP_HPP_
