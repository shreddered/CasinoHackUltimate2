#include "vk/client.hpp"
#include "http/utils.hpp"

#include <stdexcept>

namespace vk {

Client::Client(const std::string& token) : m_token{token} {}

std::string Client::queryParams(const json& data) {
    std::string result{};
    for (const auto& elem : data.items()) {
        if (elem.value().is_string()) {
            result += elem.key() + '=' + http::utils::escape(elem.value().get<std::string>()) + '&';
        } else {
            result += elem.key() + '=' + http::utils::escape(elem.value().dump()) + '&';
        }
    }
    result.pop_back();
    return result;
}

json Client::method(const std::string& name, json params) {
    if (!params.contains("access_token"))
        params["access_token"] = m_token;
    if (!params.contains("v"))
        params["v"] = Client::v;
    const auto response = m_session.post(Client::url + name, Client::queryParams(params));
    json data = json::parse(response);
    if (!data.contains("response")) {
        throw std::runtime_error{"Error from VK:" + data.dump(4)};
    }
    return data["response"];
}

} // namespace vk
