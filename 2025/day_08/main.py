# https://adventofcode.com/2025/day/X
import sys


def parse_input(path: str):
    with open(path) as f:
        return [line.strip() for line in f if line.strip()]


def part1(data):
    # TODO: implement Part 1
    return None


def part2(data):
    # TODO: implement Part 2
    return None


def main(path: str):
    data = parse_input(path)
    print(f"Part 1: {part1(data)}")
    print(f"Part 2: {part2(data)}")


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else "input.txt")

