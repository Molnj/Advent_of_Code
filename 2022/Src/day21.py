"""
AOC 2022 day21 - Monkey Math
    [ https://adventofcode.com/2022/day/21 ]
    - pt1: 21208142603224
    - pt2: 3882224466191
    - lessons:
        - don't assume things, that are not explicitly specified
          (all divisions will be integers)
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path: str) -> list[tuple[str, str]]:
    monkeys = []
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]
    for line in contents:
        name, equation = line.split(": ")
        monkeys.append((name, equation))
    return monkeys


def part1(monkeys: list[tuple[str, str]]) -> None:
    """ part 1 solution """
    solution = 0
    monkeys = monkeys.copy()
    sub_solutions = {}

    # get all integer monkeys (+ remove them from monkeys)
    idx = 0
    while idx < len(monkeys):
        name, equation = monkeys[idx]
        try:
            sub_solutions[name] = int(equation)
            monkeys.pop(idx)
            idx -= 1
        except ValueError:
            pass
        idx += 1

    while monkeys:
        idx = 0
        while idx < len(monkeys):
            name, equation = monkeys[idx]
            try:
                first, operation, second = equation.split(" ")
                if operation == "+":
                    val = sub_solutions[first] + sub_solutions[second]
                    sub_solutions[name] = val
                if operation == "-":
                    val = sub_solutions[first] - sub_solutions[second]
                    sub_solutions[name] = val
                if operation == "*":
                    val = sub_solutions[first] * sub_solutions[second]
                    sub_solutions[name] = val
                if operation == "/":
                    val = sub_solutions[first] / sub_solutions[second]
                    sub_solutions[name] = int(val)
                monkeys.pop(idx)
                idx -= 1
            except KeyError:
                pass
            idx += 1

    solution = sub_solutions["root"]
    print(f"#{f'  {cur_day} part1 answer is: {solution}': <48}#")


def part2(monkiz, min: int, max: int) -> None:
    """ part 2 solution """
    # all monkey names seem to appear in the input twice (except "root")
    # once as they get evaluated, once as they get assigned
    # that means only one side will depend one "humn" and even linearly
    # thus binary search is applicable to the solution
    solution = 0
    monkeys = monkiz.copy()
    sub_solutions = {}
    mid = int((max+min)//2)

    # get all integer monkeys (+ remove them from monkeys)
    idx = 0
    while idx < len(monkeys):
        name, expression = monkeys[idx]
        if name == "humn":
            expression = mid
        try:
            sub_solutions[name] = int(expression)
            monkeys.pop(idx)
            idx -= 1
        except ValueError:
            pass
        idx += 1

    while monkeys:
        idx = 0
        while idx < len(monkeys):
            name, equation = monkeys[idx]
            try:
                first, operation, second = equation.split(" ")
                if operation == "+":
                    val = sub_solutions[first] + sub_solutions[second]
                    sub_solutions[name] = val
                if operation == "-":
                    val = sub_solutions[first] - sub_solutions[second]
                    sub_solutions[name] = val
                if operation == "*":
                    val = sub_solutions[first] * sub_solutions[second]
                    sub_solutions[name] = val
                if operation == "/":
                    val = sub_solutions[first] / sub_solutions[second]
                    sub_solutions[name] = int(val)
                monkeys.pop(idx)
                idx -= 1
                # finishing up evaluation of root
                if len(monkeys) == 0:
                    if sub_solutions[first] < sub_solutions[second]:
                        part2(monkiz, min, mid)
                    if sub_solutions[first] > sub_solutions[second]:
                        part2(monkiz, mid, max)
                    else:
                        solution = sub_solutions["humn"]
                        print(f"#{f'  {cur_day} part2 answer is: {solution}': <48}#")
                        exit()
            except KeyError:
                pass
            idx += 1
    return -1


def main():
    """ day21 main """
    monkeys = read_file(input_path)
    part1(monkeys)
    part2(monkeys, 0, 3882224466192)
    print("#"*50)
