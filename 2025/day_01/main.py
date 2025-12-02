# https://adventofcode.com/2025/day/1

import sys

class CircularEncoder:
    def __init__(self, value=0, value_max=99):
        self.value = value
        self.value_max = value_max
        self.crossings = 0
        self.landings = 0

    def turn(self, command: str):
        direction = 1 if command[0].upper() == "R" else -1
        steps = int(command[1:])
        limit = self.value_max + 1

        old = self.value
        self.value = (old + direction * steps) % limit

        # part 1: landing on 0
        if self.value == 0:
            self.landings += 1

        # part 2: moving over 0
        self.crossings += abs((old + direction * steps) // limit) 
        if (direction == -1) and (old == 0): self.crossings -= 1
        if (direction == -1) and (self.value == 0): self.crossings += 1

        return f"Encoder pos={self.value:02d}, lands={self.landings}, crosses={self.crossings}"


def process_file(path) -> CircularEncoder:
    enc = CircularEncoder(50)
    with open(path) as f:
        for line in f:
            cmd = line.strip()
            if cmd:
                enc.turn(cmd)
    return enc


def main(path_input):
    encoder = process_file(path_input)
    print(f"Part 1: {encoder.landings}")
    print(f"Part 2: {encoder.crossings}")


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else "input.txt")

