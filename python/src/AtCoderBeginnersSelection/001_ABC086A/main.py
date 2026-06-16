#!/usr/bin/env python
# coding:utf-8

# ABC086A - Product
# https://atcoder.jp/contests/abs/tasks/abc086_a
# 標準入出力用共通モジュール
from iofunctions import readstdin_lines, split_space

import function as f


def main():
    inputs = split_space(readstdin_lines()[0])
    a, b = int(inputs[0]), int(inputs[1])
    print(f.is_oddeven_product(a, b))


if __name__ == "__main__":
    main()
