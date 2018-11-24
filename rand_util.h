#ifndef RU_H
#define RU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/**random_double - random DOUBLE
  *Computes a randomom double between 0 and 1 using C's inbuilt RNG
*/
double random_double();

/**random_double - random DOUBLE
  *Computes a randomom double between min and max (inclusive ish) using C's inbuilt RNG
    * min. The minimum value
    * max. The maximum value
*/
double random_range(double min, double max);

/**random_bool - random BOOLEAN
  * Computes a randomom boolean which is true with probability p.
  * p. The probability of returning true
*/
bool random_bool(double p);

double gauss(void);

int random_integer(int min, int max);

int binomial(int n, double p);

#endif
