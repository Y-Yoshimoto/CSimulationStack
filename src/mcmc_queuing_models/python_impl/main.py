"""
Demo: Poisson sampler (Python / NumPy implementation).
Mirrors the output of the C implementation demo.
"""
# 乱数シード用
import time

# シミュレート関数読み込み
from WaitingTaskSimulation import WaitingTaskSimulation

# 定数
## 乱数シードは実行ごとに変わるように、現在の時間をミリ秒単位で取得して使用
SEED = int(time.time() * 1000) % 1000000  # Generate a random seed for reproducibility
##　1セット当たりのサイクル数
SET_OF_CYCLES = 60
# サンプリングセット数
NUM_SAMPLES_SET = 100
# 乱数生成数
NUM_RANDOM = NUM_SAMPLES_SET * SET_OF_CYCLES
# ラムダの値のリスト
# LAMBDAS = [0.5, 1.0, 1.5, 2.0, 2.5, 3.0] 
LAMBDAS = [2.0] 

# グラフ描画用の関数をインポート
from renderGraph import render_histogram

def main() -> None:

    for lam in LAMBDAS:
        # シミュレーションの初期化
        simulation = WaitingTaskSimulation(
            p_lambda=lam,
            set_of_cycles=SET_OF_CYCLES,
            seed=SEED
        )
        # シミュレーションの実行
        results = simulation.run_simulation(NUM_SAMPLES_SET)
        # 結果の表示
        print(f"Lambda: {lam}, Results: {results}")

if __name__ == "__main__":
    main()
