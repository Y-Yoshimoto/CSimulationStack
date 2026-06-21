#!/usr/bin/env python
# coding:utf-8

# ABC049C - 白昼夢(daydream)
# https://atcoder.jp/contests/abs/tasks/arc065_a
# 標準入出力用共通モジュール
from iofunctions import readstdin_lines, split_space, split_space_convert

import function as f


def main():
    input = readstdin_lines()
    print(input[0])
    print(f.daydream(input[0]))


if __name__ == "__main__":
    main()
