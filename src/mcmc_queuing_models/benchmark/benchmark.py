"""
Benchmark: Poisson sampler (Python / NumPy) vs C reference.

Measures throughput (samples/second) for lambda = 0.5, 1.0, 1.5, 2.0
using both element-wise sampling and vectorised NumPy sampling.
"""

import sys
import time
import math
import numpy as np

# Make python_impl importable when run from the benchmark directory
sys.path.insert(0, "../python_impl")
from poisson_sampler import poisson_sample, poisson_samples  # noqa: E402

NUM_SAMPLES = 100_000
NUM_RUNS = 10
SEED = 12345
LAMBDAS = [0.5, 1.0, 1.5, 2.0]


def _stats(times: list[float]) -> tuple[float, float]:
    """Return (mean, stddev) for a list of elapsed times."""
    mean = sum(times) / len(times)
    var = sum((t - mean) ** 2 for t in times) / (len(times) - 1)
    return mean, math.sqrt(var)


def bench_elementwise(lambda_: float) -> tuple[float, float]:
    """Benchmark element-wise sampling (one call per sample)."""
    times = []
    for r in range(NUM_RUNS):
        rng = np.random.default_rng(SEED + r)
        t0 = time.perf_counter()
        for _ in range(NUM_SAMPLES):
            poisson_sample(lambda_, rng)
        times.append(time.perf_counter() - t0)
    return _stats(times)


def bench_vectorised(lambda_: float) -> tuple[float, float]:
    """Benchmark vectorised (batch) sampling."""
    times = []
    for r in range(NUM_RUNS):
        rng = np.random.default_rng(SEED + r)
        t0 = time.perf_counter()
        poisson_samples(lambda_, NUM_SAMPLES, rng)
        times.append(time.perf_counter() - t0)
    return _stats(times)


def main() -> None:
    print("Poisson Sampler Benchmark (Python / NumPy)")
    print("=" * 50)
    print(f"Samples per run: {NUM_SAMPLES:,}   Runs: {NUM_RUNS}")
    print()

    print("-- Element-wise sampling (single call per sample) --")
    for lam in LAMBDAS:
        mean, stddev = bench_elementwise(lam)
        throughput = NUM_SAMPLES / mean
        print(
            f"  lambda = {lam:.1f} | mean = {mean:.6f} s | "
            f"stddev = {stddev:.6f} s | throughput = {throughput:,.0f} samples/s"
        )

    print()
    print("-- Vectorised sampling (batch NumPy call) --")
    for lam in LAMBDAS:
        mean, stddev = bench_vectorised(lam)
        throughput = NUM_SAMPLES / mean
        print(
            f"  lambda = {lam:.1f} | mean = {mean:.6f} s | "
            f"stddev = {stddev:.6f} s | throughput = {throughput:,.0f} samples/s"
        )

    print()
    print("Done.")


if __name__ == "__main__":
    main()
