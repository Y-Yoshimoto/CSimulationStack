import unittest

# unittestの実行場所が同一ディレクトリの場合
# ImportErrorが発生するため絶対インポートに切り替える
try:
    from . import function as f
except ImportError:
    import function as f


class TestPattern:
    def __init__(self, pattern: dict):
        self.input = pattern['in']
        self.output = pattern['out']


# テストパターン
TESTPATTERN = [
    {'in': [1, 2, 3, 'test'], 'out': '6 test'},
    {'in': [72, 128, 256, 'myonmyon'], 'out': '456 myonmyon'}
]


class RunTest(unittest.TestCase):
    def test_000_PracticeA_1(self):
        for t in [TestPattern(pattern) for pattern in TESTPATTERN]:
            assert f.sum_and_string(
                t.input[0], t.input[1], t.input[2], t.input[3]) == t.output


if __name__ == '__main__':
    unittest.main()
