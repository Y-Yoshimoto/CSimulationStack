# mcmc_poisson – 待ち行列モデル向けポアソンサンプラー

待ち行列モデルのマルコフ連鎖モンテカルロ（MCMC）シミュレーション基盤です。ポアソン分布サンプリングを使用します。

## ディレクトリ構成

```
mcmc_poisson/
├── c_impl/          # C言語実装（Knuth法）
├── python_impl/     # Python実装（NumPy）
└── benchmark/       # C言語版とPython版のベンチマーク比較
```

## クイックスタート

### C言語実装

```bash
cd c_impl
make
./poisson_demo
```

### Python実装

```bash
pip install numpy
cd python_impl
python3 main.py
```

### ベンチマーク

**C言語版ベンチマーク:**

```bash
cd benchmark
make
./benchmark_c
```

**Python版ベンチマーク:**

```bash
cd benchmark
python3 benchmark.py
```

## アルゴリズム

C言語実装では、ポアソン分布サンプリングに **Knuth法** を使用しています。

1. `L = exp(-λ)` を計算する
2. `k = 0`、`p = 1` を初期化する
3. `(0, 1]` の範囲で一様乱数 `U` を生成する
4. `p = p * U` を計算する
5. `p < L` ならば `k` を返す。そうでなければ `k++` してステップ3へ戻る

Python実装では `numpy.random.Generator.poisson()` を使用します。  
分布として等価であり、バッチ（ベクトル化）サンプリングに高度に最適化されています。

## λ値の想定範囲

λ = 0 ～ 2（待ち行列モデルの到着率・サービス率に適した範囲）
