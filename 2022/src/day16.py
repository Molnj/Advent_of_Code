"""
AOC 2022 day16 - Proboscidea Volcanium
    [ https://adventofcode.com/2022/day/16 ]
    - pt1:
    - pt2:
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.abspath(os.path.join(os.getcwd(), os.pardir))
input_path = os.path.join(file_dir, f'txt_inputs_test/{cur_day}.txt')    # using \ as 1st char in str represents absoulte path (all before it wouldl be discarded)
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path: str) -> list[dict]:
    """ parse input txt file 
    uses BFS to create graph - deleting empty nodes and weighing edges accordingly"""
    valves = {}
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]
        for line in contents:
            valve = line.split()[1]
            flow = int(line.split()[4].split('=')[1][:-1])
            neighbors = [n[:2] for n in line.split()[9:]]
            valves[valve] = [flow, neighbors]
    
    # BFSs for all nodes
    dists = {}
    for valve in valves:
        # ignore empty nodes (except AA)
        if valve != "AA" and valves[valve][0] == 0:
            continue

        dists[valve] = {}
        visited = {valve}
        queue = [(valve, 0)]
        while queue:
            node = queue.pop(0)
            pos, dist = node
            for neighbor in valves[pos][1]:
                if neighbor in visited:
                    continue
                visited.add(neighbor)
                if valves[neighbor][0] != 0:
                    dists[valve][neighbor] = dist + 1
                queue.append((neighbor, dist+1))

    return (dists)


def dfs(time, valve, bitmask):
    if (time, valve, bitmask) in cache:
        return cache[(time, valve, bitmask)]
    
    maxval = 0
    for neighbor in dists[valve]:
        bit = 1 << indices[neighbor]
        if bitmask & bit:
            continue
        remtime = time - dists[valve][neighbor] - 1
        if remtime <= 0:
            continue
        maxval = max(maxval, dfs(remtime, neighbor, bitmask | bit) + valves[neighbor] * remtime)
        
    cache[(time, valve, bitmask)] = maxval
    return maxval

    
def part1(graph: dict) -> None:
    """ part 1 solution """
    max_flow = 0
    time = 30
    max_flow = dfs(graph, time)
    
    print(f"#{f'  {cur_day} part1 answer is: {max_flow}': <48}#") 


def part2(graph: dict) -> None:
    """ part 2 solution """
    max_flow = 0
    time = 26
    max_flow = dfs(graph, time)
    print(f"#{f'  {cur_day} part2 answer is: {max_flow}': <48}#")


def main():
    """ day16 main """
    graph = read_file(input_path)
    [print(key,':',value) for key, value in graph.items()]
    part1(graph)
    #part2(graph)
    print("#"*50)

main()