#!/usr/bin/env python
# coding:utf-8

def card_game_for_two(nums: list[int]) -> int:
    # 交互に反転する関数
    pm = _plue_minus_c()
    return sum([pm(x) for x in sorted(nums, reverse=True)])


def _plue_minus_c():
    """# 呼び出す度に+/-を入れ替えて値を返すクロージャ"""
    plueef = False

    def _func(n):
        nonlocal plueef
        plueef = not plueef
        return n if plueef else -n
    return _func


def _run():
    print("run")
    print(card_game_for_two([3, 1]))
    print(card_game_for_two([2, 7, 4]))


if __name__ == "__main__":
    _run()
