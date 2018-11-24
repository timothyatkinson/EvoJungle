#include "rand_util.h"

/**random_double - random double
  *Computes a randomom double between 0 and 1 using C's inbuilt RNG
*/
double random_double(){
  return (double)rand() / (double)RAND_MAX;
}

/**random_double - random double
  *Computes a randomom double between min and max (inclusive ish) using C's inbuilt RNG
    * min. The minimum value
    * max. The maximum value
*/
double random_range(double min, double max){
  return min + (random_double() * fabs(max - min));
}

/**random_bool - random BOOLEAN
  * Computes a randomom boolean which is true with probability p.
  * p. The probability of returning true
*/
bool random_bool(double p){
  return random_double() <= p;
}


/* generate a randomom value weighted within the normal (gaussian) distribution */
double gauss(void)
{
  double x = (double)rand() / RAND_MAX,
         y = (double)rand() / RAND_MAX,
         z = sqrt(-2 * log(x)) * cos(2 * M_PI * y);
  return z;
}


int random_integer(int min, int max){
    return (int)round((random_double() * ((max - 1) - min)) + min);
}


int binomial(int n, double p){
  int x = 0;
  for(int i = 0; i < n; i++){
    if(random_bool(p)){
      x++;
    }
  }
  return x;
}
