# ヒストグラムのグラフを描画するためのコード
import matplotlib.pyplot as plt
import numpy as np

# ヒストグラムを描画し、jpegファイルとして保存する関数
def render_histogram(samples, lam):
    # ヒストグラムを描画
    plt.figure(figsize=(10, 6))
    plt.hist(samples, bins=np.arange(-0.5, samples.max() + 1.5, 1), density=True, alpha=0.6, color='g')
    
    # タイトルとラベルを設定
    plt.title(f'Poisson Distribution (lambda={lam})')
    plt.xlabel('Value')
    plt.ylabel('Density')
    
    # グリッドを表示
    plt.grid(True)
    
    # jpegファイルとして保存
    filename = f'poisson_histogram_lambda_{lam:.1f}.jpeg'
    plt.savefig(filename)
    print(f"Histogram saved as {filename}")
    
    # グラフを表示
    plt.show()

# リストの値をy軸の値として、x軸は0からリストの長さ-1までの整数とするグラフを描画し、jpegファイルとして保存する関数
def render_line_graph(values, lam, max_y = 60, min_y = 0):
    # x軸の値を生成
    x_values = np.arange(len(values))
    
    # 線グラフを描画
    plt.figure(figsize=(10, 6))
    plt.plot(x_values, values, marker=None, linestyle='-', color='b')
    plt.ylim(min_y, max_y)
    # 点を描画しない
    plt.scatter(x_values, values, color='b')
    
    # タイトルとラベルを設定
    plt.title(f'Line Graph of Values (lambda={lam})')
    plt.xlabel('Index')
    plt.ylabel('Value')
    
    # グリッドを表示
    plt.grid(True)
    
    # jpegファイルとして保存
    filename = f'line_graph_lambda_{lam:.1f}.jpeg'
    plt.savefig(filename)
    print(f"Line graph saved as {filename}")
    
    # グラフを表示
    plt.show()
# リストのオブジェクトを引数にとり、パラメータの値ごとに判例をつけて、複数の線グラフを同じグラフに描画する関数
def render_multiple_line_graphs(values_list, lam_list, max_y = 60, min_y = 0):
    # x軸の値を生成
    x_values = np.arange(len(values_list[0]))
    
    # 線グラフを描画
    plt.figure(figsize=(10, 6))
    for values, lam in zip(values_list, lam_list):
        plt.plot(x_values, values, marker=None, linestyle='-', label=f'lambda={lam}')
    plt.ylim(min_y, max_y)
    
    # タイトルとラベルを設定
    plt.title('Line Graph of Values for Different Lambdas')
    plt.xlabel('Index')
    plt.ylabel('Value')
    
    # 凡例を表示
    plt.legend()
    
    # グリッドを表示
    plt.grid(True)
    
    # jpegファイルとして保存
    filename = 'multiple_line_graphs.jpeg'
    plt.savefig(filename)
    print(f"Multiple line graphs saved as {filename}")
    
    # グラフを表示
    plt.show()