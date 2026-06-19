"""
Poisson distribution sampler using NumPy.
Equivalent to the C implementation (Knuth's algorithm range 0-2).
"""

import numpy as np


def poisson_sample(lambda_: float, rng: np.random.Generator) -> int:
    """
    Sample a single value from Poisson(lambda_) using NumPy.

    Parameters
    ----------
    lambda_ : float
        Expected value (mean) of the distribution. Intended range: 0-2.
    rng : np.random.Generator
        NumPy random number generator instance.

    Returns
    -------
    int
        Number of events sampled from Poisson(lambda_).
    """
    return int(rng.poisson(lambda_))


def poisson_samples(lambda_: float, n: int, rng: np.random.Generator) -> np.ndarray:
    """
    Draw *n* samples from Poisson(lambda_) at once (vectorised).

    Parameters
    ----------
    lambda_ : float
        Expected value (mean) of the distribution.
    n : int
        Number of samples to draw.
    rng : np.random.Generator
        NumPy random number generator instance.

    Returns
    -------
    np.ndarray of int
        Array of sampled event counts.
    """
    return rng.poisson(lambda_, size=n)
