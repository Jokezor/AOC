import math


def read_file(file_name: str) -> list:
    return [line.strip('\n') for line in open(file_name, 'r')]


def binary_search(boarding_pass: str) -> int:
    row = [0, 127]
    col = [0, 7]
    for ind, char in enumerate(boarding_pass):
        if char == 'F':
            if boarding_pass[ind+1] in ['F', 'B']:
                row = [row[0], math.floor((row[0] + row[1])/2)]
            else:
                row = math.floor((row[0] + row[1]) / 2)
        elif char == 'B':
            if boarding_pass[ind + 1] in ['F', 'B']:
                row = [math.ceil((row[0] + row[1])/2), row[1]]
            else:
                row = math.ceil((row[0] + row[1]) / 2)
        elif char == 'L':
            if ind < len(boarding_pass) - 1:
                col = [col[0], math.floor((col[0] + col[1])/2)]
            else:
                col = math.floor((col[0] + col[1]) / 2)
        elif char == 'R':
            if ind < len(boarding_pass) - 1:
                col = [math.ceil((col[0] + col[1]) / 2), col[1]]
            else:
                col = math.ceil((col[0] + col[1]) / 2)
    # print(row * 8 + col)
    return row * 8 + col


def search_boarding_passes(boarding_passes: list) -> int:
    highest_id = 0
    for boarding_pass in boarding_passes:
        boarding_pass_id = binary_search(boarding_pass)
        if boarding_pass_id > highest_id:
            highest_id = boarding_pass_id
    return highest_id


def get_boarding_pass_id(boarding_passes: list) -> int:
    ids = []
    for boarding_pass in boarding_passes:
        boarding_pass_id = binary_search(boarding_pass)
        ids.append(boarding_pass_id)

    valid_ids = sorted(ids)[7:len(ids)-7]
    correct_id = -1
    for ind, id in enumerate(valid_ids):
        if (valid_ids[ind] + 2) in valid_ids and (valid_ids[ind] + 1) not in valid_ids:
            correct_id = valid_ids[ind] + 1
    return correct_id


if __name__ == '__main__':
    puzzle_input = 'input.txt'
    boarding_passes = read_file(puzzle_input)

    # Part 1
    print(search_boarding_passes(boarding_passes))

    # Part 2
    print(get_boarding_pass_id(boarding_passes))
