#include "coin/miner.hpp"
#include "coin/math/eval.hpp"

#include <nlohmann/json.hpp>

#include <boost/program_options.hpp>

#include <cstdlib>
#include <fstream>
#include <iostream>

using nlohmann::json;

int main(int argc, char* argv[]) {
    std::string token = std::getenv("TOKEN");
    coin::Miner miner{token};
    miner.run();
    return 0;
}
