import os

cur_day = os.path.basename(__file__)[:-3]
file_dir = os.path.dirname(os.path.realpath('__file__'))
input_path = os.path.join(file_dir, f'../txt_inputs/{cur_day}.txt')
input_path = os.path.abspath(os.path.realpath(input_path))

class Found(Exception): pass


def read_file(file_path: str) -> list[str]:
    with open(file_path, "r+") as file:
        contents = [line.rstrip('\n') for line in file]
    return contents


def get_sensors(lines: list[str]) -> list[tuple[int]]:
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
    radius = []
    for s in sensors:
        sx, sy, d = s
        r = []
        for i in range(d):
            r.append((sx+i, sy-(d-i)))      # upper right side
            r.append((sx+(d-i), sy+i))      # lower right side
            r.append((sx-i, sy+(d-i)))      # lower left side
            r.append((sx-(d-i), sy-i))      # lower left side
        radius.append(r)
    return radius


def part1(radius: list[tuple[int, int], int]) -> None:
    covered = []
    Y = 2_000_000

    overlaps = []
    for r in radius:
        temp = []
        for coord in r:
            if coord[1] == Y:
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

    print(f"#\t{cur_day} part1 answer is: {len(set(covered))-1}\t\t\t\t\t#")


def part2(radius: list[tuple[int, int], int]) -> None:
    tuning_frequency = 0
    all_covered = []
    outskirt = []
    for r in radius:
        for c in r:
            all_covered.append(c)
    set(all_covered)
    for r in radius:
        cnt = 0
        for coord in r:
            if cnt > 3:
                cnt = 0
            x = coord[0]
            y = coord[1]
            if (0 <= x <= 4_000_000) and (0 <= y <= 4_000_000):
                if cnt == 0:    y -= 1
                elif cnt == 1:  x += 1
                elif cnt == 2:  y += 1
                elif cnt == 3:  x -= 1
                outskirt.append((x, y))
            cnt += 1
    outskirt.sort()
    for i in range(len(outskirt)-3):
        if outskirt[i] == outskirt[i+1] \
                and outskirt[i] == outskirt[i+2] \
                and outskirt[i] == outskirt[i+3]:
            tuning_frequency = outskirt[i][0] * 4_000_000 + outskirt[i][1]
            #print(outskirt[i][0], outskirt[i][1])
            break
    print(f"#\t{cur_day} part2 answer is: {tuning_frequency}\t\t\t\t\t#")


def main():
    lines = read_file(input_path)
    sensors = get_sensors(lines)
    radius = get_sensor_radiuses(sensors)
    # part1(radius)
    part2(radius)
    print("#################################################")