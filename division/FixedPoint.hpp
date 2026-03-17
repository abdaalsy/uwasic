#include <cstdint>
#pragma once
// This is a script to test out the Newton-Raphson method's convergence, at different bit widths and decimal point placements
// https://www.researchgate.net/publication/220804890_An_Efficient_Hardware_Implementation_for_a_Reciprocal_Unit
// The article above states that the NR method doubles its precision every iteration
// The speed of convergence is dependent on the initial guess
// In the article, a degree 2 polynomial with coefficients a=2.58586, b=−5.81818, and c=4.24242, is evaluated at the divisor to get an inital guess of the reciprocal.

// With our small bit widths we can't use these exact coefficients so I'm gonna approximate them at different bit widths (8, 12, 16) and decimal point placements and see how precise it is compared to the actual initial guess. 
// We're using the fixed point format so I'm only gonna approximate these coefficients with possible fixed-point values

template<typename T, int fractional_bits>
struct FixedPoint {
    T raw;
    // Generate a fixed point number from a double
    constexpr FixedPoint(double decimal) : raw(static_cast<T>(decimal * (1LL << fractional_bits))) {}
    // We can convert to double when we actually want to print
    double to_double() const {
        return static_cast<double>(raw) / (1LL << fractional_bits);
    }
    FixedPoint operator+(const FixedPoint& right) const  {
        return FixedPoint<T, fractional_bits>(static_cast<T>(raw + right.raw));   
    }
    FixedPoint& operator+=(const FixedPoint& right) {
        *this = (*this) + right;
        return *this;
    }
    FixedPoint operator-(const FixedPoint& right) const {
        return FixedPoint<T, fractional_bits>(static_cast<T>(raw - right.raw));
    }
    FixedPoint& operator-=(const FixedPoint& right) {
        *this = (*this) - right;
        return *this;
    }
    FixedPoint operator*(const FixedPoint& right) const {
        // Imagine using cents instead of dollars to represent priced. $2 * $2 = $4. However, 200 * 200 = 40000 = $400
        // After multiplying the raw result, we need to divide our product by 2^fractional_bits
        // The raw result can get really large so we'll use a large type to hold it prior to scaling
        int64_t raw_result{static_cast<int64_t>(raw) * static_cast<int64_t>(right.raw)};
        return FixedPoint<T, fractional_bits>(static_cast<T>(raw_result >> fractional_bits));
    }
    FixedPoint& operator*=(const FixedPoint& right) {
        *this = (*this) * right;
        return *this;
    }
private:
    // Generate a fixed point number from another fixed point number (for doing math)
    // Private because inputting the number 10 expecting 10.0 can cause the raw to be 10 instead
    constexpr FixedPoint(T r) { raw = r; }
};

