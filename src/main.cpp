#include "coin/miner.hpp"
#include "coin/math/eval.hpp"

#include <nlohmann/json.hpp>

#include <boost/program_options.hpp>

#include <fstream>
#include <iostream>

using nlohmann::json;

int main(int argc, char* argv[]) {
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "print this help message")
        ("token", boost::program_options::value<std::string>(),
            "VK API access token");
    boost::program_options::variables_map vm;
    boost::program_options::store(
            boost::program_options::parse_command_line(argc, argv, desc),
            vm);
    boost::program_options::notify(vm);
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }
    if (!vm.count("token")) {
        std::cerr << desc << std::endl;
        return 1;
    }
    std::string token = vm["token"].as<std::string>();
    coin::Miner miner{token};
    miner.run();
    return 0;
}
