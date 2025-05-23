"""
AOC 2022 day03 - Rucksack Reorganization
    [ https://adventofcode.com/2022/day/3 ]
    - pt1: 7872
    - pt2: 2497
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path: str) -> list[str]:
    """ parse input txt line-by-line into list of strings """
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = file.readlines()
    return contents


def get_char_priority(char: str) -> int:
    """ converting lower- and upper-case letters into ASCII value --> priority """
    if char.islower():
        return ord(char) - 96
    return ord(char) - 38


def part1(txt: list[str]) -> None:
    """ part 1 solution """
    priority_sum = 0
    for line in txt:
        comp1 = line[:len(line) // 2]
        comp2 = line[len(line) // 2:]
        # matching_char only finds 1st matching char, but shouldn't be more anyway
        matching_char = (str(set(comp1) & set(comp2)))[2]
        priority_sum += get_char_priority(matching_char)
    print(f"#{f'  {cur_day} part1 answer is: {priority_sum}': <48}#")


def part2(txt: list[str]) -> None:
    """ part 2 solution """
    priority_sum = 0
    list_of_lines = [line.strip() for line in txt]
    i = 0
    while i < len(list_of_lines):
        for char in list_of_lines[i]:
            if char in list_of_lines[i+1] and char in list_of_lines[i+2]:
                priority_sum += get_char_priority(char)
                break
        i += 3
    print(f"#{f'  {cur_day} part2 answer is: {priority_sum}': <48}#")


def main():
    """ day03 main """
    txt_file = read_file(input_path)
    part1(txt_file)
    part2(txt_file)
    print("#"*50)
