#ifndef INCLUDE_HTTP_UTILS_HPP_
#define INCLUDE_HTTP_UTILS_HPP_

// STL headers
#include <string>

namespace http {

namespace utils {

struct Data {
    std::string host;
    std::string target;
}; // struct Data

Data getHostAndTarget(const std::string& url);

} // namespace utils

} // namespace http

#endif // INCLUDE_HTTP_UTILS_HPP_
