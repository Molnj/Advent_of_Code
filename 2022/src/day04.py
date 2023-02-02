"""
AOC 2022 day04 - Camp Cleanup
    [ https://adventofcode.com/2022/day/4 ]
    - pt1: 547
    - pt2: 843
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


def expand_section(sect: str) -> set:
    """
        :param sect: e.g.: "3-7"
        :return: e.g.: [3, 4, 5, 6, 7]
    """
    full_section = set()
    start, end = sect.split("-")
    start = int(start)
    end = int(end)
    while start <= end:
        full_section.add(start)
        start += 1
    return full_section


def part1(txt: list[str]) -> None:
    """ part 1 solution """
    subset_cnt = 0
    for line in txt:
        section1, section2 = line.split(",")
        section1 = expand_section(section1)
        section2 = expand_section(section2)
        if section1.issubset(section2) or section2.issubset(section1):
            subset_cnt += 1
    print(f"#{f'  {cur_day} part1 answer is: {subset_cnt}': <48}#")


def part2(txt: list[str]) -> None:
    """ part 1 solution """
    intersection_cnt = 0
    for line in txt:
        section1, section2 = line.split(",")
        section1 = expand_section(section1)
        section2 = expand_section(section2)
        if bool(section1 & section2):
            intersection_cnt += 1
    print(f"#{f'  {cur_day} part2 answer is: {intersection_cnt}': <48}#")


def main():
    """ day04 main """
    txt_file = read_file(input_path)
    part1(txt_file)
    part2(txt_file)
    print("#"*50)
