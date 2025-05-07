"""
AOC 2022 day17 - Pyroclastic Flow
    [ https://adventofcode.com/2022/day/17 ]
    - pt1: 3168
    - pt2: 1554117647070
    - lessons: finding looping cycle in list (pt2)s
"""

import os
import re

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')    # using \ as 1st char in str represents absoulte path (all before it wouldl be discarded)
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path: str) -> list[str]:
    """ parse input txt character-by-character into wind gust directions """
    gusts = []
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]
        for line in contents:
            for cmd in line:
                gusts.append(cmd)
    return gusts


def spawn_rock(idx: int, y: int) -> set:
    y += 3
    if idx == 0:
        return set([(y,2), (y,3), (y,4), (y,5)])               
    elif idx == 1:
        return set([(y,3), (y+1,2), (y+1,3), (y+1,4), (y+2,3)]) 
    elif idx == 2:
        return set([(y,2), (y,3), (y,4), (y+1,4), (y+2,4)])
    elif idx == 3:
        return set([(y,2), (y+1,2), (y+2,2), (y+3,2)])
    elif idx == 4:
        return set([(y,2), (y,3), (y+1,2), (y+1,3)])
    else:
        raise ValueError("Rock ID unknown")


def move_left(rock: set, chamber: set):
    temp_rock = set([(y, x-1) for (y, x) in rock])
    if temp_rock & chamber:
        return rock
    if any([x < 0 for (y, x) in temp_rock]):
        return rock
    return set([(y, x-1) for (y, x) in rock])


def move_right(rock: set, chamber: set):
    temp_rock = set([(y, x+1) for (y, x) in rock])
    if temp_rock & chamber:
        return rock
    if any([x > 6 for (y, x) in temp_rock]):
        return rock
    return temp_rock


def move_down(rock: set, chamber: set):
    temp_rock = set([(y-1, x) for (y, x) in rock])
    if temp_rock & chamber:
        return rock
    if any([y < 0 for (y, x) in temp_rock]):
        return rock
    return temp_rock


def visualize(chamber: set, height: int) -> None:
    for y in range(height+1):
        print('|', end="")
        for x in range(7):
            if {(height-y, x)} & chamber:
                print('#', end="")
            else:
                print('.', end="")
        print('|', end="\n")
    print("+-------+")


def check_repetition(heights: list[int]):
    """ looks for a pattern that's longer than 10 numbers & loops at least 2 times """
    max_len = len(heights)//2
    for idx in range(max_len//2):
        cur_len = 10
        while idx+2*cur_len < len(heights):
            if heights[idx : idx+cur_len] == heights[idx+cur_len : idx+2*cur_len]:
                return (idx, heights[idx : idx+cur_len])
            cur_len += 1
    return (-1, (-1,-1))

def part1(gusts: list[str], max_turns: int) -> None:
    """ part 1 solution """
    chamber = set()
    rock = set()
    max_height = 0
    rock_cnt = 0
    turn = -1
    while rock_cnt < max_turns:
        turn += 1
        if not rock:
            rock |= spawn_rock(rock_cnt%5, max_height)
            rock_cnt += 1

        if gusts[turn%len(gusts)] == '<':
            rock = move_left(rock, chamber)
        else:
            rock = move_right(rock, chamber)

        rock_tmp = move_down(rock, chamber)
        if rock_tmp == rock:
            chamber |= rock
            rock.clear()
            max_height = max([y for (y,x) in chamber]) + 1
        else:
            rock = rock_tmp

    # visualize(chamber, max_height)
    print(f"#{f'  {cur_day} part1 answer is: {max_height}': <48}#")


def part2(gusts: list[str], max_turns: int) -> None:
    """ part 2 solution """
    height_pattern = []
    chamber = set()
    rock = set()
    max_height = 0
    rock_cnt = 0
    turn = -1
    while rock_cnt < max_turns:
        # print(turn)
        turn += 1
        if not rock:
            rock |= spawn_rock(rock_cnt%5, max_height)
            rock_cnt += 1

        if gusts[turn%len(gusts)] == '<':
            rock = move_left(rock, chamber)
        else:
            rock = move_right(rock, chamber)

        rock_tmp = move_down(rock, chamber)
        if rock_tmp == rock:
            chamber |= rock
            rock.clear()
            prev_height = max_height
            max_height = max([y for (y,x) in chamber]) + 1
            height_pattern.append(max_height - prev_height)
        else:
            rock = rock_tmp

        if rock_cnt%1000==0:
            rep_idx, rep_pattern = check_repetition(height_pattern)
            if rep_idx != -1:
                rep_len = len(rep_pattern)
                rep_val = sum(rep_pattern)
                init_height = sum(height_pattern[:rep_idx])
                height = init_height + (((max_turns-rep_idx)//rep_len)*rep_val) + sum(rep_pattern[:(max_turns-rep_idx)%rep_len])
                print(f"#{f'  {cur_day} part2 answer is: {height}': <48}#")
                break


def main():
    """ day17 main """
    gusts = read_file(input_path)
    part1(gusts, 2023)
    part2(gusts, 1_000_000_000_000)
    print("#"*50)
