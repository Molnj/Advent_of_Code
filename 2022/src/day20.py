"""
AOC 2022 day20 - Grove Positioning System
    [ https://adventofcode.com/2022/day/20 ]
    - pt1: 7153
    - pt2: 6146976244822
    - lessons:
        - shifting more than length of circular buffer originally
            was done by "while bigger subtract buf length from idx"
            this was too slow, correct method: idx = idx % len(buffer)
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path: str) -> list[tuple[int, int]]:
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [int(line.rstrip('\n')) for line in file]
        for idx, val in enumerate(contents):
            contents[idx] = (idx, val)
    return contents


def part1(buf: list[tuple[int, int]]) -> None:
    """ part 1 solution """
    coordinate_sum = 0
    buffer = buf.copy()
    for cnt in range(len(buffer)):
        for idx, tup in enumerate(buffer):
            if tup[0] == cnt:
                buffer.pop(idx)
                idx += tup[1]
                idx = idx % len(buffer)
                if idx == 0:
                    idx = len(buffer)
                buffer.insert(idx, tup)
                break

    index_of_zero = 0
    for idx, val in enumerate(buffer):
        if val[1] == 0:
            index_of_zero = idx
            break

    idx_1000 = (index_of_zero + 1000) % len(buffer)
    idx_2000 = (index_of_zero + 2000) % len(buffer)
    idx_3000 = (index_of_zero + 3000) % len(buffer)
    coordinate_sum = buffer[idx_1000][1] + buffer[idx_2000][1] + buffer[idx_3000][1]
    print(f"#{f'  {cur_day} part1 answer is: {coordinate_sum}': <48}#")


def part2(buf: list[tuple[int, int]]) -> None:
    """ part 2 solution """
    coordinate_sum = 0
    decryption_key = 811589153
    buffer = []
    for tup in buf:
        buf_idx = tup[0]
        buf_val = tup[1] * decryption_key
        buffer.append((buf_idx, buf_val))

    for _ in range(10):
        for cnt in range(len(buffer)):
            for idx, tup in enumerate(buffer):
                if tup[0] == cnt:
                    buffer.pop(idx)
                    idx += tup[1]
                    idx = idx % len(buffer)
                    if idx == 0:
                        idx = len(buffer)
                    buffer.insert(idx, tup)
                    break

    index_of_zero = 0
    for idx, val in enumerate(buffer):
        if val[1] == 0:
            index_of_zero = idx
            break

    idx_1000 = (index_of_zero + 1000) % len(buffer)
    idx_2000 = (index_of_zero + 2000) % len(buffer)
    idx_3000 = (index_of_zero + 3000) % len(buffer)
    coordinate_sum = buffer[idx_1000][1] + buffer[idx_2000][1] + buffer[idx_3000][1]
    print(f"#{f'  {cur_day} part2 answer is: {coordinate_sum}': <48}#")


def main():
    """ day20 main """
    buffer = read_file(input_path)
    part1(buffer)
    part2(buffer)
    print("#"*50)
