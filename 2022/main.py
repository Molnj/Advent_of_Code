"""
    Driver file for my AOC 2022 project
"""

import sys
import time

from src import \
    day01, day02, day03, day04, day05, day06, day07, \
    day08, day09, day10, day11, day12, day13, day14, \
    day15, day16, day17, day18, day19, day20, day21, \
    day22, day23, day24, day25


start_time = time.time()    #   timing execution time (timeit is alternative)
sys.path.insert(0, '/the/folder/path/name-package/')

GREEN = '\033[92m'
BOLD = '\033[1m'
END = '\033[0m'

if __name__ == "__main__":
    print("#"*50)
    print("#" + GREEN + BOLD + f"{'ADVENT OF CODE - 2022': ^48}" + END + "#")
    print("#" + GREEN + BOLD + f"{'Python Solution': ^48}" + END + "#")
    print("#"*50)
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
    day12.main()
    day13.main()
    day14.main()
    # day15.main()
    # day16.main()
    day17.main()
    day18.main()
    # day19.main()
    day20.main()
    day21.main()
    day22.main()
    day23.main()
    day24.main()
    day25.main()

    elapsed_time_s = (time.time() - start_time)
    print("#"*50)
    print("#" + GREEN + BOLD + f"{'Complete execution time:': ^48}" + END + "#")
    print("#" + GREEN + BOLD + f"{f'{elapsed_time_s:.2f} s': ^48}" + END + "#")
    print("#"*50)
