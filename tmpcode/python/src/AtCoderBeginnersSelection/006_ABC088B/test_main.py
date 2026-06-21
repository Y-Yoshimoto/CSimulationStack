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
    {'in': [3, 1], 'out': 2},
    {'in': [2, 7, 4], 'out': 5},
    {'in': [20, 18, 2, 18], 'out': 18}
]


class RunTest(unittest.TestCase):
    """TestAddMethodsクラスは、addメソッドをテストするためのテストケースを適用する"""

    def test_006_ABC088B_1(self):
        for t in [TestPattern(pattern) for pattern in TESTPATTERN]:
            assert f.card_game_for_two(t.input) == t.output


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
