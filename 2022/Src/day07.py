"""
AOC 2022 day07 - No Space Left On Device
    [ https://adventofcode.com/2022/day/7]
    - pt1: 1444896
    - pt2: 404395
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)

dir_sizes = []
TOTAL_SPACE = 70000000
FREE_SPACE_NEEDED = 30000000

class File:
    """ Class simulating Files """
    def __init__(self, file_name: str, file_size: int):
        """ initializing file """
        self.name = file_name
        self.size = file_size

    def __str__(self, level=0) -> str:
        """ formatting for printing directory tree """
        ret = "\t"*level+" - "+self.name+f" (file, size={self.size})\n"
        return ret

    def get_name(self):
        """ filler method for pylint"""
        return self.name

class Directory:
    """ Class simulating Directories """
    def __init__(self, dir_name: str, dir_parent: str):
        """ initializing directory """
        self.name = dir_name
        self.parent = dir_parent
        self.sub_dirs = []
        self.files = []

    def add_dir(self, sub_dir):
        """ adds sub-directory to directory"""
        self.sub_dirs.append(sub_dir)

    def add_file(self, file: File):
        """ adds file to directory """
        self.files.append(file)

    def size(self) -> int:
        """ calculates directory size """
        size = 0
        for sub_dir in self.sub_dirs:
            size += sub_dir.size()
        for file in self.files:
            size += file.size
        return size

    def __str__(self, level=0) -> str:
        """ formatting for printing directory tree """
        ret = "\t"*level+" - "+self.name+" (dir)\n"
        for file in self.files:
            ret += file.__str__(level + 1)
        for sub in self.sub_dirs:
            ret += sub.__str__(level+1)
        return ret


def read_file(file_path: str) -> list[str]:
    """ parse input txt line-by-line into list of strings """
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]
    return contents


def parse_file_system(txt: list[str]) -> Directory:
    """
        :param txt: txt input lne-by-line
        :return: creates a tree DS consisting from directories and files - returns root dir
    """
    root = Directory("File System", "")
    cur_dir = root
    lines = [line.strip() for line in txt]  # get iterable input
    for line in lines:
        if line.startswith("$"):
            if "cd" in line:
                dir_part = line.split(" ")[2]
                if dir_part == "..":
                    cur_dir = cur_dir.parent
                else:
                    new_dir = Directory(dir_part, cur_dir)
                    cur_dir.add_dir(new_dir)
                    cur_dir = new_dir
            elif "ls" in line:
                pass
            else:
                raise Exception(f"ERROR: Unrecognized $ command in line: {line}")
        else:
            if line.split(" ")[0] == "dir":
                pass
            elif line.split(" ")[0].isnumeric():
                file_size, file_name = line.split(" ")
                cur_dir.add_file(File(file_name, int(file_size)))
            else:
                raise Exception(f"ERROR: Can't parse line: {line}")
    return root


def get_dir_sizes(directory: Directory):
    """ recursively get the size of given directory (with sub-dirs and files) """
    for sub in directory.sub_dirs:
        dir_sizes.append(sub.size())
        get_dir_sizes(sub)
    return dir_sizes


def part1() -> None:
    """ part 1 solution """
    solution = 0
    for size in dir_sizes:
        if size < 100000:
            solution += size
    print(f"#{f'  {cur_day} part1 answer is: {solution}': <48}#")


def part2(root: Directory) -> None:
    """ part 2 solution """
    solution = 0
    space_used = root.size()
    space_to_be_deleted = FREE_SPACE_NEEDED - (TOTAL_SPACE - space_used)
    dir_sizes.sort()
    for size in dir_sizes:
        if size >= space_to_be_deleted:
            solution = size
            break
    print(f"#{f'  {cur_day} part2 answer is: {solution}': <48}#")


def main():
    """ day07 main """
    txt_file = read_file(input_path)
    root = parse_file_system(txt_file)
    get_dir_sizes(root)
    part1()
    part2(root)
    print("#"*50)
