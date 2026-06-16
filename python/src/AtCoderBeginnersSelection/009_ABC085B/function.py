#!/usr/bin/env python
# coding:utf-8

# 検索対象の単語
SEARCHWORD = ['dream', 'dreamer', 'erase', 'eraser']
reSEARCHWORD = [x[::-1] for x in SEARCHWORD]


def daydream(string):
    restring = string[::-1]
    ans = _replaceList(restring, reSEARCHWORD)
    return "YES" if ans else "NO"


def _replaceList(string: str, words: list[str]) -> bool:
    return any([_replaceAndString(string, w) for w in words])


def _replaceAndString(string: str, word: str):
    """ 再帰的に置換可能かを検索する """
    # 置換できる文字列で始まっている場合は再起的に検索する
    if string.startswith(word):
        restring = string.replace(word, '', 1)
        # 全て置換できる場合はTRUE
        if (restring == ''):
            return True
        else:
            return any([_replaceAndString(restring, w) for w in reSEARCHWORD])
    return False


def _run():
    print("run")
    print(daydream("erasedream"))
    # print(daydream("dreameraser"))
    # print(daydream("dreamerer"))


if __name__ == "__main__":
    _run()
