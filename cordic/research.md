# Using CORDIC for division, arctan, vector magnitude, square root, cosine
CORDIC is a method where you binary search to get the answer. By its nature, its iterative and each iteration adds 1 bit of precision. Each iteration requires a clock pulse to update registers.

CORDIC's main selling point is the reusability it offers for various operations. In this document I'll be writing my research for how to perform each of the above operations using CORDIC, and then I'll see what circuitry can be reused when we put it all together.

## Division
Note: CORDIC division only converges when $-2 < Y/X < 2$.

The main algorithm is as follows:
Initialize $y_{0}=Y$, and $z_{0}=0$.

$$y_{i+1}=y_{i}-dX \cdot 2^{-i}$$

$$z_{i+1}=z_{i}+d \cdot 2^{-i}$$

Where $d=1$ if $Y>0$, $d=-1$ if $Y<0$.

After a desired number of iterations, the quotient will be $z_{i}$.

## Vector Magnitude and Arctan

Good news: While I don't think we'll ever need to find the angle of a vector. This same exact circuit can be used for it.

Note: This method only converges when the angle of our vector is between 90 and -90 degrees.

Depending on the number of iterations, the inputs need to be prescaled differently. For more than 6-7 bits of precision, prescale by 0.60725.

Initialize $y_{0}=0.60725Y$, $x_{0}=0.60725X$, $z_{0}=0$

Initialize a LUT with the following values at indexes 0-7:
45, 26.565, 14.036, 7.125, 3.576, 1.790, 0.895, 0.448

$$x_{i+1}=x_{i}+dX \cdot 2^{-i}$$

$$y_{i+1}=y_{i}-dX \cdot 2^{-i}$$

$$z_{i+1}=z_{i}+d\cdot AngleLUT[i]$$

Where $d=1$ if $Y>0$, $d=-1$ if $Y<0$.

After a desired number of iterations, $x_{i}$ will hold the magnitude, $z_{i}$ will hold the angle.

## Square Root

I noticed on the table of operations and their frequency in the Notion that vector normalization and square root are equal. I'm assuming this means that vector normalization is the only context in which we use square root in which case we don't need a separate circuit. I can ask AI for the algorithm if we need it tho.

## Cosine

Good news: Cosine resuses almost all the circuitry as vector normalization except for a slight difference in how we determine $d$.

Since cos(B) = cos(-B), negate B if its negative. Also, this only converges for $B < 90deg$

If we want to calculate $AcosB$, the algorithm is as follows:

Initialize $x_{0}=0.60725A$, $y_{0}=0$, $z_{0}=B$

$$x_{i+1}=x_{i}-dy_{i} \cdot 2^{-i}$$

$$y_{i+1}=y_{i}+dx_{i} \cdot 2^{-i}$$

$$z_{i+1}=z_{i}-d\cdot AngleLUT[i]$$

Where $d=1$ if $Z>0$, $d=-1$ if $Z<0$.

After a desired number of iterations, the value of $AcosB$ will be stored in $x_{i}$.




