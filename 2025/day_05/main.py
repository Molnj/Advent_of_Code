# https://adventofcode.com/2025/day/X
import sys


def parse_input(path: str):
    with open(path) as f:
        parts = f.read().strip().split("\n\n")
    ranges = [tuple(map(int, line.split('-'))) fpr line in parts[0].splitlines()]
    ids = [int(x) for x in parts[1].splitlines()]
    return ranges, ids


def count_fresh(ranges, ids):
    cnt = 0
    for i in ids:
        for low, high in ranges:
            if low <= i <= high:
                cnt += 1
                break
    return cnt



def part1(ranges, ids):
    cnt_fresh = count_fresh(ranges, ids)
    return cnt_frest


def part2(ranges, ids):
    # TODO: implement Part 2
    return None


def main(path: str):
    ranges, ids = parse_input(path)
    print(f"Part 1: {part1(ranges, ids)}")
    print(f"Part 2: {part2(ranges, ids)}")


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else "input.txt")

