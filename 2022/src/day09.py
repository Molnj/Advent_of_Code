"""
AOC 2022 day09 - Rope Bridge
    [ https://adventofcode.com/2022/day/9 ]
    - pt1: 5695
    - pt2: 2434
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path: str) -> list[str]:
    """ parse input txt line-by-line into list of strings """
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]
    return contents


def simulate_movement(rope: list, move: str) -> list:
    """
        returns a list of [X,Y] coordinates - "positions"
        last coordinate = the new head position
        the rest = positions covered by the tail
    """
    positions = [[0, 0]]

    move_dir = move.split(" ")[0]
    move_len = int(move.split(" ")[1])

    for _ in range(move_len):
        for knot, __ in enumerate(rope):
            cur_knot = [rope[knot][0], rope[knot][1]]
            # move rope head
            if knot == 0:
                if move_dir == 'R':
                    cur_knot[0] += 1
                elif move_dir == 'L':
                    cur_knot[0] -= 1
                elif move_dir == 'U':
                    cur_knot[1] += 1
                elif move_dir == 'D':
                    cur_knot[1] -= 1
            # move rope body
            else:
                prev_knot = [rope[knot-1][0], rope[knot-1][1]]
                if (abs(prev_knot[1] - cur_knot[1]) <= 1) \
                        and (abs(prev_knot[0] - cur_knot[0]) <= 1):
                    # no movement if previous node is within the 3×3 area
                    pass
                else:
                    if (prev_knot[0] - cur_knot[0]) > 0:
                        cur_knot[0] += 1
                    if (prev_knot[0] - cur_knot[0]) < 0:
                        cur_knot[0] -= 1
                    if (prev_knot[1] - cur_knot[1]) > 0:
                        cur_knot[1] += 1
                    if (prev_knot[1] - cur_knot[1]) < 0:
                        cur_knot[1] -= 1
            rope[knot][0], rope[knot][1] = cur_knot[0], cur_knot[1]

        positions.append([rope[-1][0], rope[-1][1]])    # add current tail position
    positions.pop(0)
    return rope, positions


def part1(moves: list[str], rope_len: int) -> None:
    """ part 1 solution """
    tail_positions = []
    rope = [[0, 0] for _ in range(0, rope_len)]
    for move in moves:
        rope, temp = simulate_movement(rope, move)
        for i in temp:
            if i not in tail_positions:
                tail_positions.append(i)
    print(f"#{f'  {cur_day} part1 answer is: {len(tail_positions)}': <48}#")


def part2(moves: list[str], rope_len: int) -> None:
    """ part 2 solution """
    tail_positions = []
    rope = [[0, 0] for _ in range(0, rope_len)]
    for move in moves:
        rope, temp = simulate_movement(rope, move)
        for i in temp:
            if i not in tail_positions:
                tail_positions.append(i)
    print(f"#{f'  {cur_day} part2 answer is: {len(tail_positions)}': <48}#")


def main():
    """ day09 main """
    move_list = read_file(input_path)
    part1(move_list, 2)
    part2(move_list, 10)
    print("#"*50)
