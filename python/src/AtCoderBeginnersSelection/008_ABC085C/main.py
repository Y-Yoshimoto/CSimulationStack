#!/usr/bin/env python
# coding:utf-8

# ABC085C - Otoshidama
# https://atcoder.jp/contests/abs/tasks/abc085_c
# 標準入出力用共通モジュール
from iofunctions import readstdin_lines, split_space, split_space_convert

import function as f


def main():
    input = split_space_convert(readstdin_lines()[0])
    n, y = input[0], input[1]
    print(f'N: {n} Y: {y}')
    print(f.Otoshidama(n, y))


if __name__ == "__main__":
    main()
