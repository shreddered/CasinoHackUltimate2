#include "http/utils.hpp"

#include <cctype>
#include <iomanip>
#include <ios>
#include <regex>
#include <sstream>

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

std::string escape(const std::string& unescaped) {
    std::ostringstream os;
    os << std::hex;
    for (const auto& c : unescaped) {
        if (isalnum(c) || c == '-' || c == '~' || c == '_' || c == '.') {
            os << c;
        } else {
            os << std::uppercase;
            os << '%' << std::setw(2) << int((unsigned char) c);
            os << std::nouppercase;
        }
    }
    return os.str();
}

} // namespace http::utils
