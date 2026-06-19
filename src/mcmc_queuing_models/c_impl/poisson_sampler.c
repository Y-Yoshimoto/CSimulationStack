/* Enable rand_r (reentrant) from POSIX */
#define _POSIX_C_SOURCE 199506L

#include "poisson_sampler.h"

#include <math.h>
#include <stdlib.h>

/*
 * Sample from a Poisson distribution using Knuth's algorithm.
 *
 * Algorithm:
 *   1. Compute L = exp(-lambda)
 *   2. Set k = 0, p = 1
 *   3. Generate uniform random U in (0, 1]
 *   4. p = p * U
 *   5. If p < L, return k; otherwise k++, go to step 3
 */
int poisson_sample(double lambda, unsigned int *seed)
{
    double L = exp(-lambda);
    double p = 1.0;
    int k = 0;
    /* Precompute the divisor: rand_r range is [0, RAND_MAX], shift to (0, 1] */
    static const double RAND_DIVISOR = (double)RAND_MAX + 2.0;

    do {
        k++;
        double u = (rand_r(seed) + 1.0) / RAND_DIVISOR;
        p *= u;
    } while (p > L);

    return k - 1;
}
