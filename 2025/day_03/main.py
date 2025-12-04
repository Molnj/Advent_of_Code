# https://adventofcode.com/2025/day/3

import sys


def parse_input(path: str) -> int:
    with open(path) as f:
        return [line.strip() for line in f if line.strip()]


def biggest_n_digit_subsequence(line: str, digits: int) -> int:
    nums = [int(c) for c in line.strip()]
    to_remove = len(nums) - digits  # count of how many digits we need to drop still
    chosen = []

    for n in nums:
        while to_remove > 0 and chosen and chosen[-1] < n:
            chosen.pop()
            to_remove -= 1
        chosen.append(n)

    chosen = chosen[:digits]  # final trim to ensure n digits
    return int("".join(map(str, chosen)))


def part1(data: str) -> int:
    return sum(biggest_n_digit_subsequence(line, 2) for line in data)


def part2(data: str) -> int:
   return sum(biggest_n_digit_subsequence(line, 12) for line in data)


def main(path: str):
    data = parse_input(path)
    print(f"Part 1: {part1(data)}")
    print(f"Part 2: {part2(data)}")


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else "input.txt")

