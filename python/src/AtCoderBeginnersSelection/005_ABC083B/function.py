#!/usr/bin/env python
# coding:utf-8

def SomeSums(n: int, a: int, b: int) -> int:
    judge_func = _judgement_fit_c(a, b)
    numbers = [x for x in range(1, n + 1) if judge_func(_sumdigit(x))]
    return sum(numbers)


def _sumdigit(n: int) -> int:
    """ 与えられた整数の各桁の合計 """
    quotient, remainder = int(n / 10), int(n % 10)
    # print(f'n: {n} quotient:{quotient} remainder:{remainder}')
    return remainder + _sumdigit(quotient) if quotient != 0 else remainder


def _judgement_fit_c(a, b):
    """ 判定関数を返すクロージャ """
    def _func(m: int) -> bool:
        return m >= a and m <= b
    return _func


def _run():
    print("run")
    print(_sumdigit(100))
    print(SomeSums(20, 2, 5))
    print(SomeSums(10, 1, 2))
    print(SomeSums(100, 4, 16))


if __name__ == "__main__":
    _run()
