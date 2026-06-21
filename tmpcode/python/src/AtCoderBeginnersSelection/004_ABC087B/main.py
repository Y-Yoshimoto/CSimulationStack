#!/usr/bin/env python
# coding:utf-8

##
##
# 標準入出力用共通モジュール
from iofunctions import readstdin_lines, split_space, split_space_convert

import function as f


def main():
    input = [int(x) for x in readstdin_lines()]
    print(input)
    print(f.coins(a=input[0], b=input[1], c=input[2], x=input[3]))


if __name__ == "__main__":
    main()
