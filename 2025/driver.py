"""
Advent of Code 2025 driver
Automatically runs all or specific day_* modules in this folder.
"""

from pathlib import Path
import importlib
import argparse
import time


def banner(text, char="#", color="\033[92m", bold="\033[1m", end="\033[0m"):
    line = char * 50
    print(line)
    print(f"{char}{color}{bold}{text.center(48)}{end}{char}")
    print(line)


def print_summary(results, total):
    print("\n" + "#" * 50)
    print(f"{'Execution Summary':^50}")
    print("#" * 50)
    for name, t in results:
        print(f"{name:>10}: {t:6.2f}s")
    print("-" * 50)
    print(f"{'Total':>10}: {total:6.2f}s")


def run_day(day_folder: Path, use_test: bool) -> tuple[str, float] | None:
    """Import and run a single day_* module, returning timing info."""
    mod_name = f"{day_folder.name}.main"
    try:
        module = importlib.import_module(mod_name)
        print(f"\n--- Running {mod_name} ---")

        input_file = day_folder / ("input-test.txt" if use_test else "input.txt")
        if not input_file.exists():
            print(f"Missing input file for {day_folder.name}, skipping.")
            return None

        t0 = time.time()
        module.main(input_file)
        return day_folder.name, time.time() - t0
    except ModuleNotFoundError:
        print(f"{mod_name} not found.")
    except AttributeError:
        print(f"{mod_name} missing main().")
    return None


def run_all(use_test=False, single_day=None):
    base = Path(__file__).parent
    results = []
    start = time.time()

    day_folders = sorted(base.glob("day_*"))
    if not single_day:
        for folder in day_folders:
            result = run_day(folder, use_test)
            if result:
                results.append(result)
    else:
        match = next((d for d in day_folders if d.name == f"day_{single_day:02d}"), None)
        if match:
            result = run_day(match, use_test)
            if result:
                results.append(result)
        else:
            print(f"No such day folder: day-{single_day:02d}")

    print_summary(results, time.time() - start)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Advent of Code 2025 driver")
    parser.add_argument("--test", action="store_true", help="use test inputs")
    parser.add_argument("--day", type=int, help="run only a specific day (e.g., 5)")
    args = parser.parse_args()

    banner("ADVENT OF CODE - 2025")
    banner("Python Solution by Máté Molnár")

    run_all(use_test=args.test, single_day=args.day)

