#!/usr/bin/env python
# coding:utf-8
import unittest


# unittestの実行場所が同一ディレクトリの場合
# ImportErrorが発生するため絶対インポートに切り替える
try:
    from . import function as f
except ImportError:
    import function as f


# テストパターン
TESTPATTERN = [
    {'in': [2, 2, 2, 100], 'out': 2},
    {'in': [5, 1, 0, 150], 'out': 0},
    {'in': [30, 40, 50, 6000], 'out': 213},
]


class RunTest(unittest.TestCase):
    """TestAddMethodsクラスは、addメソッドをテストするためのテストケースを適用する"""

    def test_004_ABC087B_1(self):
        for t in [TestPattern(pattern) for pattern in TESTPATTERN]:
            assert f.coins(t.input[0], t.input[1],
                           t.input[2], t.input[3]) == t.output


class TestPattern:
    """ テストパターンクラス
    TestPatternクラスのコンストラクタ
    Args:
        pattern (dict): パターンの辞書。'in'キーと'out'キーを持つ

    Attributes:
        input: パターンの入力値
        output: パターンの出力値
    """

    def __init__(self, pattern: dict):

        self.input = pattern['in']
        self.output = pattern['out']


if __name__ == '__main__':
    unittest.main()
