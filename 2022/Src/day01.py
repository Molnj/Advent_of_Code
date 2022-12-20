"""
AOC 2022 day01 - Calorie Counting
    - pt1: 74198
    - pt2: 209914
"""

import os

file_dir = os.path.dirname(os.path.realpath('__file__'))
file_name = os.path.join(file_dir, '../txt_inputs/day01.txt')
file_name = os.path.abspath(os.path.realpath(file_name))


def read_file(file_path):
    """ parse input txt line-by-line into list of strings """
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = file.readlines()
    return contents


def part1():
    """ part 1 solution """
    max_kcal = 0
    curr_val = 0
    for line in read_file(file_name):
        line = line.strip()
        if len(line) != 0:
            curr_val += int(line)
        else:
            if curr_val > max_kcal:
                max_kcal = curr_val
            curr_val = 0
    print(f"#\tday01 part1 answer is: {max_kcal}\t\t\t\t#")


def part2():
    """ part 2 solution """
    kcal_list = []
    curr_val = 0
    for line in read_file(file_name):
        line = line.strip()
        if len(line) != 0:
            curr_val += int(line)
        else:
            kcal_list.append(curr_val)
            curr_val = 0
    top3_sum = sum(sorted(kcal_list, reverse=True)[:3])
    print(f"#\tday01 part2 answer is: {top3_sum}\t\t\t\t#")


def main():
    """ day01 main """
    part1()
    part2()
    print("#################################################")
