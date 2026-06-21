#!/usr/bin/env python
# coding:utf-8

# ABC086C - Traveling
# https://atcoder.jp/contests/abs/tasks/arc089_a
# 標準入出力用共通モジュール
from iofunctions import readstdin_lines, split_space, split_space_convert

import function as f


def main():
    travelplan = [split_space_convert(x) for x in readstdin_lines()[1:]]
    print(travelplan)
    print(f.traveling(travelplan))


if __name__ == "__main__":
    main()
