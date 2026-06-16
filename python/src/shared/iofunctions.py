#!/usr/bin/env python
# coding:utf-8
# 標準入出力関連関数モジュール

import sys

# 標準出力読み取り


def readstdin_lines() -> list:
    """
    標準入力から行を読み取り、行毎の文字列のリストとして返す
    Returns:
        list: 読み取られた行のリスト
    """
    print("Input and Ctrl+D.")
    print("Start ----------------")
    # 入力を改行毎にリストに分割して改行コードをなくした文字列リストを返す
    input_lines = [s.replace('\n', '') for s in sys.stdin.readlines()]
    print("End  -----------------\n")
    return input_lines

# 文字列の半角スペース分割


def split_space(string: str) -> list:
    """
    文字列をスペースで分割する関数

    Args:
        string (str): 分割する文字列

    Returns:
        list: スペースで分割された文字列のリスト
    """
    return string.split(' ')


def split_space_convert(string: str, convert=int) -> list:
    """
    文字列をスペースで分割しint変換する

    Args:
        string (str): 分割する文字列

    Returns:
        list: スペースで分割された文字列のリスト
    """
    return [convert(x) for x in split_space(string)]
