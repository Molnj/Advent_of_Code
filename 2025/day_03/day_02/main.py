# https://adventofcode.com/2025/day/2

import sys

def process_file(path: str):
    with open(path) as f:
        for line in f:
            endpoints = [tuple(map(int, _range.split("-"))) for _range in line.split(",")]
    return endpoints


def solve(line: str, part: int = 1) -> int:
    """Sum of all invalid IDs in all ranges."""
    invalid_check = is_invalid_id_part1 if part == 1 else is_invalid_id_part2
    total = 0
    for start, end in process_file(line):
        for n in range(start, end + 1):
            if invalid_check(n):
                total += n
    return total


def is_invalid_id_part1(n: int) -> bool:
    """Invalid if the number is made of some substring repeated *exactly twice*."""
    s = str(n)
    if len(s) % 2 != 0:
        return False
    half = len(s) // 2
    return s[:half] == s[half:]


def is_invalid_id_part2(n: int) -> bool:
    """Invalid if the number is made of some substring repeated *2 or more times*."""
    s = str(n)
    l = len(s)
    for size in range(1, (l // 2) + 1):
        if l % size == 0:
            if s == s[:size] * (l // size):
                return True
    return False


def main(path_input: str):
    print(f"Part 1: {solve(path_input, 1)}")
    print(f"Part 2: {solve(path_input, 2)}")


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else "input.txt")

