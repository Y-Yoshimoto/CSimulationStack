#!/usr/bin/env python
# coding:utf-8

# ABC081B - Shift only
# https://atcoder.jp/contests/abs/tasks/abc081_b
# 標準入出力用共通モジュール
from iofunctions import readstdin_lines, split_space

import function as f


def main():
    inputs = readstdin_lines()
    inputNumbers = [int(x) for x in split_space(inputs[1])]
    print(f.shift_only(inputNumbers))
    # print(f._func(1, 1))


if __name__ == "__main__":
    main()
