#!/usr/bin/env python
# coding:utf-8

# ABC088B - Card Game for Two
# https://atcoder.jp/contests/abs/tasks/abc088_b
# 標準入出力用共通モジュール
from iofunctions import readstdin_lines, split_space, split_space_convert

import function as f


def main():
    input = readstdin_lines()
    nums = split_space_convert(input[1])
    print(card_game_for_two(nums))
    # print(f._func(1, 1))


if __name__ == "__main__":
    main()
