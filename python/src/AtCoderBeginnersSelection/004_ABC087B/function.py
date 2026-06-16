#!/usr/bin/env python
# coding:utf-8

import itertools


def coins(a: int, b: int, c: int, x: int) -> int:
    # 50円未満の金額が含まれていた場合, 合計値よりも指定金額が大きい場合は0
    if (not (x % 50 == 0)) or (_sumCoins(a, b, c) < x):
        return 0

    # 各硬貨の組み合わせの直積を計算
    p = itertools.product(range(a + 1), range(b + 1), range(c + 1))
    cmbination = [(_sumCoins(a, b, c), a, b, c)
                  for (a, b, c) in p if _sumCoins(a, b, c) == x]
    return len(list(cmbination))


def _sumCoins(a: int, b: int, c: int) -> int:
    return 50 * (10 * a + 2 * b + c)


def _run():
    print("run")
    print(coins(a=2, b=2, c=2, x=100))
    print(coins(a=30, b=40, c=50, x=6000))


if __name__ == "__main__":
    _run()
