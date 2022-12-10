import os

file_dir = os.path.dirname(os.path.realpath('__file__'))
file_name = os.path.join(file_dir, '../txt_inputs/day02.txt')
file_name = os.path.abspath(os.path.realpath(file_name))


def read_file(file_path: str) -> str:
    with open(file_path, "r+") as file:
        contents = file.readlines()
    return contents

    
def part1(txt: str) -> None:
    score = 0
    results = {    # points for outcome + points for shape
        "A X": 3+1,
        "A Y": 6+2,
        "A Z": 0+3,
        "B X": 0+1,
        "B Y": 3+2,
        "B Z": 6+3,
        "C X": 6+1,
        "C Y": 0+2,
        "C Z": 3+3
    }
    for line in txt:
        line = line.strip()
        score += results[line]
    print(f"#\tday02 part1 answer is: {score}\t\t\t\t#")


def part2(txt: str) -> None:
    score = 0
    results = {    # points for outcome + points for shape
        "A X": 0+3,
        "A Y": 3+1,
        "A Z": 6+2,
        "B X": 0+1,
        "B Y": 3+2,
        "B Z": 6+3,
        "C X": 0+2,
        "C Y": 3+3,
        "C Z": 6+1
    }
    for line in txt:
        line = line.strip()
        score += results[line]
    print(f"#\tday02 part2 answer is: {score}\t\t\t\t#")


def main():
    txt_file = read_file(file_name)
    part1(txt_file)
    part2(txt_file)
    print("#################################################")
