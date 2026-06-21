# 実行環境確認用
import unittest

# unittestの実行場所が同一ディレクトリの場合
# ImportErrorが発生するため絶対インポートに切り替える
try:
    from . import function as f
except ImportError:
    import runtimecheck.function as f


class RunTest(unittest.TestCase):

    def test_runtimecheck(self):
        assert f.add(2, 3) == 5


if __name__ == "__main__":
    unittest.main()
