"""
AOC 2022 day24 -
    [ https://adventofcode.com/2022/day/24 ]
    - pt1:
    - pt2:
    - lessons:
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path: str) -> list[str]:
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]
    return contents


def part1() -> None:
    """ part 1 solution """
    val = 0
    print(f"#{f'  {cur_day} part1 answer is: {val}': <48}#")


def part2() -> None:
    """ part 2 solution """
    val = 0
    print(f"#{f'  {cur_day} part2 answer is: {val}': <48}#")


def main():
    """ day24 main """
    lines = read_file(input_path)
    part1()
    #part2()
    print("#"*50)
