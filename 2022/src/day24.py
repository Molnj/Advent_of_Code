"""
AOC 2022 day24 -
    [ https://adventofcode.com/2022/day/24 ]
    - pt1: 314
    - pt2: 896
    - lessons:
        priority que (although turns out it won't work with BFS)
        even when same position might repeat in BFS (eg.: waiting in place), same pos with same time can't
"""

import os
import math

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.abspath(os.path.join(os.getcwd(), os.pardir))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path):
    """ parse input txt file """
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]
    return contents


def gcd(a,b):
    """ return GCD (Greatest Common Divisor) of a and b """
    if a == 0:
        return b
    return gcd(b%a, a)


def lcm(a,b):
    """ return LCM (Least Common Multiple) of a and b """
    return (a // gcd(a,b))* b


def predict_storm(valley):
    all_valley_states = []
    cur_valles_state = []
    num_of_states = lcm(len(valley)-2, len(valley[0])-2)
    blizzards = {
        '^': [-1, 0],
        'v': [1, 0],
        '<': [0, -1],
        '>': [0, 1]
    }

    # init valley
    temp = []
    for y, line in enumerate(valley):
        for x, char in enumerate(line):
            if char in blizzards:
                cur_valles_state.append([y, x, blizzards[char]])
                temp.append((y, x))
    all_valley_states.append(temp)

    # perpare all possible blizzard configuration
    for _ in range(num_of_states-1):
        temp = []
        for state in cur_valles_state:
            y, x, dir = state
            y += dir[0]
            x += dir[1]
            if y == 0:                  y = len(valley) - 2
            if y == len(valley) - 1:    y = 1
            if x == 0:                  x = len(valley[0]) - 2
            if x == len(valley[0]) - 1: x = 1
            temp.append((y, x))
            state[0] = y
            state[1] = x
        all_valley_states.append(set(temp))     # converting to sets, to get fewer members
            
    # print(*all_valley_states, sep='\n') # ez legyen lokál, végigozgatnin őt range lcm-en és csak az xy menjen ki a valleystate-be
    return all_valley_states


# TODO - how to optimize this?
def bfs(valley_states: list[set], valley, start: tuple, end_pos: tuple, time: int) -> int:
    """ 
        BFS for maze with moving walls
        not tracking visited nodes, since stopping or backstepping might be useful
        returns time needed to escape maze
    """
    seen = [] # tracking ((x,y), time) nodes - coordinate mighr be repeated, but not with same time
    myQueue = []
    myQueue.append((start, time))
    while myQueue:
        # pop next item from priority queue
        node = myQueue.pop(0)
        
        # discard node if already seen
        if node in seen:
            continue
        # add node to seen list
        seen.append(node)

        time = node[1] + 1
        pos = node[0]
        pos_y, pos_x = pos
        
        # managing neighbours (only in boundary)
        for pos_y2, pos_x2 in ((pos_y+1, pos_x), (pos_y, pos_x+1), (pos_y-1, pos_x), (pos_y, pos_x-1)):
            # ENDPOINT FOUND
            if (pos_y2, pos_x2) == end_pos:
                # print(f"reached: {end_pos}")
                return time
            # adding neighbor pos to que (if not in blizzard)
            if (pos_y2, pos_x2) not in valley_states[time % len(valley_states)]:
                if (1 <= pos_y2 < len(valley)-1) and (1 <= pos_x2 < len(valley[0])-1) \
                        and (pos_y2, pos_x2) not in valley_states[time % len(valley_states)]:
                    myQueue.append(((pos_y2, pos_x2), time))
        # managing current pos - adding it to que (since stopping might be needed)
        if pos not in valley_states[time % len(valley_states)]:
            myQueue.append((pos, time))
    return -1


def part1(valley, valley_states) -> None:
    """ part 1 solution """
    time = 0
    start_pos = (0, 1)
    end_pos = ( len(valley)-1, len(valley[0])-2 )

    time = bfs(valley_states, valley, start_pos, end_pos, time)
    print(f"#{f'  {cur_day} part1 answer is: {time}': <48}#")


def part2(valley, valley_states) -> None:
    """ part 2 solution """
    time = 0
    start_pos = (0, 1)
    end_pos = ( len(valley)-1, len(valley[0])-2 )

    time = bfs(valley_states, valley, start_pos, end_pos, time)
    time = bfs(valley_states, valley, end_pos, start_pos, time)
    time = bfs(valley_states, valley, start_pos, end_pos, time)
    print(f"#{f'  {cur_day} part2 answer is: {time}': <48}#")


def main():
    """ day24 main """
    valley = read_file(input_path)
    valley_states = predict_storm(valley)
    part1(valley, valley_states)
    part2(valley, valley_states)
    print("#"*50)

main()





"""

# A simple implementation of Priority Queue using queue.
class PriorityQueue(object):
    def __init__(self, end_pos):
        self.queue = []
        self.end_pos = end_pos

    def __str__(self):
        return ' '.join([str(i) for i in self.queue])

    # for checking if the queue is empty
    def isEmpty(self):
        return len(self.queue) == 0

    # for inserting an element in the queue
    def push_(self, data):
        self.queue.append(data)

    # for popping an element based on Priority
    def pop_(self):
        try:
            min_idx = 0
            for i in range(len(self.queue)):
                # prioritizing closer coordinates to end point (using Eucleidan distance)
                cur_dist = math.sqrt( (self.end_pos[0] - self.queue[i][0][0])**2 + (self.end_pos[1] - self.queue[i][0][1])**2 )
                min_dist = math.sqrt( (self.end_pos[0] - self.queue[min_idx][0][0])**2 + (self.end_pos[1] - self.queue[min_idx][0][1])**2 )
                cur_time = self.queue[i][1]
                min_time = self.queue[min_idx][1]
                if cur_dist + cur_time < min_dist + min_time:
                    min_idx = i
                # prioritizing lower time (second prio)
                if cur_dist == min_dist:
                    if self.queue[i][1] < self.queue[min_idx][1]:
                        min_idx = i
            item = self.queue[min_idx]
            del self.queue[min_idx]
            return item
        except IndexError:
            print()
            exit()

"""