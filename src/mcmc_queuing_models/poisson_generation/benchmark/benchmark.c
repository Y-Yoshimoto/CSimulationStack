/* Enable clock_gettime and CLOCK_MONOTONIC from POSIX */
#define _POSIX_C_SOURCE 199309L

#include "../c_impl/poisson_sampler.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Number of samples per benchmark run */
#define NUM_SAMPLES 100000
/* Number of repeat runs used to compute mean / stddev */
#define NUM_RUNS 10
/* Random seed base */
#define SEED_BASE 12345U

static void format_with_commas(unsigned long long value, char *buffer,
                               size_t buffer_size) {
  char digits[32];
  size_t digit_count = 0;

  do {
    digits[digit_count++] = (char)('0' + (value % 10ULL));
    value /= 10ULL;
  } while (value > 0ULL);

  size_t output_index = 0;
  for (size_t i = 0; i < digit_count; i++) {
    if (i > 0 && (digit_count - i) % 3 == 0) {
      if (output_index + 1 < buffer_size) {
        buffer[output_index++] = ',';
      }
    }

    if (output_index + 1 < buffer_size) {
      buffer[output_index++] = digits[digit_count - 1 - i];
    }
  }

  if (buffer_size > 0) {
    buffer[output_index < buffer_size ? output_index : buffer_size - 1] = '\0';
  }
}

static double clock_seconds(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec + ts.tv_nsec * 1e-9;
}

static void benchmark_lambda(double lambda) {
  double times[NUM_RUNS];

  for (int r = 0; r < NUM_RUNS; r++) {
    unsigned int seed = SEED_BASE + (unsigned int)r;
    double t0 = clock_seconds();

    for (int i = 0; i < NUM_SAMPLES; i++) {
      (void)poisson_sample(lambda, &seed);
    }

    double t1 = clock_seconds();
    times[r] = t1 - t0;
  }

  /* Compute mean and standard deviation */
  double mean = 0.0;
  for (int r = 0; r < NUM_RUNS; r++) {
    mean += times[r];
  }
  mean /= NUM_RUNS;

  double var = 0.0;
  for (int r = 0; r < NUM_RUNS; r++) {
    double diff = times[r] - mean;
    var += diff * diff;
  }
  double stddev = sqrt(var / (NUM_RUNS - 1));

  double throughput = (double)NUM_SAMPLES / mean;
  unsigned long long throughput_rounded =
      (unsigned long long)llround(throughput);
  char throughput_text[32];
  format_with_commas(throughput_rounded, throughput_text,
                     sizeof(throughput_text));

  printf("  lambda = %.1f | mean = %.6f s | stddev = %.6f s | throughput = %s "
         "samples/s\n",
         lambda, mean, stddev, throughput_text);
}

int main(void) {
  double lambdas[] = {0.5, 1.0, 1.5, 2.0};
  int num_lambdas = (int)(sizeof(lambdas) / sizeof(lambdas[0]));

  printf("Poisson Sampler Benchmark (C / Knuth's algorithm)\n");
  printf("==================================================\n");
  printf("Samples per run: %d   Runs: %d\n\n", NUM_SAMPLES, NUM_RUNS);

  for (int i = 0; i < num_lambdas; i++) {
    benchmark_lambda(lambdas[i]);
  }

  printf("\nDone.\n");
  return 0;
}
