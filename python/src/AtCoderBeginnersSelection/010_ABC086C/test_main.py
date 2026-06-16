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
    {'in': [[3, 1, 2], [6, 1, 1]], 'out': 'Yes'},
    {'in': [[2, 100, 100]], 'out': 'No'},
    {'in': [[5, 1, 1], [100, 1, 1]], 'out': 'No'},
]


class RunTest(unittest.TestCase):
    """TestAddMethodsクラスは、addメソッドをテストするためのテストケースを適用する"""

    def test_010_ABC086C_1(self):
        for t in [TestPattern(pattern) for pattern in TESTPATTERN]:
            assert f.traveling(t.input) == t.output


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
