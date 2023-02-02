"""
AOC 2022 day13 - Distress Signal
    [ https://adventofcode.com/2022/day/13 ]
    - pt1: 6369
    - pt2: 25800
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.abspath(os.path.join(os.getcwd(), os.pardir))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path: str) -> list[list[int]]:
    """ parse input list pairs """
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]
        pairs = []
        temp = []
        for line in contents:
            if line == "":
                pairs.append(temp)
                temp = []
            else:
                temp.append(eval(line))
    return pairs


def compare(left: int, right: int) -> str:
    """ comparison between two lists """
    if isinstance(left, int) and isinstance(right, int):
        if left < right:
            return "ordered"
        if left > right:
            return "unordered"
        return "equal"
    if isinstance(left, list) and isinstance(right, int):
        return compare(left, [right])
    if isinstance(left, int) and isinstance(right, list):
        return compare([left], right)
    if isinstance(left, list) and isinstance(right, list):
        i = 0
        while i < len(left) and i < len(right):
            comp = compare(left[i], right[i])
            if comp in ("ordered", "unordered"):
                return comp
            i += 1
        if i == len(left) and len(left) < len(right):
            return "ordered"
        if i == len(right) and len(right) < len(left):
            return "unordered"


def bubble_sort(arr: list[list[int]]) -> list[list[int]]:
    """ bubble sort (should be quick) """
    new_arr = []
    while len(arr) > 1:
        temp = [arr[0]]
        i = 1
        while i < len(arr):
            # print(f"{temp[0]} ---- {arr[i]}")
            comp = compare(temp[0], arr[i])
            if comp == "unordered":
                temp[0] = arr[i]
            i += 1
        new_arr.append(temp[0])
        arr.remove(temp[0])
    new_arr.append(arr[0])  # appending last element from array
    return new_arr


def part1(pairs: list[list[int]]) -> None:
    """ part 1 solution """
    index_sum = 0
    for idx, pair in enumerate(pairs):
        if compare(pair[0], pair[1]) == "ordered":
            index_sum += (idx + 1)
    print(f"#{f'  {cur_day} part1 answer is: {index_sum}': <48}#")


def part2(pairs: list[list[int]]) -> None:
    """ part 2 solution """
    distress_signal = 1
    items = [[[2]], [[6]]]
    for pair in pairs:
        items.append(pair[0])
        items.append(pair[1])
    items = bubble_sort(items)  # should be quick sort, but it's getting late
    for idx, i in enumerate(items):
        # print(idx+1, i)
        if i == [[2]]:
            distress_signal *= (idx+1)
        if i == [[6]]:
            distress_signal *= (idx+1)
    print(f"#{f'  {cur_day} part2 answer is: {distress_signal}': <48}#")


def main():
    """ day 13 main"""
    pairs = read_file(input_path)
    part1(pairs)
    part2(pairs)
    print("#"*50)
