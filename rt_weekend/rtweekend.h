#pragma once

// this file will get included at the top of our main.cpp file so we don't need to write so many include statements which is kinda ugly

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// no longer having to type std:: before the following common things:

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Common Headers

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"
