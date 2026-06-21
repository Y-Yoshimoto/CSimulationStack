#!/usr/bin/env python
# coding:utf-8

#
#
# 標準入出力用共通モジュール
from iofunctions import readstdin_lines, split_space, split_space_convert

import function as f


def main():
    input = readstdin_lines()
    print(input)
    # print(f._func(1, 1))


if __name__ == "__main__":
    main()
