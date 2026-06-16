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
    {'in': [9, 45000], 'out': '4 0 5'},
    {'in': [20, 196000], 'out': '-1 -1 -1'},
    {'in': [1000, 1234000], 'out': '14 27 959'},
    {'in': [2000, 20000000], 'out': '2000 0 0'}
]


class RunTest(unittest.TestCase):
    """TestAddMethodsクラスは、addメソッドをテストするためのテストケースを適用する"""

    def test_008_ABC085C_1(self):
        for t in [TestPattern(pattern) for pattern in TESTPATTERN]:
            assert t.output in f.Otoshidama(t.input[0], t.input[1])


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
