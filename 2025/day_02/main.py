# https://adventofcode.com/2025/day/

import sys

def process_file(path):
    with open(path) as f:
        for line in f:
            pass
    return 0

def main(path_input):
    x = process_file(path_input)
    print(f"Part 1: ")
    print(f"Part 2: ")


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else "input.txt")

