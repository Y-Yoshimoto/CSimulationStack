#!/usr/bin/env python
# coding:utf-8
class PlanObject:
    """ プラン座標クラス """

    def __init__(self, planList: list[int]) -> None:
        self.t = planList[0]
        self.x = planList[1]
        self.y = planList[2]


def traveling(travelplan: list[list[int]]) -> str:
    plans = [PlanObject(p) for p in [[0, 0, 0]] + travelplan]
    return 'Yes' if checkPairwiseCondition(plans, movementJudgment) else "No"


def checkPairwiseCondition(plans, func):
    """ リストから二つづつ取り出しfuncの評価がTreuなら次を評価する """
    if (len(plans) == 1):
        return True
    return checkPairwiseCondition(plans[1:], func) if func(plans[0], plans[1]) else False


def movementJudgment(s: PlanObject, e: PlanObject) -> bool:
    """ 2点間の移動が可能か否かを評価する(偶奇性/移動距離を満たしているか) """
    dt, dx, dy = e.t - s.t, abs(e.x - s.x), abs(e.y - s.y)
    # print(f'dt: {dt}, dx: {dx}, dy: {dy}')
    l = dx + dy
    return (dt % 2 == l % 2) and (l <= dt)


def _run():
    print("run")
    print(traveling([[3, 1, 2], [6, 1, 1]]))
    print(traveling([[2, 100, 100]]))
    print(traveling([[5, 1, 1], [100, 1, 1]]))


if __name__ == "__main__":
    _run()
