#include <iostream>
#include <boost/asio.hpp>

#include "http/session.hpp"

int main(int argc, char* argv[]) {
    http::Session session;
    std::cout << session.get("https://google.com") << std::endl;
    std::cout << session.get("https://ya.ru") << std::endl;
    return 0;
}
