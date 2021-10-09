#include "coin/miner.hpp"
#include "coin/math/eval.hpp"
#include "http/session.hpp"

#include <chrono>
#include <fstream>
#include <random>
#include <thread>
#include <unordered_map>

#include <nlohmann/json.hpp>

namespace coin {

using nlohmann::json;

NoImageException::NoImageException(const std::string& msg) noexcept
    : std::runtime_error{msg} {}

Miner::Miner(const std::string& token) : m_client{token} {}

void Miner::sendMessage(const std::string& text, const std::string& payload) {
    static std::random_device rd;
    static std::mt19937 gen{rd()};
    json data = { { "random_id", gen() },
                  { "message", text },
                  { "peer_id", Miner::peer } };
    if (!payload.empty())
        data["payload"] = payload;
    m_client.method("messages.send", data);
}

std::string Miner::getLastImage() {
    const json data = { { "peer_id", Miner::peer },
                        { "count", 1 } };
    const auto response = m_client.method("messages.getHistory", data);
    const auto message = response["items"].front();
    if (message["attachments"].empty()) {
        throw NoImageException{message["text"].get<std::string>()};
    }
    const auto sizes = message["attachments"][0]["photo"]["sizes"];
    const std::string url = sizes.back()["url"].get<std::string>();
    http::Session session;
    return session.get(url);
}

std::string Miner::getLastMessage() {
    const json data = { { "peer_id", Miner::peer },
                        { "count", 1 } };
    const auto response = m_client.method("messages.getHistory", data);
    const auto message = response["items"].front();
    return message["text"].get<std::string>();
}

void Miner::run() {
    std::unordered_map<std::string, std::string> actions = {
        { "play", R"({"action":"play"})" },
        { "level", R"({"action":"level","level":12})" },
        { "show_answer", R"({"action":"show_answer"})" } };
    while (1) {
        try {
            sendMessage("Ур. 12", actions["level"]);
            std::this_thread::sleep_for(std::chrono::seconds(2));
            auto const data = getLastImage();
            auto const ans = math::eval(data);
            std::this_thread::sleep_for(std::chrono::seconds(7));
            sendMessage(ans);
            std::this_thread::sleep_for(std::chrono::seconds(4));
            if (getLastMessage() == "Ответ неверный, попробуйте ещё раз...") {
                std::this_thread::sleep_for(std::chrono::seconds(4));
                sendMessage("Показать ответ", actions["show_answer"]);
                std::this_thread::sleep_for(std::chrono::seconds(4));
            }
        } catch(math::EvalException e) { // give up on failure
            std::this_thread::sleep_for(std::chrono::seconds(4));
            sendMessage("Показать ответ", actions["show_answer"]);
            std::this_thread::sleep_for(std::chrono::seconds(4));
        }
    }
}

}
