#ifndef POISSON_SAMPLER_H
#define POISSON_SAMPLER_H

/*
 * Poisson distribution sampler using Knuth's algorithm.
 * Suitable for lambda values in the range 0-2 (queuing model use case).
 */

/*
 * Sample from a Poisson distribution with the given lambda.
 *
 * Parameters:
 *   lambda - expected value (mean) of the distribution (0 <= lambda <= 2)
 *   seed   - pointer to the random seed state (updated on each call)
 *
 * Returns:
 *   Number of events sampled from Poisson(lambda)
 */
int poisson_sample(double lambda, unsigned int *seed);

#endif /* POISSON_SAMPLER_H */
