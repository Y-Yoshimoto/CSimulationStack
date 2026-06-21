#!/usr/bin/env python
# coding:utf-8

def kagami_mochi(list: list[int]) -> int:
    return len(set(list))


def _run():
    print("run")
    print(kagami_mochi([10, 8, 8, 6]))
    print(kagami_mochi([15, 15, 15]))
    print(kagami_mochi([50, 30, 50, 100, 50, 80, 30]))


if __name__ == "__main__":
    _run()
