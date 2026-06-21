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
NUM_SAMPLES_SET = 1000
# 乱数生成数
NUM_RANDOM = NUM_SAMPLES_SET * SET_OF_CYCLES
# ラムダの値のリスト
LAMBDAS = [0.1, 0.25, 0.5, 0.75, 1.0, 1.5] 
# LAMBDAS = [2.0] 

# グラフ描画用の関数をインポート
from renderGraph import render_histogram, render_line_graph, render_multiple_line_graphs

def main() -> None:
    results_list = []

    for lam in LAMBDAS:
        # シミュレーションの初期化
        simulation = WaitingTaskSimulation(
            p_lambda=lam,
            set_of_cycles=SET_OF_CYCLES,
            seed=SEED
        )
        # シミュレーションの実行
        results = simulation.run_simulation(NUM_SAMPLES_SET)
        results_list.append(_cleaningList(results))
        # 結果の表示
        # print(f"Lambda: {lam}, Results: {results}")
        # グラフの描画
        # render_line_graph(results, lam)

    render_multiple_line_graphs(results_list, LAMBDAS)

def _cleaningList(values):
    # リストを、SET_OF_CYCLES-1より大きい値を、SET_OF_CYCLESに置き換えるて補正する関数
    _fit = lambda x: SET_OF_CYCLES if x > SET_OF_CYCLES - 1 else x
    cleaned_values = [_fit(value) for value in values]
    return cleaned_values

if __name__ == "__main__":
    main()
