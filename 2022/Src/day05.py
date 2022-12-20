"""
AOC 2022 day05 - Supply Stacks
    - pt1: FWNSHLDNZ
    - pt2: RNRGDNFQG
"""

import os

file_dir = os.path.dirname(os.path.realpath('__file__'))
file_name = os.path.join(file_dir, '../txt_inputs/day05.txt')
file_name = os.path.abspath(os.path.realpath(file_name))

STACK_NUM = 9


def read_file(file_path: str) -> list[str]:
    """ parse input txt line-by-line into list of strings """
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]     # readlines(), but without "\n"
    return contents


def create_stacks(lines: list[str]) -> list[list]:
    """
        :param lines: input txt lines in list[str] form
        :return: lists representing the stacks (at the start of the input txt)
    """
    stacks = [[] for _ in range(STACK_NUM)]
    i = 7
    while i >= 0:
        crates = lines[i][1::4]
        for cur, _ in enumerate(crates):
            if crates[cur] != " ":
                stacks[cur].append(crates[cur])
        i -= 1
    return stacks


def move_crates(lines: list[str], stacks: list[list], can_move_multiple) -> list[list]:
    """

    :param lines: commands containing how many crates to move (with origin and destination)
    :param stacks: list of lists representing the stacks (with current state)
    :param can_move_multiple: moving stack one-by-one or all of them together
    :return: the listflist] representation of the stacks in the newly reached state
    """
    i = 10
    while i < len(lines):
        lines[i] = lines[i].split()
        _num = int(lines[i][1])
        _from = int(lines[i][3]) - 1
        _to = int(lines[i][5]) - 1
        if can_move_multiple:
            crates = []
            for _ in range(_num):
                crates.append(stacks[_from].pop())
            for _ in range(_num):
                stacks[_to].append(crates.pop())
        else:
            for _ in range(_num):
                crate = stacks[_from].pop()
                stacks[_to].append(crate)
        i += 1
    return stacks


def get_top_crates(stacks: list[list]) -> str:
    """
    :param stacks: list[list] representetion of the stacks
    :return: list of the crates on top on each stack
    """
    top_str = ""
    for i in range(STACK_NUM):
        top_str += stacks[i].pop()
    return top_str


def part1(txt: list[str]) -> None:
    """ part 1 solution """
    lines = [line.strip() for line in txt]          # get iterable input
    stacks = create_stacks(lines)                   # create stacks
    move_crates(lines, stacks, False)               # move stack items
    result = get_top_crates(stacks)                 # get result (string of top item letters)
    print(f"#\tday05 part1 answer is: {result}\t\t\t#")


def part2(txt: list[str]) -> None:
    """ part 1 solution """
    lines = [line.strip() for line in txt]          # get iterable input
    stacks = create_stacks(lines)                   # create stacks
    move_crates(lines, stacks, True)                # move stack items
    result = get_top_crates(stacks)                 # get result (string of top item letters)
    print(f"#\tday05 part2 answer is: {result}\t\t\t#")


def main():
    """ day05 main """
    txt_file = read_file(file_name)
    part1(txt_file)
    part2(txt_file)
    print("#################################################")
