"""
AOC 2022 day25 -
    [ https://adventofcode.com/2022/day/25 ]
    - pt1: 20=02=120-=-2110-0=1
    - pt2: Merry Christmas! 🎄 (no part2)
    - lessons: --
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)

snafu = {
    '=': -2,
    '-': -1,
    '0': 0,
    '1': 1,
    '2': 2
}


def read_file(file_path: str) -> list[str]:
    with open(file_path, mode="r+", encoding="utf-8") as file:
        codes = [line.rstrip('\n') for line in file]
    return codes


def part1(codes: list[str]) -> None:
    """ part 1 solution """
    sum_snafu = ""

    # get sum_dec
    dec_nums = []
    sum_dec = 0
    for num in codes:
        temp = 0
        for idx, val in enumerate(reversed(num)):
            temp += snafu[val] * (5**idx)
        dec_nums.append(temp)
        sum_dec += temp

    # sum_dec to sum_snafu (building from right to left)
    prev_remain = 0
    while sum_dec != 0 or prev_remain:
        curr_remain = sum_dec % 5 + prev_remain
        sum_snafu = {0: "0", 1: "1", 2: "2", 3: "=", 4: "-", 5: "0"}[curr_remain] + sum_snafu
        sum_dec //= 5
        # if negative vakue was added, then carry 1 remainder to the next pentagonal place (g5^n)
        if curr_remain > 2:
            prev_remain = 1
        else:
            prev_remain = 0

    print(f"#{f'  {cur_day} part1 answer is: {sum_snafu}': <48}#")



def main():
    """ day25 main """
    codes = read_file(input_path)
    part1(codes)
    print(f"#{f'  {cur_day} part2 answer is: Merry Christmas! 🎄': <47}#")
    print("#"*50)
