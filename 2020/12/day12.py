import math


def read_file(file_name: str) -> list:
    return [(line.strip('\n')[0], int(line.strip('\n')[1:])) for line in open(file_name, 'r')]


def move_ship(instructions: list) -> dict:
    """
    cos(0) = 1: x
    sin(0) = 0: y
    cos(-90) = cos(270) = 0: x
    sin(-90) = sin(270) = -1: y
    There's only turns of 90 degrees meaning that we can use x += 10*cos(deg) and y += 10*sin(deg) when F10
    N3 just plainly increases y: y += 3
    S3 just plainly decreases y: y -= 3
    E3 just plainly increases x: x += 3
    W3 just plainly decreases x: x -= 3
    """
    position = {'x': 0, 'y': 0, 'deg': 0}
    for instruction_tuple in instructions:
        direction = instruction_tuple[0]
        amount = instruction_tuple[1]

        if direction == 'F':
            position['x'] += amount * math.cos(position['deg'])
            position['y'] += amount * math.sin(position['deg'])

        elif direction == 'E':
            position['x'] += amount
        elif direction == 'W':
            position['x'] -= amount
        elif direction == 'N':
            position['y'] += amount
        elif direction == 'S':
            position['y'] -= amount

        elif direction == 'R':
            position['deg'] -= amount * math.pi/180
        elif direction == 'L':
            position['deg'] += amount * math.pi/180
    return position


def use_waypoint_move_ship(instructions: list) -> dict:
    """
    Using the rotation matrix here we just need to make sure we change incase of 'L' (counter-clockwise) or 'R' (clockwise)
    : https://en.wikipedia.org/wiki/Rotation_matrix
    x = xcos(rad) - ysin(rad)
    y = xsin(rad) + ycos(rad)
    N3 just plainly increases y: y += 3
    S3 just plainly decreases y: y -= 3
    E3 just plainly increases x: x += 3
    W3 just plainly decreases x: x -= 3
    """
    ship_position = {'x': 0, 'y': 0}
    waypoint_position = {'x': 10, 'y': 1}
    for instruction_tuple in instructions:
        direction = instruction_tuple[0]
        amount = instruction_tuple[1]

        if direction == 'F':
            ship_position['x'] += amount * waypoint_position['x']
            ship_position['y'] += amount * waypoint_position['y']

        elif direction == 'E':
            waypoint_position['x'] += amount
        elif direction == 'W':
            waypoint_position['x'] -= amount
        elif direction == 'N':
            waypoint_position['y'] += amount
        elif direction == 'S':
            waypoint_position['y'] -= amount

        elif direction == 'R':
            rad = amount * math.pi / 180
            old_x = waypoint_position['x']
            waypoint_position['x'] = round(waypoint_position['x'] * math.cos(rad) + waypoint_position['y'] * math.sin(rad))
            waypoint_position['y'] = round(waypoint_position['y'] * math.cos(rad) - old_x * math.sin(rad))

        elif direction == 'L':
            rad = amount * math.pi / 180
            old_x = waypoint_position['x']
            waypoint_position['x'] = round(waypoint_position['x'] * math.cos(rad) - waypoint_position['y'] * math.sin(rad))
            waypoint_position['y'] = round(waypoint_position['y'] * math.cos(rad) + old_x * math.sin(rad))
    print(ship_position, waypoint_position)
    return ship_position


def calc_manhattan_distance(ship_position: dict) -> int:
    return round(abs(ship_position['x']) + abs(ship_position['y']))


if __name__ == '__main__':
    file_name = 'input.txt'
    instructions = read_file(file_name)
    part_1 = calc_manhattan_distance(move_ship(instructions))
    part_2 = calc_manhattan_distance(use_waypoint_move_ship(instructions))
    print(part_1, part_2)
