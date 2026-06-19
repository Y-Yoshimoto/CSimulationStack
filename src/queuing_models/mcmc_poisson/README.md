# mcmc_poisson – Poisson Sampler for Queuing Models

MCMC simulation foundation using Poisson distribution sampling for queuing models.

## Directory Structure

```
mcmc_poisson/
├── c_impl/          # C implementation (Knuth's algorithm)
├── python_impl/     # Python implementation (NumPy)
└── benchmark/       # Benchmark comparison (C and Python)
```

## Quick Start

### C Implementation

```bash
cd c_impl
make
./poisson_demo
```

### Python Implementation

```bash
pip install numpy
cd python_impl
python3 main.py
```

### Benchmarks

**C benchmark:**

```bash
cd benchmark
make
./benchmark_c
```

**Python benchmark:**

```bash
cd benchmark
python3 benchmark.py
```

## Algorithm

The C implementation uses **Knuth's algorithm** for Poisson sampling:

1. Compute `L = exp(-λ)`
2. Set `k = 0`, `p = 1`
3. Generate uniform random `U` in `(0, 1]`
4. `p = p * U`
5. If `p < L`, return `k`; otherwise `k++` and go to step 3

The Python implementation uses `numpy.random.Generator.poisson()`, which is
equivalent in distribution and highly optimised for batch (vectorised) sampling.

## Intended Lambda Range

λ = 0 – 2 (suitable for queuing model arrival/service rates).
