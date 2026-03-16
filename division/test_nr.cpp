#include <iostream>

// This is a script to test out the Newton-Raphson method's convergence
// https://www.researchgate.net/publication/220804890_An_Efficient_Hardware_Implementation_for_a_Reciprocal_Unit
// The article above states that the NR method doubles its precision every iteration
// The speed of convergence is dependent on the initial guess
// In the article, a degree 2 polynomial with coefficients a=2.58586, b=−5.81818, and c=4.24242, is evaluated at the divisor to get an inital guess of the reciprocal.

// With our small bit widths we can't use these exact coefficients so I'm gonna approximate them and see how precise it is compared to the actual initial guess. 
// We're using the fixed point format so I'm only gonna approximate these coefficients with possible fixed-point values

