import os

file_dir = os.path.dirname(os.path.realpath('__file__'))
file_name = os.path.join(file_dir, '../txt_inputs/day01.txt')
file_name = os.path.abspath(os.path.realpath(file_name))


def read_file(file_name):
    with open(file_name, "r+") as file:
        contents = file.read()
    print(contents)
    
    
def main():
    read_file(file_name)


if __name__ == "__main__":
    main()