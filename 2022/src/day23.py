"""
AOC 2022 day23 - Unstable Diffusion
    [ https://adventofcode.com/2022/day/23 ]
    - pt1: 4146
    - pt2: 957
    - lessons:
        - pretty nice list comprehensions and matrix neighbour checks here
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.abspath(os.path.join(os.getcwd(), os.pardir))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path: str) -> set[set[int, int]]:
    elves = set()
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]
    for y, line in enumerate(contents):
        for x, char in enumerate(line):
            if char == '#':
                elves.add((y, x))
    return elves


def part1(elves: set[set[int, int]]) -> None:
    """ part 1 solution """
    empty_ground = 0
    elves = elves.copy()
    dir_list = ['N', 'S', 'W', 'E']

    for _ in range(10):
        moving_elves = []
        # round 1 - checking whether move is possible to somewhere
        for (y, x) in elves:
            # check if elf has neighbors - if not, it won't move
            has_neighbour = False
            for dy in [-1, 0, 1]:
                for dx in [-1, 0, 1]:
                    if (y + dy, x + dx) in elves and (dy != 0 or dx != 0):
                        has_neighbour = True
            if not has_neighbour:
                continue

            # check if any side is free (in dir_list order)
            for dir_ in dir_list:
                if dir_ == 'N' \
                        and (y-1, x) not in elves \
                        and (y-1, x-1) not in elves \
                        and (y-1, x+1) not in elves:
                    moving_elves.append(((y, x), (y-1, x)))
                    break
                elif dir_ == 'E' \
                        and (y, x+1) not in elves \
                        and (y+1, x+1) not in elves \
                        and (y-1, x+1) not in elves:
                    moving_elves.append(((y, x), (y, x+1)))
                    break
                elif dir_ == 'S' \
                        and (y+1, x) not in elves \
                        and (y+1, x-1) not in elves \
                        and (y+1, x+1) not in elves:
                    moving_elves.append(((y, x), (y+1, x)))
                    break
                elif dir_ == 'W' \
                        and (y, x-1) not in elves \
                        and (y+1, x-1) not in elves \
                        and (y-1, x-1) not in elves:
                    moving_elves.append(((y, x), (y, x-1)))
                    break

        # remove elves from move list that have same destination
        passing_elves = []
        no_go_zones = set()
        visited = set()
        for start, dest in moving_elves:
             if not dest in visited:
                 visited.add(dest)
             else:
                 no_go_zones.add(dest)
        for start, dest in moving_elves:
            if dest not in no_go_zones:
                passing_elves.append((start, dest))

        # moving elves
        for start, dest in passing_elves:
            elves.add(dest)
            elves.discard(start)

        # rotate direction list
        dir_list = dir_list[1:] + [dir_list[0]]

    # get number of empty spots in smallest encircling square
    y_min = min(y for (y, x) in elves)
    y_max = max(y for (y, x) in elves)
    x_min = min(x for (y, x) in elves)
    x_max = max(x for (y, x) in elves)

    for y in range(y_min, y_max + 1):
        for x in range(x_min, x_max + 1):
            if (y, x) not in elves:
                empty_ground += 1

    print(f"#{f'  {cur_day} part1 answer is: {empty_ground}': <48}#")


def part2(elves: set[set[int, int]]) -> None:
    """ part 2 solution """
    num_of_turns = 0
    elves = elves.copy()
    dir_list = ['N', 'S', 'W', 'E']

    while True:
        num_of_turns += 1
        moving_elves = []
        # round 1 - checking whether move is possible to somewhere
        for (y, x) in elves:
            # check if elf has neighbors - if not, it won't move
            has_neighbour = False
            for dy in [-1, 0, 1]:
                for dx in [-1, 0, 1]:
                    if (y + dy, x + dx) in elves and (dy != 0 or dx != 0):
                        has_neighbour = True
            if not has_neighbour:
                continue

            # check if any side is free (in dir_list order)
            for dir_ in dir_list:
                if dir_ == 'N' \
                        and (y - 1, x) not in elves \
                        and (y - 1, x - 1) not in elves \
                        and (y - 1, x + 1) not in elves:
                    moving_elves.append(((y, x), (y - 1, x)))
                    break
                elif dir_ == 'E' \
                        and (y, x + 1) not in elves \
                        and (y + 1, x + 1) not in elves \
                        and (y - 1, x + 1) not in elves:
                    moving_elves.append(((y, x), (y, x + 1)))
                    break
                elif dir_ == 'S' \
                        and (y + 1, x) not in elves \
                        and (y + 1, x - 1) not in elves \
                        and (y + 1, x + 1) not in elves:
                    moving_elves.append(((y, x), (y + 1, x)))
                    break
                elif dir_ == 'W' \
                        and (y, x - 1) not in elves \
                        and (y + 1, x - 1) not in elves \
                        and (y - 1, x - 1) not in elves:
                    moving_elves.append(((y, x), (y, x - 1)))
                    break

        # remove elves from move list that have same destination
        passing_elves = []
        no_go_zones = set()
        visited = set()
        for start, dest in moving_elves:
            if not dest in visited:
                visited.add(dest)
            else:
                no_go_zones.add(dest)
        for start, dest in moving_elves:
            if dest not in no_go_zones:
                passing_elves.append((start, dest))

        # moving elves
        any_moved = False
        for start, dest in passing_elves:
            elves.add(dest)
            elves.discard(start)
            any_moved = True
        if not any_moved:
            break

        # rotate direction list
        dir_list = dir_list[1:] + [dir_list[0]]

    print(f"#{f'  {cur_day} part2 answer is: {num_of_turns}': <48}#")


def main():
    """ day23 main """
    elves = read_file(input_path)
    # print(elves)
    part1(elves)
    part2(elves)
    print("#"*50)
