"""
AOC 2022 day16 - Proboscidea Volcanium
    [ https://adventofcode.com/2022/day/16 ]
    - pt1:
    - pt2:
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'txt_inputs_test/{cur_day}.txt')    # using \ as 1st char in str represents absoulte path (all before it wouldl be discarded)
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)

flows = set()


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

        dists[valve] = []
        dists[valve].append(valves[valve][0]    )
        dists[valve]["flow"] = valves[valve][0]     # TODO could store "flow" better somehow
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


def bfs(graph: dict, node: str, time: int) -> int:
    flow = 0
    queue = [[node, flow, time]]
    visited = []
    for next, dist in graph[node].items():
        print(next)
    while queue:
        next_node = queue.pop(0)
        node_ = next_node[0]
        flow_ = next_node[1]
        time_ = next_node[2]
        # TODO - a mostnai flow nem jó, kell egy külön dict h mi mennyi, vagy 3 elemes listák kell legyenek a kis dict elemek
        if node not in visited:
            if :
                grid[y_start][x_start] = start_val  # reset 'S' from 'a' back to 'S'
                return distance
            for node_y2, node_x2 in ((node_y+1, node_x), (node_y-1, node_x),
                                     (node_y, node_x+1), (node_y, node_x-1)):
                if 0 <= node_x2 < width and 0 <= node_y2 < height:
                    next_square = grid[node_y2][node_x2]
                    if next_square == end_val:
                        next_square = ord('z')-ord('a')+1  # correct 'E' to 'z'
                    if next_square <= grid[node_y][node_x] + 1:
                        queue.append([(node_y2, node_x2), distance])
    return -1


def dfs(visited, graph, node, time, flow_rate):
    if node not in visited:
        if time < 0:
            flows.add(flow_rate)
        else:
            cur_flow = 0
            visited.add(node)
            for next, dist in graph[node].items():
                print(flows)
                if next == "flow":
                    cur_flow = dist
                    flow_rate += cur_flow * (time-1)  # not dist, but flow rate
                    print(flow_rate)
                else:
                    if cur_flow == 0:
                        dfs(visited, graph, next, time-dist, flow_rate)
                    else:
                        dfs(visited, graph, next, time-dist-1, flow_rate) 
    else:
        flows.add(flow_rate)           


def part1(graph: dict) -> None:
    """ part 1 solution """
    max_flow = 0
    bfs(graph, "AA", 30)
    #visited = set()
    #dfs(visited, graph, "AA", 30, 0)
    print(flows)
    print(f"#{f'  {cur_day} part1 answer is: {max_flow}': <48}#") 


def part2(graph: dict) -> None:
    """ part 2 solution """
    max_flow = 0
    time = 26
    max_flow = dfs(graph, "AA", time)
    print(f"#{f'  {cur_day} part2 answer is: {max_flow}': <48}#")


def main():
    """ day16 main """
    graph = read_file(input_path)
    [print(key,':',value) for key, value in graph.items()]
    part1(graph)
    #part2(graph)
    print("#"*50)
