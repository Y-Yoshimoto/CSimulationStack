#!/usr/bin/env python
# coding:utf-8

def Otoshidama(N: int, Y: int) -> list[int]:
    # 全て一万円札でも足りない場合/1000未満の端数が含まれている場合は['-1, -1, -1']
    if ((Y > N * 10000) or Y % 1000 != 0):
        return ['-1, -1, -1']
    # 計算
    # 1000円単位に変換し(10, 5, 1)の組み合わせとする
    y, n = Y / 1000, N
    # 1万円の枚数毎に探索を行う。
    # 1万円が決まった時に5千円の枚数は一意に決定できる。
    # N - a = b + c   → N' = b + c
    # Y - 10a =5b + c → Y' = 5b + c
    # b = (Y' - N') / 4 : bが整数の時に正解の組み合わせ候補になる。
    # b = (Y - N -9a) / 4
    combination = [_culc_5_1(y - a*10, n-a, a)
                   for a in range(min(n, int(y/10)) + 1)]
    ans = [x for x in combination if x is not None]
    return ans if len(ans) != 0 else ['-1 -1 -1']


def _culc_5_1(y_: int, n_: int, a: int):
    """ 5000円/1000円の枚数を計算する """
    b = (y_ - n_) / 4
    c = n_ - b
    if (b.is_integer() and c.is_integer() and b >= 0 and c >= 0):
        return f'{a} {int(b)} {int(c)}'


def _run():
    print("run")
    print(Otoshidama(2000, 20000000))


if __name__ == "__main__":
    _run()
