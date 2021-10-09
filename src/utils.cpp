#include "http/utils.hpp"

#include <regex>

namespace http::utils {

Data getHostAndTarget(const std::string& url) {
    Data result;
    static const std::regex filter{R"((http[s]:\/\/)?([^:\/\s]+)(\/.*)?)"};
    std::smatch match;
    if (std::regex_match(url, match, filter)) {
        result.host = std::string{match[2].str()};
        result.target = std::string{match[3].str()};
        if (result.target.empty())
            result.target = "/";
    }
    return result;
}

} // namespace http::utils
