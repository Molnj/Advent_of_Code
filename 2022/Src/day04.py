import os

file_dir = os.path.dirname(os.path.realpath('__file__'))
file_name = os.path.join(file_dir, '../txt_inputs/day04.txt')
file_name = os.path.abspath(os.path.realpath(file_name))


def read_file(file_path: str) -> list[str]:
    with open(file_path, "r+") as file:
        contents = [line.rstrip('\n') for line in file]     # readlines(), but without "\n"
    return contents


def expand_section(sect: str) -> set:
    full_section = set()
    start, end = sect.split("-")
    start = int(start)
    end = int(end)
    while start <= end:
        full_section.add(start)
        start += 1
    return full_section


def part1(txt: list[str]) -> None:
    subset_cnt = 0
    for line in txt:
        section1, section2 = line.split(",")
        section1 = expand_section(section1)
        section2 = expand_section(section2)
        if section1.issubset(section2) or section2.issubset(section1):
            subset_cnt += 1
    print(f"#\tday04 part1 answer is: {subset_cnt}\t\t\t#")


def part2(txt: list[str]) -> None:
    intersection_cnt = 0
    for line in txt:
        section1, section2 = line.split(",")
        section1 = expand_section(section1)
        section2 = expand_section(section2)
        if bool(section1 & section2):
            intersection_cnt += 1
    print(f"#\tday04 part2 answer is: {intersection_cnt}\t\t\t#")


def main():
    txt_file = read_file(file_name)
    part1(txt_file)
    part2(txt_file)
    print("#########################################")
