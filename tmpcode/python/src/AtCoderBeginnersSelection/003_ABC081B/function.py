#!/usr/bin/env python
# coding:utf-8

# 与えられた引数のリストがすべて偶数の時に割る2を続けて続けれれる回数を返す
def shift_only(nums: list[int]) -> int:
    # 全てが偶数かを判断
    isAllEven = all([n % 2 == 0 for n in nums])
    if not isAllEven:
        return 0
    return 1 + shift_only([int(n / 2) for n in nums])


def _run():
    print("run")
    # alist = [4, 4, 6, 10]
    alist = [8, 12, 40]
    print(shift_only(alist))


if __name__ == "__main__":
    _run()
