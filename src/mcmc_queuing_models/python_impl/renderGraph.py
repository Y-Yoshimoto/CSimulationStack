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