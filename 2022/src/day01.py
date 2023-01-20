"""
AOC 2022 day01 - Calorie Counting
    [ https://adventofcode.com/2022/day/1 ]
    - pt1: 74198
    - pt2: 209914
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')    # using \ as 1st char in str represents absoulte path (all before it wouldl be discarded)
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path):
    """ parse input txt line-by-line into list of strings """
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = file.readlines()
    return contents


def part1(input: str):
    """ part 1 solution """
    max_kcal = 0
    curr_val = 0
    for line in input:
        line = line.strip()
        if len(line) != 0:
            curr_val += int(line)
        else:
            if curr_val > max_kcal:
                max_kcal = curr_val
            curr_val = 0
    print(f"#{f'  {cur_day} part1 answer is: {max_kcal}': <48}#")


def part2(input: str):
    """ part 2 solution """
    kcal_list = []
    curr_val = 0
    for line in input:
        line = line.strip()
        if len(line) != 0:
            curr_val += int(line)
        else:
            kcal_list.append(curr_val)
            curr_val = 0
    top3_sum = sum(sorted(kcal_list, reverse=True)[:3])
    print(f"#{f'  {cur_day} part2 answer is: {top3_sum}': <48}#")


def main():
    """ day01 main """
    input = read_file(input_path)
    part1(input)
    part2(input)
    print("#"*50)
