#!/usr/bin/env python
# coding:utf-8

# PracticeA - Welcome to AtCoder
# https://atcoder.jp/contests/abs/tasks/practice_1
# 標準入出力用共通モジュール
from iofunctions import readstdin_lines, split_space

import function as f


def main():
    inputs = readstdin_lines()
    lineTwos = inputs[1].split(' ')
    numbers = [int(inputs[0]), int(lineTwos[0]), int(lineTwos[1])]

    print(f'{f.sum_and_string(numbers[0], numbers[1], numbers[2], inputs[2])}')


if __name__ == '__main__':
    main()
