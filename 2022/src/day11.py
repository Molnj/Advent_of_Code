"""
AOC 2022 day11 - Monkey in the Middle
    [ https://adventofcode.com/2022/day/11 ]
    - pt1: 90294
    - pt2: 18170818354
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)

monkeys = []


class Monke:
    """ class describing monkeys """
    def __init__(self, name: int, items: list, operation: str, test: tuple):
        self.name = name
        self.items = items
        self.operation = operation
        self.test = test
        self.inspect_cnt = 0


def read_file(file_path: str) -> None:
    """ parse input txt into Monke(y) objects """
    global monkeys
    monkeys = []
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]
    monkey_lines = []
    temp = []
    for line in contents:
        if line == "":
            monkey_lines.append(temp)
            temp = []
        else:
            temp.append(line)

    # create monkey objects
    for monkey in monkey_lines:
        name = int(monkey[0].split()[1][0])
        items = [list(map(int, monkey[1].split(": ")[1].split(", ")))][0]
        operation = monkey[2].split(" = ")[1]
        test = (int(monkey[3].split(" ")[-1]),
                int(monkey[4].split(" ")[-1]),
                int(monkey[5].split(" ")[-1]))
        monke = Monke(name, items, operation, test)
        monkeys.append(monke)


def part1() -> None:
    """ part 1 solution """
    monkey_business = 0
    for _ in range(20):
        for monke in monkeys:
            for old in monke.items:
                new = eval(monke.operation)
                monke.inspect_cnt += 1
                new = new // 3
                if new % monke.test[0] == 0:
                    monkeys[monke.test[1]].items.append(new)
                else:
                    monkeys[monke.test[2]].items.append(new)
                monke.items = []

    businesses = []
    for monke in monkeys:
        businesses.append(monke.inspect_cnt)
        businesses.sort(reverse=True)
    monkey_business = businesses[0] * businesses[1]

    print(f"#{f'  {cur_day} part1 answer is: {monkey_business}': <48}#")


def part2() -> None:
    """
        part 2 solution
            mod - Modular Arithmetic
            without the // 3 worry division, the numbers get exponentially big
            worry is important at the tests, where "worry % XX == 0" is checked
            XX is different by all the monkeys
            if we multiply these XX together from all the monkeys, then we get a common modulo
            dividing the worry level with this common modulo and only passing th remainder ==
            == gets the same results at checks (even after operations) as passing the whole number
    """
    commond_mod = 1
    for monke in monkeys:
        commond_mod *= monke.test[0]

    monkey_business = 0
    for _ in range(10000):
        for monke in monkeys:
            for old in monke.items:
                new = eval(monke.operation)
                monke.inspect_cnt += 1
                if new % monke.test[0] == 0:
                    new %= commond_mod
                    monkeys[monke.test[1]].items.append(new)
                else:
                    new %= commond_mod
                    monkeys[monke.test[2]].items.append(new)
                monke.items = []

    businesses = []
    for monke in monkeys:
        businesses.append(monke.inspect_cnt)
        businesses.sort(reverse=True)
    monkey_business = businesses[0] * businesses[1]
    print(f"#{f'  {cur_day} part2 answer is: {monkey_business}': <48}#")


def main():
    """ day11 main"""
    read_file(input_path)
    part1()
    read_file(input_path)
    part2()
    print("#"*50)