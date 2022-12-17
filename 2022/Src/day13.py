import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'../txt_inputs/{cur_day}.txt')
input_path = os.path.abspath(os.path.realpath(input_path))


def read_file(file_path: str) -> list[list[int]]:
    with open(file_path, "r+") as file:
        contents = [line.rstrip('\n') for line in file]
        pairs = []
        temp = []
        for line in contents:
            if line == "":
                pairs.append(temp)
                temp = []
            else:
                temp.append(eval(line))
    return pairs


def compare(left: int, right: int) -> str:
    if isinstance(left, int) and isinstance(right, int):
        if left < right: return "ordered"
        if left > right: return "unordered"
        return "equal"
    if isinstance(left, list) and isinstance(right, int):
        return compare(left, [right])
    if isinstance(left, int) and isinstance(right, list):
        return compare([left], right)
    if isinstance(left, list) and isinstance(right, list):
        i = 0
        while i < len(left) and i < len(right):
            comp = compare(left[i], right[i])
            if comp == "ordered" or comp == "unordered":
                return comp
            i += 1
        if i == len(left) and len(left) < len(right):
            return "ordered"
        if i == len(right) and len(right) < len(left):
            return "unordered"


def bubble_sort(arr: list[list[int]]) -> list[list[int]]:
    new_arr = []
    while len(arr) > 1:
        temp = [arr[0]]
        i = 1
        while i < len(arr):
            # print(f"{temp[0]} ---- {arr[i]}")
            comp = compare(temp[0], arr[i])
            if comp == "unordered":
                temp[0] = arr[i]
            i += 1
        new_arr.append(temp[0])
        arr.remove(temp[0])
    new_arr.append(arr[0])  # appending last element from array
    return new_arr


def part1(pairs: list[list[int]]) -> None:
    index_sum = 0
    for idx, p in enumerate(pairs):
        if compare(p[0], p[1]) == "ordered":
            index_sum += (idx + 1)
    print(f"#\t{cur_day} part1 answer is: {index_sum}\t\t\t\t\t#")


def part2(pairs: list[list[int]]) -> None:
    distress_signal = 1
    items = [[[2]], [[6]]]
    for pair in pairs:
        items.append(pair[0])
        items.append(pair[1])
    items = bubble_sort(items)  # should be quick sort, but it's getting late
    for idx, i in enumerate(items):
        # print(idx+1, i)
        if i == [[2]]:
            distress_signal *= (idx+1)
        if i == [[6]]:
            distress_signal *= (idx+1)
    print(f"#\t{cur_day} part2 answer is: {distress_signal}\t\t\t\t#")


def main():
    pairs = read_file(input_path)
    part1(pairs)
    part2(pairs)
    print("#################################################")
