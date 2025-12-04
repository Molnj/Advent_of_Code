# https://adventofcode.com/2025/day/4
import sys

NEIGHBORS = [(-1,-1), (0,-1), (1,-1),
             (-1, 0),         (1, 0),
             (-1, 1), (0, 1), (1, 1)]


def parse_input(path: str) -> list[list[str]]:
    with open(path) as f:
        return [list(line.strip()) for line in f if line.strip()]


def count_accessible(matrix: list[list[str]]) -> (int,int):
    rows, cols = len(matrix), len(matrix[0]) 
    accessibles = []
    for y in range(rows):
        for x in range (cols):
            if matrix[y][x] != '@':
                continue
            adjacent = 0
            for dx, dy in NEIGHBORS:
                nx, ny = x + dx, y + dy
                if 0 <= nx < cols and 0 <= ny < rows and matrix[ny][nx] == '@':
                    adjacent += 1
            if adjacent < 4:
                accessibles.append((x,y))
    return accessibles


def part1(matrix: list[list[str]]) -> int:
    return len(count_accessible(matrix))


def part2(matrix: list[list[str]]):
    matrix_copy = [row[:] for row in matrix]
    total_removed = 0
    while 1:
        accessibles = count_accessible(matrix_copy)
        if not accessibles:
            break
        total_removed += len(accessibles)
        for x,y in accessibles:
            matrix_copy[y][x] = '.'
    return total_removed


def main(path: str):
    matrix = parse_input(path)
    print(f"Part 1: {part1(matrix)}")
    print(f"Part 2: {part2(matrix)}")


if __name__ == "__main__":
    solve(sys.argv[1] if len(sys.argv) > 1 else "input.txt")

