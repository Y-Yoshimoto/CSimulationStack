#!/usr/bin/env python
# coding:utf-8

def _sum_three_number(a: int, b: int, c: int) -> int:
    return a + b + c

def sum_and_string(a: int, b: int, c: int, s: str) -> str:
    return f'{_sum_three_number(a, b, c)} {s}'

# 関数デバック用
def _run():
    print('run')
    print(_sum_three_number(1, 2, 3))

if __name__ == '__main__':
    _run()

