# 変則待ち行列MCMCシミュレーション
# キューに対して1サイクル辺り1つのタスクが1つキューに追加される
# キューの最大の大きさが決まっていて、キューが満杯の時は新しいタスクは破棄される
# キューからは、ポアソン分布に従ってタスクが取り出される
# {set_of_cycles} サイクルを1セットとして、{num_samples_set}セットのシミュレーションを行う

# 乱数シード用
import time
BASE_SEED = int(time.time() * 1000) % 1000000

# numpy
import numpy as np


class WaitingTaskSimulation:
    '''変則待ち行列シミュレーションを行うクラス'''
    
    def __init__(self,
                p_lambda: float,
                set_of_cycles: int = 60, 
                queue_length: int = 5, 
                initial_easing_cycles: int = 1,
                seed: int = BASE_SEED):
        '''コンストラクタ
        Args:
            set_of_cycles (int): 1セット当たりのサイクル数
            queue_length (int): キューの最大長
            p_lambda (float): ポアソン分布のパラメータ
            initial_easing_cycles (int): 初期緩和セット数
            seed (int): 乱数シード
        '''
        # インスタンス変数の初期化
        self.parm = {
            "set_of_cycles": set_of_cycles,
            "queue_length": queue_length,
            "p_lambda": p_lambda,
            "initial_easing_cycles": initial_easing_cycles,
        }
        self.rng = np.random.default_rng(seed)
        # キューの初期化
        self.queue = 0
        # 初期緩和を行う
        self.initial_easing()

    ## ユーティリティ関数 #################################
    def _generate_poisson_samples(self, n: int) -> np.ndarray:
        '''ポアソン分布に従ってn個のサンプルを生成する'''
        return self.rng.poisson(self.parm["p_lambda"], size=n)

    def _add_task(self):
        ''' キューイングシミュレーションを行う '''
        if self.queue <= self.parm["queue_length"]:
                self.queue += 1

    def _dequeue_tasks(self, num_tasks: int):
        ''' キューからタスクを取り出し取り出した値を返す '''
        dequeue_count = min(num_tasks, self.queue)
        self.queue -= dequeue_count
        # print(f"DEBUG: キューの状態: {self.queue} -> 取り出したタスク数: {dequeue_count}")
        return dequeue_count

    def initial_easing(self) -> None:
        '''初期緩和処理を行う'''
        _poisson_s = self._generate_poisson_samples(self.parm["initial_easing_cycles"] * self.parm["set_of_cycles"])
        return self._one_set_simulation(_poisson_s)

    ## シミュレーション関数 #################################
    def _one_set_simulation(self, _poisson_s) -> int:
        '''1セットのシミュレーションを実行する
        Args:
            _poisson_s (np.ndarray): ポアソン分布に従って生成されたサンプル
        Returns:
            int: 各サイクルで取り出されたタスク数の合計
        '''
        results = map(lambda x: self._one_cycle_simulation(), _poisson_s)
        # print(f"DEBUG: 処理結果の合計: {sum(results)}")
        return sum(results)
    
    def _debug_one_set_simulation(self, _poisson_s) -> tuple[int, list[int]]:
        results = list(map(lambda x: self._one_cycle_simulation(), _poisson_s))
        # print(f"DEBUG: 処理結果の合計: {sum(results)}")
        return (sum(results), results)

    def _one_cycle_simulation(self) -> int:
        '''1サイクルのシミュレーションを実行する'''
        # キューにタスクを追加する
        self._add_task()
        # ポアソン分布に従ってタスクを取り出す
        tasks_removed = self._dequeue_tasks(self.rng.poisson(self.parm["p_lambda"]))
        return tasks_removed
    
    def run_simulation(self, run_set: int) -> list[int]:
        '''シミュレーションを実行する'''
        # ポアソン分布に従ってサンプルを生成する
        _poisson_s = self._generate_poisson_samples(run_set * self.parm["set_of_cycles"])
        # 1セットごとに、サンプルを取り出してシミュレーションを実行する
        return [self._one_set_simulation(chunk) 
                    for chunk in _poisson_s.reshape(-1, self.parm["set_of_cycles"])]
