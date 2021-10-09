#ifndef INCLUDE_COIN_MATH_EVAL_HPP_
#define INCLUDE_COIN_MATH_EVAL_HPP_

#include <stdexcept>
#include <string>

namespace coin {

namespace math {

class EvalException : public std::runtime_error {
public:
    explicit EvalException(const std::string& msg) noexcept;
}; // class EvalException

std::string eval(const std::string& image);

} // namespace math

} // namespace coin

#endif // INCLUDE_COIN_MATH_EVAL_HPP_
