#include "poisson_sampler.h"

#include <stdio.h>
#include <stdlib.h>

#define NUM_SAMPLES 20
#define SEED        42

int main(void)
{
    unsigned int seed = SEED;
    double lambdas[] = {0.5, 1.0, 1.5, 2.0};
    int num_lambdas = (int)(sizeof(lambdas) / sizeof(lambdas[0]));

    printf("Poisson sampler demo (Knuth's algorithm)\n");
    printf("=========================================\n\n");

    for (int i = 0; i < num_lambdas; i++) {
        double lambda = lambdas[i];
        double sum = 0.0;

        printf("lambda = %.1f  -> samples: ", lambda);
        for (int j = 0; j < NUM_SAMPLES; j++) {
            int k = poisson_sample(lambda, &seed);
            sum += k;
            printf("%d ", k);
        }
        printf("\n");
        printf("  mean = %.3f (expected %.1f)\n\n", sum / NUM_SAMPLES, lambda);
    }

    return 0;
}
