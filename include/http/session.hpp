#ifndef INCLUDE_HTTP_SESSION_HPP_
#define INCLUDE_HTTP_SESSION_HPP_

#include "http/http.hpp"
// STL headers
#include <string>

namespace http {

class Session {
public:
    Session();
    std::string get(const std::string& url);
    std::string post(const std::string& url, const std::string& data);
    virtual ~Session() noexcept = default;
private:
    net::io_context m_ioc;
    ssl::context m_ctx;
}; // class Session

} // namespace http

#endif // INCLUDE_HTTP_SESSION_HPP_
