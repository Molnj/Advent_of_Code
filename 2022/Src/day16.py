"""
AOC 2022 day16 - Proboscidea Volcanium
    [ https://adventofcode.com/2022/day/16 ]
    - pt1:
    - pt2:
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')    # using \ as 1st char in str represents absoulte path (all before it wouldl be discarded)
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path: str) -> list(dict):
    """ parse input txt file """
    adjacencies = []
    flow_rates = {}
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]
        for line in contents:
            print(line.split())


def part1() -> None:
    """ part 1 solution """
    val = 0
    minutes = 30
    print(f"#{f'  {cur_day} part1 answer is: {val}': <48}#") 

def part2() -> None:
    """ part 2 solution """
    val = 0
    print(f"#{f'  {cur_day} part2 answer is: {val}': <48}#")


def main():
    """ day16 main """
    lines = read_file(input_path)
    part1()
    #part2()
    print("#"*50)

main()