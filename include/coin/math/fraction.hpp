#ifndef INCLUDE_COIN_MATH_FRACTION_HPP_
#define INCLUDE_COIN_MATH_FRACTION_HPP_

#include <numeric>
#include <ostream>
#include <stdexcept>
#include <string>

namespace coin {

namespace math {

template<class T>
class Fraction final {
public:
    T num, den;
    explicit constexpr Fraction(const T& _num, const T& _den) : num(_num), den(_den) {
        if (!_den)
            throw std::invalid_argument("Denominator must be != 0");
        this->reduce();
    }
    inline constexpr Fraction<T>& reverse() noexcept {
        std::swap(this->num, this->den);
        return *this;
    }
    inline std::string toString() const noexcept {
        return (((this->num < 0) != (this->den < 0)) ? "-" : "") + std::to_string(abs(this->num)) + 
            ((abs(this->den) == 1) ? "" : ('/' + std::to_string(abs(this->den))));
    }
    /*
     * '+', '-', '*', '/' unary/binary operators
     * Note that reduction happens on construction
     */ 
    template<class T1> 
    friend inline constexpr Fraction<T1> operator +(const Fraction<T1>& f1, const Fraction<T1>& f2) noexcept {
        return Fraction<T1>(f1.num * f2.den + f2.num * f1.den, f1.den * f2.den);
    }
    template<class T1>
    friend inline constexpr Fraction<T1> operator -(const Fraction<T1>& f1, const Fraction<T1>& f2) noexcept {
        return Fraction<T1>(f1.num * f2.den - f2.num * f1.den, f1.den * f2.den);
    }
    template<class T1>
    friend inline constexpr Fraction<T1> operator *(const Fraction<T1>& f1, const Fraction<T1>& f2) noexcept {
        return Fraction<T1>(f1.num * f2.num, f2.den * f1.den);
    }
    template<class T1>
    friend inline constexpr Fraction<T1> operator /(const Fraction<T1>& f1, const Fraction<T1>& f2) noexcept {
        return Fraction<T1>(f1.num * f2.den, f2.num * f1.den);
    }
    template<class T1>
    friend std::ostream& operator <<(std::ostream& os, const Fraction<T1>& frac) noexcept {
        return os << frac.dump();
    }
    inline constexpr Fraction<T>& operator -() noexcept {
        this->num *= static_cast<T>(-1);
        return *this;
    }
    inline constexpr Fraction<T>& operator +() noexcept {
        return *this; // lol
    }
private:
    constexpr Fraction<T>& reduce() noexcept {
        T div = std::gcd(this->num, this->den);
        this->num /= div;
        this->den /= div;
        return *this;
    }
}; // class Fraction

} // namespace math

} // namespace coin

#endif // INCLUDE_COIN_MATH_FRACTION_HPP_
