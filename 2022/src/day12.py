"""
AOC 2022 day12 - Hill Climbing Algorithm
    [ https://adventofcode.com/2022/day/12 ]
    - pt1: 408
    - pt2: 399
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.abspath(os.path.join(os.getcwd(), os.pardir))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)

start_val = ord('S') - ord('a') + 1     # -13
end_val = ord('E') - ord('a') + 1       # -27


def read_file(file_path: str) -> list[list[int]]:
    """ parse input txt onto topological height map matrix """
    with open(file_path, mode="r+", encoding="utf-8") as file:
        matrix = [[ord(num)-ord('a')+1 for num in line.strip()] for line in file]
    return matrix


def get_starting_pos(grid: list[list[int]], start: int) -> tuple:
    """ finding 'S' starting position in grid """
    grid_y, grid_x = 0, 0
    for row in grid:
        grid_x = 0
        for square in row:
            if square == start:
                grid[grid_y][grid_x] = 1  # ste S to 1
                return grid_y, grid_x
            grid_x += 1
        grid_y += 1
    return -1, -1


def bfs(grid: list[list[int]], start: tuple) -> int:
    """
        ugly Breath First Search implementation
        (no Dijkstra needed, since it's not a weighted graph)
        a queue starts with the starting coordinate
        every element in the queue is a 2 element list:
          - (y,x) coordinates,
          - z distance from starting point
        during an iteration:
            first element of queue is popped
            if it was already visited (there is a shorter path to it) then it's discarded here
            distance is incremented by 1
            all the neighbors of the current square get added to the queue, with it's distance value
            the conditional parts check for:
                not goung out of bound from matrix
                only adding neighbours to the queue, that are maximum by 1 higher than current
                E to 'z', since unique 'E' val is needed for finding end, but can be climbed as 'z'
    """
    # correct 'S' to 'a'
    y_start, x_start = start
    grid[y_start][x_start] = 1

    width = len(grid[0])
    height = len(grid)

    distance = -1
    queue = [[start, distance]]     # queue - will be filled with neighbours
    visited = []                    # list of already visited nodes
    while queue:
        next_node = queue.pop(0)
        node = next_node[0]
        distance = next_node[1]
        if node not in visited:
            distance += 1
            visited.append(node)
            node_y, node_x = node
            # print(node, grid[y][x], distance)
            if grid[node_y][node_x] == end_val:
                grid[y_start][x_start] = start_val  # reset 'S' from 'a' back to 'S'
                return distance
            for node_y2, node_x2 in ((node_y+1, node_x), (node_y-1, node_x),
                                     (node_y, node_x+1), (node_y, node_x-1)):
                if 0 <= node_x2 < width and 0 <= node_y2 < height:
                    next_square = grid[node_y2][node_x2]
                    if next_square == end_val:
                        next_square = ord('z')-ord('a')+1  # correct 'E' to 'z'
                    if next_square <= grid[node_y][node_x] + 1:
                        queue.append([(node_y2, node_x2), distance])
    return -1


def bfs_2(grid: list[list[int]], start: tuple) -> int:
    """
        another BFS implementation for part 2
        going from E backwards until the first value 1 is found
    """
    # correct 'S' to 'a'
    y_start, x_start = start
    grid[y_start][x_start] = ord('z') - ord('a') + 1

    width = len(grid[0])
    height = len(grid)

    distance = -1
    queue = [[start, distance]]     # queue - will be filled with neighbours
    visited = []                    # list of already visited nodes
    while queue:
        next_node = queue.pop(0)
        node = next_node[0]
        distance = next_node[1]
        if node not in visited:
            distance += 1
            visited.append(node)
            node_y, node_x = node
            # print(node, grid[y][x], distance)
            if grid[node_y][node_x] == 1:
                grid[y_start][x_start] = start_val  # reset 'S' from 'a' back to 'S'
                return distance
            for node_y2, node_x2 in ((node_y+1, node_x), (node_y-1, node_x),
                                     (node_y, node_x+1), (node_y, node_x-1)):
                if 0 <= node_x2 < width and 0 <= node_y2 < height:
                    next_square = grid[node_y2][node_x2]
                    if next_square >= grid[node_y][node_x] - 1:
                        queue.append([(node_y2, node_x2), distance])
    return -1


def part1(grid: list[list[int]]) -> None:
    """ part 1 solution """
    starting_pos = get_starting_pos(grid, start_val)
    step_num = bfs(grid, starting_pos)
    print(f"#{f'  {cur_day} part1 answer is: {step_num}': <48}#")


def part2(grid: list[list[int]]) -> None:
    """ part 2 solution """
    starting_pos = get_starting_pos(grid, end_val)
    step_num = bfs_2(grid, starting_pos)
    print(f"#{f'  {cur_day} part2 answer is: {step_num}': <48}#")


def main():
    """ day12 main """
    matrix = read_file(input_path)
    part1(matrix)
    part2(matrix)
    print("#"*50)
