#include <iostream>
#include <random>
#include <cstdint>
#include <cmath>
#include "FixedPoint.hpp"

// Coefficients for polynomial that returns an initial guess for the reciprocal

constexpr double a{2.58586};
constexpr double b{-5.81818};
constexpr double c{4.24242};

constexpr int fractional_bits_8{4};
constexpr int fractional_bits_16{12};

int main() {
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "----- Start 8-Bit Test------" << std::endl;
    constexpr FixedPoint<std::int8_t, fractional_bits_8> a_8{a};
    constexpr FixedPoint<std::int8_t, fractional_bits_8> b_8{b};
    constexpr FixedPoint<std::int8_t, fractional_bits_8> c_8{c};
    std::cout << "a_8 = " << a_8.to_double() << std::endl;
    std::cout << "b_8 = " << b_8.to_double() << std::endl;
    std::cout << "c_8 = " << c_8.to_double() << std::endl;
    // Run through 5 random numbers and compare reciprocal guessed by a, b, c, with a_8, b_8, c_8
    // The range chosen is the range at which the initial guess is close to reciprocal (found through desmos)
    std::uniform_real_distribution<double> dis(0.5, 1);
    for (auto i{0}; i < 5; i++) {
        std::cout << std::endl;
        double random_val = dis(gen);
        FixedPoint<std::int8_t, fractional_bits_8> rand_fixed{random_val};
        FixedPoint<std::int8_t, fractional_bits_8> reciprocal_fixed = a_8*rand_fixed*rand_fixed + b_8*rand_fixed + c_8;
        double reciprocal{a*rand_fixed.to_double()*rand_fixed.to_double() + b*rand_fixed.to_double() + c};
        double bits_precise{-1.0*std::log2(std::abs(reciprocal - reciprocal_fixed.to_double()))};
        double relative_error{std::abs(reciprocal - reciprocal_fixed.to_double()) / reciprocal_fixed.to_double()};
        std::cout << "Reciprocal (double): " << reciprocal << ", " << "Reciprocal (fixed-point): " << reciprocal_fixed.to_double() << ", Bits of precision retained: " << bits_precise << ", Relative error: " << relative_error << std::endl;
    }
    std::cout << std::endl;
    std::cout << "----- End 8-Bit Test------" << std::endl;
    std::cout << "----- Start 16-Bit Test------" << std::endl;
    constexpr FixedPoint<std::int16_t, fractional_bits_16> a_16{a};
    constexpr FixedPoint<std::int16_t, fractional_bits_16> b_16{b};
    constexpr FixedPoint<std::int16_t, fractional_bits_16> c_16{c};
    std::cout << "a_16 = " << a_16.to_double() << std::endl;
    std::cout << "b_16 = " << b_16.to_double() << std::endl;
    std::cout << "c_16 = " << c_16.to_double() << std::endl;
    for (auto i{0}; i < 5; i++) {
        std::cout << std::endl;
        double random_val = dis(gen);
        FixedPoint<std::int16_t, fractional_bits_16> rand_fixed{random_val};
        FixedPoint<std::int16_t, fractional_bits_16> reciprocal_fixed = a_16*rand_fixed*rand_fixed + b_16*rand_fixed + c_16;
        double reciprocal{a*rand_fixed.to_double()*rand_fixed.to_double() + b*rand_fixed.to_double() + c};
        double bits_precise{-1.0*std::log2(std::abs(reciprocal - reciprocal_fixed.to_double()))};
        double relative_error{std::abs(reciprocal - reciprocal_fixed.to_double()) / reciprocal_fixed.to_double()};
        std::cout << "Reciprocal (double): " << reciprocal << ", " << "Reciprocal (fixed-point): " << reciprocal_fixed.to_double() << ", Bits of precision retained: " << bits_precise << ", Relative error: " << relative_error << std::endl;
    }
    std::cout << std::endl;
    std::cout << "----- End 16-Bit Test------" << std::endl;
}
