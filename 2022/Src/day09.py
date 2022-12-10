import os

cur_day = os.path.basename(__file__)[:-3]

file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'../txt_inputs/{cur_day}.txt')
input_path = os.path.abspath(os.path.realpath(input_path))


def read_file(file_path: str) -> list[str]:
    with open(file_path, "r+") as file:
        contents = [line.rstrip('\n') for line in file]
    return contents


def simulate_movement(rope: list, move: str) -> list:
    """
        returns a list of [X,Y] coordinates - "positions"
        last coordinate = the new head position
        the rest = positions covered by the tail
    """
    positions = [[0, 0]]
    prev_head_pos = [rope[0][0], rope[0][1]]

    move_dir = move.split(" ")[0]
    move_len = int(move.split(" ")[1])

    for i in range(move_len):
        for knot in range(0, len(rope)):
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
                else:
                    raise Exception(f"ERROR: Unmapped direction: {move_dir}")
            # move rope body
            else:
                prev_knot = [rope[knot-1][0], rope[knot-1][1]]
                if (abs(prev_knot[1] - cur_knot[1]) <= 1) and (abs(prev_knot[0] - cur_knot[0]) <= 1):
                    pass    # no movement if previous node is within the 3×3 area - centered around current node
                else:
                    if (prev_knot[0] - cur_knot[0]) > 0:    cur_knot[0] += 1
                    if (prev_knot[0] - cur_knot[0]) < 0:    cur_knot[0] -= 1
                    if (prev_knot[1] - cur_knot[1]) > 0:    cur_knot[1] += 1
                    if (prev_knot[1] - cur_knot[1]) < 0:    cur_knot[1] -= 1
            rope[knot][0], rope[knot][1] = cur_knot[0], cur_knot[1]

        positions.append([rope[-1][0], rope[-1][1]])    # add current tail position
    positions.pop(0)
    return rope, positions


def part1(moves: list[str], rope_len: int) -> None:
    tail_positions = []
    rope = [[0, 0] for _ in range(0, rope_len)]
    for move in moves:
        rope, temp = simulate_movement(rope, move)
        for i in temp:
            if i not in tail_positions:
                tail_positions.append(i)
    print(f"#\t{cur_day} part1 answer is: {len(tail_positions)}\t\t\t#")


def part2(moves: list[str], rope_len: int) -> None:
    tail_positions = []
    rope = [[0, 0] for _ in range(0, rope_len)]
    for move in moves:
        rope, temp = simulate_movement(rope, move)
        for i in temp:
            if i not in tail_positions:
                tail_positions.append(i)
    print(f"#\t{cur_day} part2 answer is: {len(tail_positions)}\t\t\t#")


def main():
    move_list = read_file(input_path)
    part1(move_list, 2)
    part2(move_list, 10)
    print("#########################################")
