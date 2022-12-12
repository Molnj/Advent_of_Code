# importing Src package (must have __init__.py)
import sys
import time

start_time = time.time()
sys.path.insert(0, '/the/folder/path/name-package/')


class Color:
    PURPLE = '\033[95m'
    CYAN = '\033[96m'
    DARKCYAN = '\033[36m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    END = '\033[0m'


from Src import day01, day02, day03, day04, day05, day06, day07, day08, day09, day10, day11

if __name__ == "__main__":
    print("#################################################")
    print("#" + Color.GREEN + Color.BOLD + "\t\t\t  ADVENT OF CODE - 2022\t\t\t\t" + Color.END + "#")
    print("#" + Color.GREEN + Color.BOLD + "\t\t\t\t Python Solution\t\t\t\t" + Color.END + "#")
    print("#################################################")
    day01.main()
    day02.main()
    day03.main()
    day04.main()
    day05.main()
    day06.main()
    day07.main()
    day08.main()
    day09.main()
    day10.main()
    day11.main()

    elapsed_time_ms = (time.time() - start_time) * 1000
    print("#" + Color.GREEN + Color.BOLD + ("\t" * 3) + "Complete execution time:" + ("\t" * 3) + Color.END + "#")
    print("#" + Color.GREEN + Color.BOLD + "\t" * 5 + f"{elapsed_time_ms:.2f} ms" + "\t" * 5 + Color.END + "#")
    print("#################################################")
