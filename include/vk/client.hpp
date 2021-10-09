#ifndef INCLUDE_VK_CLIENT_HPP_
#define INCLUDE_VK_CLIENT_HPP_

#include "http/session.hpp"
// json
#include <nlohmann/json.hpp>
// STL headers
#include <stdexcept>
#include <string>

namespace vk {

using nlohmann::json;

class ApiException : public std::runtime_error {
public:
    explicit ApiException(const std::string& msg) noexcept;
}; // class ApiException

class Client {
public:
    static constexpr const char v[] = "5.131";
    static constexpr const char url[] = "https://api.vk.com/method/";
    explicit Client(const std::string& token);
    json method(const std::string& name, json params);
private:
    static std::string queryParams(const json& data);
    http::Session m_session;
    std::string m_token;
}; // class Client

} // namespace vk

#endif // INCLUDE_VK_CLIENT_HPP_
