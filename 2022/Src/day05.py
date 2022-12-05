import os

file_dir = os.path.dirname(os.path.realpath('__file__'))
file_name = os.path.join(file_dir, '../2022/txt_inputs/day05.txt')
file_name = os.path.abspath(os.path.realpath(file_name))

stack_num = 9


def read_file(file_path: str) -> list[str]:
    with open(file_path, "r+") as file:
        contents = [line.rstrip('\n') for line in file]     # readlines(), but without "\n"
    return contents


def create_stacks(lines: list[str]) -> list[list]:
    stacks = [[] for _ in range(stack_num)]
    i = 7
    while i >= 0:
        crates = lines[i][1::4]
        for s in range(len(crates)):
            if crates[s] != " ":
                stacks[s].append(crates[s])
        i -= 1
    return stacks


def move_crates(lines: list[str], stacks: list[list], can_move_multiple) -> list[list]:
    i = 10
    while i < len(lines):
        lines[i] = lines[i].split()
        _num = int(lines[i][1])
        _from = int(lines[i][3]) - 1
        _to = int(lines[i][5]) - 1
        if can_move_multiple:
            crates = []
            for _ in range(_num):
                crates.append(stacks[_from].pop())
            for _ in range(_num):
                stacks[_to].append(crates.pop())
        else:
            for _ in range(_num):
                crate = stacks[_from].pop()
                stacks[_to].append(crate)
        i += 1
    return stacks


def get_top_crates(stacks: list[list]) -> str:
    top_str = ""
    for i in range(stack_num):
        top_str += stacks[i].pop()
    return top_str


def part1(txt: list[str]) -> None:
    lines = [line.strip() for line in txt]          # get iterable input
    stacks = create_stacks(lines)                   # create stacks
    move_crates(lines, stacks, False)               # move stack items
    result = get_top_crates(stacks)                 # get result (string of top item letters)
    print(f"day05 part1 answer is: {result}")


def part2(txt: list[str]) -> None:
    lines = [line.strip() for line in txt]          # get iterable input
    stacks = create_stacks(lines)                   # create stacks
    move_crates(lines, stacks, True)                # move stack items
    result = get_top_crates(stacks)                 # get result (string of top item letters)
    print(f"day05 part2 answer is: {result}")


def main():
    txt_file = read_file(file_name)
    part1(txt_file)
    part2(txt_file)
    print("#################################")
