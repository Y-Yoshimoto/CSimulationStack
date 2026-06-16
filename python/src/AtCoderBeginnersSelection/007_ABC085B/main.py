#!/usr/bin/env python
# coding:utf-8

# ABC085B - Kagami Mochi
# https://atcoder.jp/contests/abs/tasks/abc085_b
# 標準入出力用共通モジュール
from iofunctions import readstdin_lines, split_space, split_space_convert

import function as f


def main():
    disks = readstdin_lines()[1:]
    # print(disks)
    print(f.kagami_mochi(disks))


if __name__ == "__main__":
    main()
