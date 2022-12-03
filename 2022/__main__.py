# importing Src package (must have __init__.py)
import sys
sys.path.insert(0, '/the/folder/path/name-package/')

from Src import day01, day02, day03
if __name__ == "__main__":
    day01.main()
    day02.main()
    day03.main()
