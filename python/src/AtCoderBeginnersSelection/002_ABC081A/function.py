#!/usr/bin/env python
# coding:utf-8

def const_one_instring(three_trout: str) -> str:
    trout_list = [int(s) for s in list(three_trout)]
    return f'{sum(trout_list)}'


def _run():
    print("run")
    print(const_one_instring('101'))
    print(const_one_instring('000'))


if __name__ == "__main__":
    _run()
