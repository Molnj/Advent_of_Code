"""
AOC 2022 day22 - Monkey Map
    [ https://adventofcode.com/2022/day/22 ]
    - pt1: 106094
    - pt2: 162038
    - lessons:
        - the task required precision, but wasn't too challenging technically
          on the other hand I need to learn more about structuring code
          (traversal between sides, especially in 3D form is pretty ugly rn)
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path: str):
    # read input txt file
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]
    idx = 0

    # find separating empty line -> field | moves
    for i, line in enumerate(contents):
        if line == "":
            idx = i
    field = contents[:idx]
    moves_temp = contents[idx+1:]

    # parse moves
    moves = []
    for line in moves_temp:
        temp = ""
        for char in line:
            if char.isalpha():
                moves.append(int(temp))
                moves.append(char)
                temp = ""
            else:
                temp += char
        moves.append(int(temp))  # add last number
    return field, moves


def part1(field: list[str], moves: list[any]) -> None:
    """ part 1 solution """
    password = 0
    direction = [0, 1]

    # get starting position (assumes there is any in 1st lien)
    pos = [0, 0]
    for idx, i in enumerate(field[0]):
        if i == '.':
            pos = [0, idx]
            break

    # traverse
    # to whomever is reading this: I am sorry
    for cmd in moves:
        if cmd == 'R':
            if direction[0] == 0:
                direction = [direction[1], 0]
            else:
                direction = [0, -direction[0]]
        elif cmd == 'L':
            if direction[0] == 0:
                direction = [-direction[1], 0]
            else:
                direction = [0, direction[0]]
        else:
            for _ in range(cmd):
                next_pos = [pos[0]+direction[0], pos[1]+direction[1]]
                next_x = next_pos[1]
                next_y = next_pos[0]

                # moving off the map on the right
                if direction == [0, 1]:
                    if next_x >= len(field[pos[0]]):
                        for idx, val in enumerate(field[pos[0]]):
                            if val != ' ':
                                next_x = idx
                                break

                # moving off the map on the left
                if direction == [0, -1]:
                    if next_x < 0:
                        next_x = len(field[pos[0]])-1
                    elif field[pos[0]][next_x] == ' ':
                        next_x = len(field[pos[0]])-1

                # moving off the map on the bottom
                if direction == [1, 0]:
                    if next_y >= len(field):
                        for idx, line in enumerate(field):
                            if len(line) > pos[1]:
                                if field[idx][pos[1]] != ' ':
                                    next_y = idx
                                    break
                    elif pos[1] >= len(field[next_y]):
                        for idx, line in enumerate(field):
                            if len(line) > pos[1]:
                                if field[idx][pos[1]] != ' ':
                                    next_y = idx
                                    break
                    elif field[next_y][pos[1]] == ' ':
                        for idx, line in enumerate(field):
                            if len(line) > pos[1]:
                                if field[idx][pos[1]] != ' ':
                                    next_y = idx
                                    break

                # moving off the map on the top
                if direction == [-1, 0]:
                    if next_y < 0:
                        for idx, line in enumerate(reversed(field)):
                            idx_rev = len(field) - idx - 1
                            if len(line) > pos[1]:
                                if field[idx_rev][pos[1]] != ' ':
                                    next_y = idx_rev
                                    break
                    elif pos[1] >= len(field[next_y]):
                        for idx_rev, line in enumerate(reversed(field)):
                            if len(line) > pos[1]:
                                if field[idx_rev][pos[1]] != ' ':
                                    next_y = idx_rev
                                    break
                    elif field[next_y][pos[1]] == ' ':
                        for idx_rev, line in enumerate(reversed(field)):
                            if len(line) > pos[1]:
                                if field[idx_rev][pos[1]] != ' ':
                                    next_y = idx_rev
                                    break

                # moving - checking for empty spaces & walls
                if field[next_y][next_x] == '#':
                    pass
                else:
                    pos = [next_y, next_x]

    # calculate password
    facing = -1
    if direction == [0, 1]:
        facing = 0
    if direction == [1, 0]:
        facing = 1
    if direction == [0, -1]:
        facing = 2
    if direction == [-1, 0]:
        facing = 3
    password = 1000 * (pos[0]+1) + 4 * (pos[1]+1) + facing

    print(f"#{f'  {cur_day} part1 answer is: {password}': <48}#")



def part2(field: list[str], moves: list[any]) -> None:
    """ part 2 solution (only maps to this one 50×50×50 input shape) - my crime against humanity"""
    # TODO - there are always 14 open sides, that's 7 side pairs, there should be a function mapping them together
    password = 0
    direction = [0, 1]

    # get starting position (assumes there is any in 1st lien)
    pos = [0, 0]
    for idx, i in enumerate(field[0]):
        if i == '.':
            pos = [0, idx]
            break

    # traverse
    # to whomever is reading this: I am sorry
    for cmd in moves:
        if cmd == 'R':
            if direction[0] == 0:
                direction = [direction[1], 0]
            else:
                direction = [0, -direction[0]]
        elif cmd == 'L':
            if direction[0] == 0:
                direction = [-direction[1], 0]
            else:
                direction = [0, direction[0]]
        else:
            for _ in range(cmd):
                next_pos = [pos[0] + direction[0], pos[1] + direction[1]]
                next_x = next_pos[1]
                next_y = next_pos[0]

                # side 1 - OK
                if (0 <= pos[0] < 50) and (100 <= pos[1] < 150):
                    # print("1", direction)
                    # moving off the map on the right
                    if direction == [0, 1]:
                        if next_x >= 150:
                            next_x = 99
                            next_y = 150 - (pos[0] + 1)
                            if field[next_y][next_x] != '#':
                                direction = [0, -1]
                    # moving off the map on the left
                    if direction == [0, -1]:
                        pass
                    # moving off the map on the bottom
                    if direction == [1, 0]:
                        if next_y >= 50:
                            next_y = pos[1] - 50
                            next_x = 99
                            if field[next_y][next_x] != '#':
                                direction = [0, -1]
                    # moving off the map on the top
                    if direction == [-1, 0]:
                        if next_y < 0:
                            next_x = pos[1] - 100
                            next_y = 199

                # side 2 - OK
                if (0 <= pos[0] < 50) and (50 <= pos[1] < 100):
                    # print("2", direction)
                    # moving off the map on the right
                    if direction == [0, 1]:
                        pass
                    # moving off the map on the left
                    if direction == [0, -1]:
                        if next_x < 50:
                            next_x = 0
                            next_y = 150 - (pos[0]+1)
                            if field[next_y][next_x] != '#':
                                direction = [0, 1]
                    # moving off the map on the bottom
                    if direction == [1, 0]:
                        pass
                    # moving off the map on the top
                    if direction == [-1, 0]:
                        if next_y < 0:
                            next_x = 0
                            next_y = pos[1] + 100
                            if field[next_y][next_x] != '#':
                                direction = [0, 1]

                # side 3
                if (50 <= pos[0] < 100) and (50 <= pos[1] < 100):
                    # print("3", direction)
                    # moving off the map on the right
                    if direction == [0, 1]:
                        if next_x >= 100:
                            next_x = pos[0] + 50
                            next_y = 49
                            if field[next_y][next_x] != '#':
                                direction = [-1, 0]
                    # moving off the map on the left
                    if direction == [0, -1]:
                        if next_x < 50:
                            next_x = pos[0] - 50
                            next_y = 100
                            if field[next_y][next_x] != '#':
                                direction = [1, 0]
                    # moving off the map on the bottom
                    if direction == [1, 0]:
                        pass
                    # moving off the map on the top
                    if direction == [-1, 0]:
                        pass

                # side 4
                if (100 <= pos[0] < 150) and (50 <= pos[1] < 100):
                    # print("4", direction)
                    # moving off the map on the right
                    if direction == [0, 1]:
                        if next_x >= 100:
                            next_x = 149
                            next_y = 150 - (pos[0] + 1)
                            if field[next_y][next_x] != '#':
                                direction = [0, -1]
                    # moving off the map on the left
                    if direction == [0, -1]:
                        pass
                    # moving off the map on the bottom
                    if direction == [1, 0]:
                        if next_y >= 150:
                            next_y = pos[1] + 100
                            next_x = 49
                            if field[next_y][next_x] != '#':
                                direction = [0, -1]
                    # moving off the map on the top
                    if direction == [-1, 0]:
                        pass

                # side 5
                if (100 <= pos[0] < 150) and (0 <= pos[1] < 50):
                    # print("5", direction)
                    # moving off the map on the right
                    if direction == [0, 1]:
                        pass
                    # moving off the map on the left
                    if direction == [0, -1]:
                        if next_x < 0:
                            next_x = 50
                            next_y = 150 - (pos[0]+1)
                            if field[next_y][next_x] != '#':
                                direction = [0, 1]
                    # moving off the map on the bottom
                    if direction == [1, 0]:
                        pass
                    # moving off the map on the top
                    if direction == [-1, 0]:
                        if next_y < 100:
                            next_x = 50
                            next_y = pos[1] + 50
                            if field[next_y][next_x] != '#':
                                direction = [0, 1]

                # side 6
                if (150 <= pos[0] < 200) and (0 <= pos[1] < 50):
                    # print("6", direction)
                    # moving off the map on the right
                    if direction == [0, 1]:
                        if next_x >= 50:
                            next_x = pos[0] - 100
                            next_y = 149
                            if field[next_y][next_x] != '#':
                                direction = [-1, 0]
                    # moving off the map on the left
                    if direction == [0, -1]:
                        if next_x < 0:
                            next_x = pos[0] - 100
                            next_y = 0
                            if field[next_y][next_x] != '#':
                                direction = [1, 0]
                    # moving off the map on the bottom
                    if direction == [1, 0]:
                        if next_y >= 200:
                            next_y = 0
                            next_x = pos[1] + 100
                    # moving off the map on the top
                    if direction == [-1, 0]:
                        pass

                # moving - checking for empty spaces & walls
                if field[next_y][next_x] == '#':
                    pass
                else:
                    pos = [next_y, next_x]

    # calculate password
    facing = -1
    if direction == [0, 1]:
        facing = 0
    if direction == [1, 0]:
        facing = 1
    if direction == [0, -1]:
        facing = 2
    if direction == [-1, 0]:
        facing = 3
    password = 1000 * (pos[0] + 1) + 4 * (pos[1] + 1) + facing
    print(f"#{f'  {cur_day} part2 answer is: {password}': <48}#")



def main():
    """ day22 main """
    field, moves = read_file(input_path)
    part1(field, moves)
    part2(field, moves)
    print("#"*50)
