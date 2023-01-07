"""
AOC 2022 day17 - Pyroclastic Flow
    [ https://adventofcode.com/2022/day/17 ]
    - pt1:
    - pt2:
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')    # using \ as 1st char in str represents absoulte path (all before it wouldl be discarded)
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path: str) -> list[str]:
    """ parse input txt character-by-character into wind gust directions """
    gusts = []
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]
        for line in contents:
            for cmd in line:
                gusts.append(cmd)
    return gusts


def move_left(stone):
    if any([x == 0] for (x, y) in stone):
        return stone
    return set([x-1, y] for (x, y) in stone)


def move_right(stone):
    if any([x > 0] for (x, y) in stone):
        return stone
    return set([x+1, y] for (x, y) in stone)


def move_down(stone):
    return set([x, y-1] for (x, y) in stone)


def part1(gusts: list[str]) -> None:
    """ part 1 solution """
    for turn in range(2022):
        print(turn)
    print(f"#{f'  {cur_day} part1 answer is: {0}': <48}#")


def part2(txt: list[str]) -> None:
    """ part 2 solution """
    print(f"#{f'  {cur_day} part2 answer is: {0}': <48}#")


def main():
    """ day17 main """
    gusts = read_file(input_path)
    print(',,,,,',gusts)
    #part1(gusts)
    #part2(map2)
    print("#"*50)
