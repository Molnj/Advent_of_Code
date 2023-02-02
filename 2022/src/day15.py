"""
AOC 2022 day15 - Beacon Exclusion Zone
    [ https://adventofcode.com/2022/day/15 ]
    - pt1: 5564017
    - pt2: 11558423398893
"""

import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.abspath(os.path.join(os.getcwd(), os.pardir))
input_path = os.path.join(file_dir, f'txt_inputs/{cur_day}.txt')
input_path = os.path.realpath(input_path)
input_path = os.path.abspath(input_path)


def read_file(file_path: str) -> list[str]:
    """ parse input txt line-by-line into list of strings """
    with open(file_path, mode="r+", encoding="utf-8") as file:
        contents = [line.rstrip('\n') for line in file]
    return contents


def get_sensors(lines: list[str]) -> list[tuple[int]]:
    """ determining all sensor coordinates with their reach distances"""
    sensors = []
    for line in lines:
        words = line.split(" ")
        sensor_x = int(words[2].split("=")[1][:-1])
        sensor_y = int(words[3].split("=")[1][:-1])
        beacon_x = int(words[8].split("=")[1][:-1])
        beacon_y = int(words[9].split("=")[1])
        dist = abs(sensor_x - beacon_x) + abs(sensor_y - beacon_y)
        sensors.append((sensor_x, sensor_y, dist))
    return sensors


def get_sensor_radiuses(sensors: list[tuple[int]]) -> list[tuple[int]]:
    """ getting all coordinates that form outer shell of sensored areas """
    radius = []
    for sensor in sensors:
        sensor_x, sensor_y, dist = sensor
        rad = []
        for i in range(dist):
            rad.append((sensor_x+i, sensor_y-(dist-i)))      # upper right side
            rad.append((sensor_x+(dist-i), sensor_y+i))      # lower right side
            rad.append((sensor_x-i, sensor_y+(dist-i)))      # lower left side
            rad.append((sensor_x-(dist-i), sensor_y-i))      # lower left side
        radius.append(rad)
    return radius


def part1(radius: list[tuple[int, int], int]) -> None:
    """ part 1 solution """
    covered = []
    height = 2_000_000

    overlaps = []
    for rad in radius:
        temp = []
        for coord in rad:
            if coord[1] == height:
                temp.append(coord[0])
        if len(temp) != 0:
            temp.sort()
            overlaps.append(temp)

    for i in overlaps:
        if len(i) == 1:
            covered.append(i[0])
        else:
            while i[0] <= i[1]:
                covered.append(i[0])
                i[0] += 1
    print(f"#{f'  {cur_day} part1 answer is: {len(set(covered))-1}': <48}#")


def part2(radius: list[tuple[int, int], int]) -> None:
    """ part 2 solution """
    tuning_frequency = 0
    all_covered = []
    outskirt = []
    for rad in radius:
        for coord in rad:
            all_covered.append(coord)
    set(all_covered)
    for rad in radius:
        cnt = 0
        for coord in rad:
            if cnt > 3:
                cnt = 0
            x_pos = coord[0]
            y_pos = coord[1]
            if (0 <= x_pos <= 4_000_000) and (0 <= y_pos <= 4_000_000):
                if cnt == 0:
                    y_pos -= 1
                elif cnt == 1:
                    x_pos += 1
                elif cnt == 2:
                    y_pos += 1
                elif cnt == 3:
                    x_pos -= 1
                outskirt.append((x_pos, y_pos))
            cnt += 1
    outskirt.sort()
    for i in range(len(outskirt)-3):
        if outskirt[i] == outskirt[i+1] \
                and outskirt[i] == outskirt[i+2] \
                and outskirt[i] == outskirt[i+3]:
            tuning_frequency = outskirt[i][0] * 4_000_000 + outskirt[i][1]
            #print(outskirt[i][0], outskirt[i][1])
            break
    print(f"#{f'  {cur_day} part2 answer is: {tuning_frequency}': <48}#")


def main():
    """ day15 main """
    lines = read_file(input_path)
    sensors = get_sensors(lines)
    radius = get_sensor_radiuses(sensors)
    part1(radius)
    part2(radius)
    print("##"*50)
