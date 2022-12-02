import os

file_dir = os.path.dirname(os.path.realpath('__file__'))
file_name = os.path.join(file_dir, '../txt_inputs/day01.txt')
file_name = os.path.abspath(os.path.realpath(file_name))


def read_file(file_name):
    with open(file_name, "r+") as file:
        contents = file.readlines()
    return contents
    
    
def part1():
    max_kcal = 0
    curr_val = 0;
    for line in read_file(file_name):
        line = line.strip()
        if len(line) != 0:
            curr_val += int(line)
        else:
            if curr_val > max_kcal:
                max_kcal = curr_val
            curr_val = 0
    print(f"day01 part1 answer is: {max_kcal}")


def part2():
    kcal_list = []
    curr_val = 0;
    for line in read_file(file_name):
        line = line.strip()
        if len(line) != 0:
            curr_val += int(line)
        else:
            kcal_list.append(curr_val)
            curr_val = 0
    top3_sum = sum(sorted(kcal_list, reverse=True)[:3])
    print(f"day01 part2 answer is: {top3_sum}")


def main():
    print("#################################")
    part1()
    part2()
    print("#################################")