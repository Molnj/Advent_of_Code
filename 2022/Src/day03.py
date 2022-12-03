import os

file_dir = os.path.dirname(os.path.realpath('__file__'))
file_name = os.path.join(file_dir, '../2022/txt_inputs/day03.txt')
file_name = os.path.abspath(os.path.realpath(file_name))


def read_file(file_path: str) -> list[str]:
    with open(file_path, "r+") as file:
        contents = file.readlines()
    return contents


def get_char_priority(char: str) -> int:
    if char.islower():
        return ord(char) - 96
    else:
        return ord(char) - 38


def part1(txt: list[str]) -> None:
    priority_sum = 0
    for line in txt:
        comp1 = line[:len(line) // 2]
        comp2 = line[len(line) // 2:]
        matching_char = (str(set(comp1) & set(comp2)))[2]   # only finds 1st matching char, but shouldn't be more anyway
        priority_sum += get_char_priority(matching_char)
    print(f"day03 part1 answer is: {priority_sum}")


def part2(txt: list[str]) -> None:
    priority_sum = 0
    list_of_lines = [line.strip() for line in txt]
    i = 0
    while i < len(list_of_lines):
        for char in list_of_lines[i]:
            if char in list_of_lines[i+1] and char in list_of_lines[i+2]:
                priority_sum += get_char_priority(char)
                break
        i += 3
    print(f"day03 part2 answer is: {priority_sum}")


def main():
    txt_file = read_file(file_name)
    part1(txt_file)
    part2(txt_file)
    print("#################################")
