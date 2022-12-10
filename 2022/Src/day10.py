import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'../txt_inputs/{cur_day}.txt')
input_path = os.path.abspath(os.path.realpath(input_path))


def read_file(file_path: str) -> list[str]:
    with open(file_path, "r+") as file:
        contents = [line.rstrip('\n') for line in file]
    return contents


def calc_sig_str(elapsed_cycles, x_reg):
    signal_strength = 0
    if elapsed_cycles % 40 == 20:
        signal_strength = elapsed_cycles * x_reg
        # print(f"{signal_strength} = {elapsed_cycles} * {x_reg}")
    return signal_strength


def calc_crt_pixel(elapsed_cycles: int, x_reg: int) -> str:
    pixel = ' '
    cur_row = (elapsed_cycles % 40) - 1
    if abs(cur_row - x_reg) <= 1:
        pixel = '█'
    if elapsed_cycles % 40 == 0:
        pixel = " \t#\n#\t"     # elapsed_cycles start at 1, so whitespace override is necessary at 40
    return pixel


def part1(instructions: list[str]) -> None:
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
    print(f"#\t{cur_day} part1 answer is: {signal_strength_sum}\t\t\t\t#")


def part2(instructions: list[str]) -> None:
    crt_screen = "#\t"
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
    print(f"#\t{cur_day} part2 answer is: 'FJUBULRZ'\t\t\t#")
    print(crt_screen[:-3])


def main():
    instructions = read_file(input_path)
    part1(instructions)
    part2(instructions)
    print("#################################################")
