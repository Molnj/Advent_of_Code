"""
AOC 2022 day10 - Cathode-Ray Tube
    [ https://adventofcode.com/2022/day/10 ]
    - pt1: 13060
    - pt2: FJUBULRZ
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
        contents = [line.rstrip('\n') for line in file]
    return contents


def calc_sig_str(elapsed_cycles, x_reg):
    """ signal strength = elapsed_cycles * x_reg position"""
    signal_strength = 0
    if elapsed_cycles % 40 == 20:
        signal_strength = elapsed_cycles * x_reg
        # print(f"{signal_strength} = {elapsed_cycles} * {x_reg}")
    return signal_strength


def calc_crt_pixel(elapsed_cycles: int, x_reg: int) -> str:
    """ draw pixel if current pinter and crt pointer are intersecting, else pass """
    pixel = ' '
    cur_row = (elapsed_cycles % 40) - 1
    if abs(cur_row - x_reg) <= 1:
        pixel = '█'
    if elapsed_cycles % 40 == 0:
        # elapsed_cycles start at 1, so whitespace override is necessary at 40
        pixel = "    #\n#     "
    return pixel


def part1(instructions: list[str]) -> None:
    """ part 1 solution """
    signal_strength_sum = 0
    elapsed_cycles = 1
    x_reg = 1
    for instr in instructions:
        sig_str = 0
        sig_str += calc_sig_str(elapsed_cycles, x_reg)
        elapsed_cycles += 1
        if instr == "noop":
            pass
        else:
            sig_str += calc_sig_str(elapsed_cycles, x_reg)
            x_reg += int(instr.split(" ")[1])
            elapsed_cycles += 1
        signal_strength_sum += sig_str
    print(f"#{f'  {cur_day} part1 answer is: {signal_strength_sum}': <48}#")


def part2(instructions: list[str]) -> None:
    """ part 2 solution """
    crt_screen = "#     "
    elapsed_cycles = 1
    x_reg = 1
    for instr in instructions:
        crt_screen += calc_crt_pixel(elapsed_cycles, x_reg)
        elapsed_cycles += 1
        if instr == "noop":
            pass
        else:
            crt_screen += calc_crt_pixel(elapsed_cycles, x_reg)
            x_reg += int(instr.split(" ")[1])
            elapsed_cycles += 1
    print(f"#{f'  {cur_day} part2 answer is: FJUBULRZ': <48}#")
    print(crt_screen[:-7])  # the last 6 chars are remainders in a new line


def main():
    """ day10 main """
    instructions = read_file(input_path)
    part1(instructions)
    part2(instructions)
    print("#"*50)
