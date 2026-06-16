#!/usr/bin/env python
# coding:utf-8

def is_oddeven_product(a, b):
    """
    2つの整数の積が奇数か偶数かを判定する関数

    Parameters:
    a (int): 1つ目の整数
    b (int): 2つ目の整数

    Returns:
    str: 'Even'（偶数）または 'Odd'（奇数）
    """
    return 'Even' if ((a * b) % 2 == 0) else 'Odd'


def _run():
    print("run")
    print(is_oddeven_product(1, 2))
    print(is_oddeven_product(3, 5))


if __name__ == "__main__":
    _run()
