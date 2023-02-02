"""
AOC 2022 day06 - Tuning Trouble
    [ https://adventofcode.com/2022/day/6 ]
    - pt1: 1175
    - pt2: 3217
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.abspath(os.path.join(os.getcwd(), os.pardir))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path: str) -> list[str]:
    """ parse input txt line-by-line into list of strings """
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]     # readlines(), but without "\n"
    return contents


def part1(txt: list[str]) -> int:
    """ part 1 solution """
    row = [line.strip() for line in txt]          # get iterable input
    line = []
    for char in str(row):
        if char.isalpha():
            line.append(char)
    idx = 3
    while idx < (len(line)):
        sliding_window = {line[idx-3], line[idx-2], line[idx-1], line[idx]}
        if len(sliding_window) == 4:
            break
        idx += 1
    print(f"#{f'  {cur_day} part1 answer is: {idx+1}': <48}#")


def part2(txt: list[str]) -> None:
    """ part 1 solution """
    row = [line.strip() for line in txt]          # get iterable input
    line = []
    for char in str(row):
        if char.isalpha():
            line.append(char)
    idx = 13
    while idx < (len(line)):
        sliding_window = {line[idx - 13], line[idx - 12], line[idx - 11],
                          line[idx - 10], line[idx - 9], line[idx - 8],
                          line[idx - 7], line[idx - 6], line[idx - 5],
                          line[idx - 4], line[idx - 3], line[idx - 2],
                          line[idx - 1], line[idx]}
        if len(sliding_window) == 14:
            break
        idx += 1
    print(f"#{f'  {cur_day} part2 answer is: {idx+1}': <48}#")


def main():
    """ day06 main """
    txt_file = read_file(input_path)
    part1(txt_file)
    part2(txt_file)
    print("#"*50)
