#ifndef INCLUDE_COIN_MINER_HPP_
#define INCLUDE_COIN_MINER_HPP_

#include "vk/client.hpp"

#include <stdexcept>
#include <string>

namespace coin {

class NoImageException : public std::runtime_error {
public:
    explicit NoImageException(const std::string& msg) noexcept;
}; // class NoImageException

class Miner {
public:
    static constexpr const char peer[] = "-181671440"; // Coin Math id
    explicit Miner(const std::string& token);
    void run(); 
private:
    void sendMessage(const std::string& text, const std::string& payload = "");
    std::string getLastImage();
    std::string getLastMessage();
    vk::Client m_client;
}; // class Client

} // namespace casino

#endif // INCLUDE_COIN_MINER_HPP_
