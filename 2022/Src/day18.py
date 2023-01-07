"""
AOC 2022 day18 - Boiling Boulders
    [ https://adventofcode.com/2022/day/18 ]
    - pt1: 4282
    - pt2: 2452
"""

import os

MAX_SIZE = 24
dfs_visited = [[[False for i in range(MAX_SIZE)]
               for j in range(MAX_SIZE)]
               for k in range(MAX_SIZE)]

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path: str) -> list[str]:
    with open(file_path, mode="r+", encoding="utf-8") as file:
        coordinates = []
        contents = [line.rstrip('\n') for line in file]
        for line in contents:
            pos = line.split(',')
            pos = [int(i)+1 for i in pos]     # str -> int list comprehension
            coordinates.append(tuple(pos))
    return coordinates


def create_space(coordinates: list[tuple[int]]) -> list[list[list[int]]]:
    cube = [[[0 for z_pos in range(MAX_SIZE)]
             for y_pos in range(MAX_SIZE)]
            for x_pos in range(MAX_SIZE)]
    for coordinate in coordinates:
        z_pos, y_pos, x_pos = coordinate
        cube[z_pos][y_pos][x_pos] = 1
    return cube


def DFS(layer, row, col, grid):
    """ Function to perform DFS Traversal on the 3D matrix grid[] """
    global MAX_SIZE
    global dfs_visited

    offset_z = [1, -1, 0, 0, 0, 0]
    offset_y = [0, 0, 1, -1, 0, 0]
    offset_x = [0, 0, 0, 0, 1, -1]

    # Initialize a stack of pairs and push the starting cell into it
    stack = [[layer, row, col]]

    # Iterate until the stack is not empty
    while len(stack) > 0:
        # Pop the top pair
        curr = stack[len(stack) - 1]
        stack.remove(stack[len(stack) - 1])
        layer = curr[0]
        row = curr[1]
        col = curr[2]

        # if found edge of defined volume -- path is found
        if (layer < 0 or row < 0 or col < 0
                or layer >= MAX_SIZE or row >= MAX_SIZE or col >= MAX_SIZE):
            dfs_visited = [[[False for i in range(MAX_SIZE)]
                            for j in range(MAX_SIZE)]
                           for k in range(MAX_SIZE)]
            # print(stack)
            return True

        # if went into a wall -- stop this branch
        if grid[layer][row][col] == 1:
            continue

        # Check if the current popped cell is a valid cell or not
        if not dfs_visited[layer][row][col]:
            # Mark the current cell as visited
            dfs_visited[layer][row][col] = True

            # Push all the adjacent cells
            for i in range(6):
                adj_z = layer + offset_z[i]
                adj_y = row + offset_y[i]
                adj_x = col + offset_x[i]
                stack.append([adj_z, adj_y, adj_x])

    dfs_visited = [[[False for i in range(MAX_SIZE)]
                    for j in range(MAX_SIZE)]
                   for k in range(MAX_SIZE)]


def part1(cube: list[list[list[int]]]) -> None:
    """ part 1 solution """
    area = 0
    offset_z = [1, -1, 0, 0, 0, 0]
    offset_y = [0, 0, 1, -1, 0, 0]
    offset_x = [0, 0, 0, 0, 1, -1]
    for z_pos in range(MAX_SIZE):
        for y_pos in range(MAX_SIZE):
            for x_pos in range(MAX_SIZE):
                if cube[z_pos][y_pos][x_pos] == 1:
                    for i in range(6):
                        adj_z = z_pos + offset_z[i]
                        adj_y = y_pos + offset_y[i]
                        adj_x = x_pos + offset_x[i]
                        if cube[adj_z][adj_y][adj_x] == 0:
                            area += 1
    print(f"#{f'  {cur_day} part1 answer is: {area}': <48}#")


def part2(cube: list[list[list[int]]]) -> None:
    """ part 2 solution """
    area = 0
    offset_z = [1, -1, 0, 0, 0, 0]
    offset_y = [0, 0, 1, -1, 0, 0]
    offset_x = [0, 0, 0, 0, 1, -1]
    for z_pos in range(MAX_SIZE):
        # print(z_pos)      # pseudo load-bar
        for y_pos in range(MAX_SIZE):
            for x_pos in range(MAX_SIZE):
                if cube[z_pos][y_pos][x_pos] == 1:
                    for i in range(6):
                        adj_z = z_pos + offset_z[i]
                        adj_y = y_pos + offset_y[i]
                        adj_x = x_pos + offset_x[i]
                        if DFS(adj_z, adj_y, adj_x, cube):
                            area += 1
    


def main():
    """ day18 main """
    coordinates = read_file(input_path)
    cube = create_space(coordinates)
    part1(cube)
    part2(cube)
    print("#"*50)
