"""
Demo: Poisson sampler (Python / NumPy implementation).
Mirrors the output of the C implementation demo.
"""

import numpy as np
from poisson_sampler import poisson_sample, poisson_samples

SEED = 42
NUM_SAMPLES = 20
LAMBDAS = [0.5, 1.0, 1.5, 2.0]


def main() -> None:
    rng = np.random.default_rng(SEED)

    print("Poisson sampler demo (NumPy)")
    print("=" * 40)
    print()

    for lam in LAMBDAS:
        samples = poisson_samples(lam, NUM_SAMPLES, rng)
        mean = samples.mean()
        print(f"lambda = {lam:.1f}  -> samples: {' '.join(str(k) for k in samples)}")
        print(f"  mean = {mean:.3f} (expected {lam:.1f})")
        print()


if __name__ == "__main__":
    main()
