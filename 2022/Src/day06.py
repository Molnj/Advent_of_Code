import os

file_dir = os.path.dirname(os.path.realpath('__file__'))
file_name = os.path.join(file_dir, '../2022/txt_inputs/day06.txt')
file_name = os.path.abspath(os.path.realpath(file_name))

stack_num = 9


def read_file(file_path: str) -> list[str]:
    with open(file_path, "r+") as file:
        contents = [line.rstrip('\n') for line in file]     # readlines(), but without "\n"
    return contents


def part1(txt: list[str]) -> int:
    row = [line.strip() for line in txt]          # get iterable input
    line = []
    for char in str(row):
        if char.isalpha():
            line.append(char)
    idx = 3
    while idx < (len(line)):
        sliding_window = {line[idx-3], line[idx-2], line[idx-1], line[idx]}
        if len(sliding_window) == 4:
            print(sliding_window)
            break
        idx += 1
    print(f"day06 part1 answer is: {idx+1}")


def part2(txt: list[str]) -> None:
    row = [line.strip() for line in txt]          # get iterable input
    line = []
    for char in str(row):
        if char.isalpha():
            line.append(char)
    idx = 13
    while idx < (len(line)):
        sliding_window = {line[idx - 13], line[idx - 12], line[idx - 11], line[idx - 10], line[idx - 9],
                          line[idx - 8], line[idx - 7], line[idx - 6], line[idx - 5], line[idx - 4],
                          line[idx - 3], line[idx - 2], line[idx - 1], line[idx]}
        if len(sliding_window) == 14:
            print(sliding_window)
            break
        idx += 1
    print(f"day06 part1 answer is: {idx+1}")


def main():
    txt_file = read_file(file_name)
    part1(txt_file)
    part2(txt_file)
    print("#################################")
