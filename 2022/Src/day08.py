import os

cur_day = os.path.basename(__file__)[:-3]

file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'../txt_inputs/{cur_day}.txt')
input_path = os.path.abspath(os.path.realpath(input_path))


def read_file(file_path: str) -> list[str]:
    with open(file_path, "r+") as file:
        contents = [line.rstrip('\n') for line in file]
    return contents


def parse_matrix(txt: list[str]) -> list[list[int]]:
    matrix = []
    for line in txt:
        row = []
        for char in line:
            row.append(int(char))
        matrix.append(row)
    return matrix


def print_matrix(matrix: list[list[int]]):
    for row in matrix:
        for item in row:
            print(item, end="")
        print()


def is_visible_from_outside(forest: list[list[int]], trees_row: int, trees_col: int) -> bool:
    is_hidden = False
    obstructed_sides = 0
    tree_height = forest[trees_row][trees_col]
    forest_height = len(forest)
    forest_width = len(forest[0])

    # checking upwards
    row = trees_row
    col = trees_col
    while row > 0:
        row -= 1
        if forest[row][col] >= tree_height:
            obstructed_sides += 1
            break

    # checking downwards
    row = trees_row
    col = trees_col
    while row < forest_height-1:
        row += 1
        if forest[row][col] >= tree_height:
            obstructed_sides += 1
            break

    # checking to the right
    row = trees_row
    col = trees_col
    while col < forest_width-1:
        col += 1
        if forest[row][col] >= tree_height:
            obstructed_sides += 1
            break

    # checking to the left
    row = trees_row
    col = trees_col
    while col > 0:
        col -= 1
        if forest[row][col] >= tree_height:
            obstructed_sides += 1
            break

    if obstructed_sides >= 4:
        is_hidden = True
    return is_hidden


def count_trees_seen(forest: list[list[int]], trees_row: int, trees_col: int) -> bool:
    trees_seen = 1
    tree_height = forest[trees_row][trees_col]
    forest_height = len(forest)
    forest_width = len(forest[0])

    # checking upwards
    temp_trees_seen = 0
    row = trees_row
    col = trees_col
    while row > 0:
        temp_trees_seen += 1
        row -= 1
        if forest[row][col] >= tree_height:
            break
    trees_seen *= temp_trees_seen

    # checking downwards
    temp_trees_seen = 0
    row = trees_row
    col = trees_col
    while row < forest_height-1:
        temp_trees_seen += 1
        row += 1
        if forest[row][col] >= tree_height:
            break
    trees_seen *= temp_trees_seen

    # checking to the right
    temp_trees_seen = 0
    row = trees_row
    col = trees_col
    while col < forest_width-1:
        temp_trees_seen += 1
        col += 1
        if forest[row][col] >= tree_height:
            break
    trees_seen *= temp_trees_seen

    # checking to the left
    temp_trees_seen = 0
    row = trees_row
    col = trees_col
    while col > 0:
        temp_trees_seen += 1
        col -= 1
        if forest[row][col] >= tree_height:
            break
    trees_seen *= temp_trees_seen

    return trees_seen


def part1(forest: list[list[int]]) -> None:
    visible_tree_num = 0
    forest_height = len(forest)
    forest_width = len(forest[0])
    x, y = 0, 0
    while y < forest_width:
        while x < forest_height:
            if is_visible_from_outside(forest, y, x):
                visible_tree_num += 1
            x += 1
        x = 0
        y += 1
    print(f"#\t{cur_day} part1 answer is: {visible_tree_num}\t\t\t\t\t#")


def part2(forest: list[list[int]]) -> None:
    top_scenic_score = 0
    forest_height = len(forest)
    forest_width = len(forest[0])
    x, y = 0, 0
    while y < forest_width:
        while x < forest_height:
            scenic_score = count_trees_seen(forest, y, x)
            if scenic_score > top_scenic_score:
                top_scenic_score = scenic_score
            x += 1
        x = 0
        y += 1
    print(f"#\t{cur_day} part2 answer is: {top_scenic_score}\t\t\t\t#")


def main():
    txt_file = read_file(input_path)
    matrix = parse_matrix(txt_file)
    # print_matrix(forest)
    part1(matrix)
    part2(matrix)
    print("#################################################")
