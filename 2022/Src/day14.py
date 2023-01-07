"""
AOC 2022 day14 - Regolith Reservoir
    [ https://adventofcode.com/2022/day/14 ]
    - pt1: 795
    - pt2: 30214
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)

sand_source = [500, 0]


def read_file(file_path: str) -> list[list[tuple]]:
    """ parse input 2D side view of chamber (for sand simulation) """
    area = []
    with open(file_path, mode="r+", encoding="utf-8") as file:
        for line in file:
            row = []
            corners = line.split(" -> ")
            for corner in corners:
                x_pos, y_pos = corner.split(",")
                row.append([int(x_pos), int(y_pos)])
            area.append(row)

    # convert cave to smaller size
    min_x = 0
    for line in area:
        for i in line:
            if min_x > i[0] or min_x == 0:
                min_x = i[0]
    for line in area:
        for i in line:
            i[0] = i[0] - min_x
    sand_source[0] = sand_source[0] - min_x
    return area


def get_cave(coords: list[list[tuple]]) -> list[list[str]]:
    """ creating cave layout from platform corner coorinates (2D side view)"""
    cave = []
    width, height, = 0, 0
    for line in coords:
        for cord in line:
            if width < cord[0]:
                width = cord[0] + 2    # idk why not 1
            if height < cord[1]:
                height = cord[1] + 1

    for _ in range(height):
        line = []
        for __ in range(width):
            line.append('.')
        cave.append(line)

    for line in coords:
        for idx, pixel in enumerate(line):
            cave[pixel[1]][pixel[0]] = '#'
            if idx+1 < len(line):
                if line[idx][0] == line[idx+1][0]:
                    while line[idx][1] < line[idx+1][1]:
                        line[idx][1] += 1
                        cave[pixel[1]][pixel[0]] = '#'
                    while line[idx][1] > line[idx+1][1]:
                        line[idx][1] -= 1
                        cave[pixel[1]][pixel[0]] = '#'
                if line[idx][1] == line[idx+1][1]:
                    while line[idx][0] < line[idx+1][0]:
                        line[idx][0] += 1
                        cave[pixel[1]][pixel[0]] = '#'
                    while line[idx][0] > line[idx+1][0]:
                        line[idx][0] -= 1
                        cave[pixel[1]][pixel[0]] = '#'
    return cave


def expand_cave(cave: list[list[str]]) -> list[list[str]]:
    """ making cave size 3× in height and width --> infinite in function"""
    for row in cave:
        for _ in range(len(cave)):
            row.insert(0, '.')
            # LL - originally .insert(-1, '.') - moved 1 platform pixel to the very right (30214+19)
            row.append('.')
        sand_source[0] += 1

    original_cave_width = len(cave[0])
    cave.append(['.'] * original_cave_width)
    cave.append(['#'] * original_cave_width)
    return cave


def simulate_sand_flow(cave: list[list[str]]) -> list[list[str]]:
    """ simulating sand movement: straight down, left-down, right-down, or stop"""
    sand_cord = sand_source.copy()
    while True:
        sand_cord[1] += 1
        if cave[sand_source[1]][sand_source[0]] != '.':
            break
        if sand_cord[1] >= len(cave):
            break
        # print(f"-->{sand_cord[1]} {sand_cord[0]}")
        if cave[sand_cord[1]][sand_cord[0]] == '.':
            continue

        if sand_cord[0]-1 < 0:
            break
        if cave[sand_cord[1]][sand_cord[0] - 1] == '.':
            sand_cord[0] -= 1
            continue

        if sand_cord[0]+1 >= len(cave[0]):
            break
        if cave[sand_cord[1]][sand_cord[0] + 1] == '.':
            sand_cord[0] += 1
            continue
        cave[sand_cord[1]-1][sand_cord[0]] = 'O'
        sand_cord = sand_source.copy()
    return cave


def part1(cave: list[list[str]]) -> None:
    """ part 1 solution """
    sand_corns = 0
    cave = simulate_sand_flow(cave)
    for _, row in enumerate(cave):
        #print(*row, sep="")
        for pixel in row:
            if pixel == 'O':
                sand_corns += 1
    print(f"#{f'  {cur_day} part1 answer is: {sand_corns}': <48}#")


def part2(cave: list[list[str]]) -> None:
    """ part 2 solution """
    sand_corns = 0
    cave = expand_cave(cave)
    cave = simulate_sand_flow(cave)
    for _, row in enumerate(cave):
        #print(_, *row, sep="")
        for pixel in row:
            if pixel == 'O':
                sand_corns += 1
    print(f"#{f'  {cur_day} part2 answer is: {sand_corns}': <48}#")


def main():
    """ day14 main """
    coordinates = read_file(input_path)
    cave = get_cave(coordinates)
    cave1 = cave.copy()
    cave2 = cave.copy()
    part1(cave1)
    part2(cave2)
    print("#"*50)
