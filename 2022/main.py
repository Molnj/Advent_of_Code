# importing Src package (must have __init__.py)
import sys
import time

start_time = time.time()
sys.path.insert(0, '/the/folder/path/name-package/')

from Src import day01, day02, day03, day04, day05, day06, day07, day08, day09

if __name__ == "__main__":
    print("#########################################")
    print("#\t\t  ADVENT OF CODE - 2022\t\t\t#")
    print("#\t\t\t Python Solution\t\t\t#")
    print("#########################################")
    day01.main()
    day02.main()
    day03.main()
    day04.main()
    day05.main()
    day06.main()
    day07.main()
    day08.main()
    day09.main()
    print(f"#\tComplete execution time: {((time.time() - start_time)*1000):.2f} ms\t#")
    print("#########################################")
