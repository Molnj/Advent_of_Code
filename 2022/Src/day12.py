import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'../txt_inputs/{cur_day}.txt')
input_path = os.path.abspath(os.path.realpath(input_path))

start_val = ord('S') - ord('a') + 1     # -13
end_val = ord('E') - ord('a') + 1       # -27


def read_file(file_path: str) -> list[list[int]]:
    with open(file_path, "r+") as file:
        matrix = [[ord(num)-ord('a')+1 for num in line.strip()] for line in file]
    return matrix


def get_starting_pos(grid: list[list[int]], start: int) -> tuple:
    y, x = 0, 0
    for row in grid:
        x = 0
        for square in row:
            if square == start:
                grid[y][x] = 1  # ste S to 1
                return y, x
            x += 1
        y += 1
    return -1, -1

"""
    ugly Breath First Search implementation
    (no Dijkstra needed, since it's not a weighted graph)
    a queue starts with the starting coordinate
    every element in the queue is a 2 element list: [(y,x) coordinates, z distance from starting point]
    during an iteration:
        first element of queue is popped
        if it was already visited (there is a shorter path to it) then it's discarded here
        distance is incremented by 1
        all the neighbors of the current square get added to the queue, with it's distance value
        the conditional parts check for:
            not goung out of bound from matrix
            only adding neighbours to the queue, that are maximum by 1 higher than current
            setting E to 'z', since unique 'E' value is needed for finding end, but can be climbed as 'z'
"""
def BFS(grid: list[list[int]], start: tuple) -> int:
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
            y, x = node
            # print(node, grid[y][x], distance)
            if grid[y][x] == end_val:
                grid[y_start][x_start] = start_val  # reset 'S' from 'a' back to 'S'
                return distance
            for y2, x2 in ((y+1, x), (y-1, x), (y, x+1), (y, x-1)):
                if 0 <= x2 < width and 0 <= y2 < height:
                    next_square = grid[y2][x2]
                    if next_square == end_val:
                        next_square = ord('z')-ord('a')+1  # correct 'E' to 'z'
                    if next_square <= grid[y][x] + 1:
                        queue.append([(y2, x2), distance])
    return -1


"""
    going from E backwards until the first value 1 is found
"""
def BFS_2(grid: list[list[int]], start: tuple) -> int:
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
            y, x = node
            # print(node, grid[y][x], distance)
            if grid[y][x] == 1:
                grid[y_start][x_start] = start_val  # reset 'S' from 'a' back to 'S'
                return distance
            for y2, x2 in ((y+1, x), (y-1, x), (y, x+1), (y, x-1)):
                if 0 <= x2 < width and 0 <= y2 < height:
                    next_square = grid[y2][x2]
                    if next_square >= grid[y][x] - 1:
                        queue.append([(y2, x2), distance])
    return -1


def part1(grid: list[list[int]]) -> None:
    starting_pos = get_starting_pos(grid, start_val)
    step_num = BFS(grid, starting_pos)
    print(f"#\t{cur_day} part1 answer is: {step_num}\t\t\t\t\t#")


def part2(grid: list[list[int]]) -> None:
    step_num_min = len(grid) * len(grid[0])
    starting_pos = get_starting_pos(grid, end_val)
    step_num = BFS_2(grid, starting_pos)
    print(f"#\t{cur_day} part2 answer is: '{step_num}'\t\t\t\t#")


def main():
    matrix = read_file(input_path)
    part1(matrix)
    part2(matrix)
    print("#################################################")
