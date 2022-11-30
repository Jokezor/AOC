import time


def read_file(file_name: str) -> list:
    return [line.strip('\n') for line in open(file_name, 'r')]


def num_occupied_seats(seat_grid: list) -> int:
    """
    Takes the seat_grid and counts for each row the number of occupied seats, then sum them together.
    """
    return sum([row.count('#') for row in seat_grid])


def update_state(seat_grid: list) -> list:
    """
    Takes the seat_grid list which is the current state of the seat grid, applies the rules and return the new state.
    """
    new_seat_grid = seat_grid[:]
    for i in range(0, len(seat_grid)):
        for j in range(0, len(seat_grid[i])):
            if seat_grid[i][j] != '.':

                # Top left corner: check below, right and diagonally
                if i == 0 and j == 0:
                    # Only check if there are no occupied seats, since there can not be four or more adjacent ones in this case
                    if not any([seat == '#' for seat in [seat_grid[i+1][j], seat_grid[i+1][j+1], seat_grid[i][j+1]]]):
                        row = list(new_seat_grid[i])
                        row[j] = '#'
                        new_seat_grid[i] = "".join(row)

                # Top row: check below, right, left and diagonally
                elif i == 0 and j in range(1, len(seat_grid[i]) - 1):
                    if seat_grid[i][j] == '#':
                        if sum([seat == '#' for seat in [seat_grid[i][j-1], seat_grid[i+1][j-1], seat_grid[i+1][j], seat_grid[i+1][j+1], seat_grid[i][j+1]]]) >= 4:
                            row = list(new_seat_grid[i])
                            row[j] = 'L'
                            new_seat_grid[i] = "".join(row)
                    elif seat_grid[i][j] == 'L':
                        if not any([seat == '#' for seat in [seat_grid[i][j - 1], seat_grid[i + 1][j - 1], seat_grid[i + 1][j], seat_grid[i + 1][j + 1], seat_grid[i][j + 1]]]):
                            row = list(new_seat_grid[i])
                            row[j] = '#'
                            new_seat_grid[i] = "".join(row)

                # Top right corner: check below, left and diagonally
                elif i == 0 and j == len(seat_grid[i]) - 1:
                    # Only check if there are no occupied seats, since there can not be four or more adjacent ones in this case
                    if not any([seat == '#' for seat in
                                [seat_grid[i][j - 1], seat_grid[i + 1][j - 1], seat_grid[i + 1][j]]]):
                        row = list(new_seat_grid[i])
                        row[j] = '#'
                        new_seat_grid[i] = "".join(row)

                # Right row: check above, below, left and diagonally
                elif i in range(1, len(seat_grid) - 1) and j == len(seat_grid[i]) - 1:
                    if seat_grid[i][j] == '#':
                        if sum([seat == '#' for seat in [seat_grid[i - 1][j], seat_grid[i - 1][j - 1], seat_grid[i][j - 1], seat_grid[i + 1][j - 1], seat_grid[i + 1][j]]]) >= 4:
                            row = list(new_seat_grid[i])
                            row[j] = 'L'
                            new_seat_grid[i] = "".join(row)
                    elif seat_grid[i][j] == 'L':
                        if not any([seat == '#' for seat in [seat_grid[i - 1][j], seat_grid[i - 1][j - 1], seat_grid[i][j - 1], seat_grid[i + 1][j - 1], seat_grid[i + 1][j]]]):
                            row = list(new_seat_grid[i])
                            row[j] = '#'
                            new_seat_grid[i] = "".join(row)

                # Bottom right corner: check above, left and diagonally
                elif i == len(seat_grid) - 1 and j == len(seat_grid[i]) - 1:
                    # Only check if there are no occupied seats, since there can not be four or more adjacent ones in this case
                    if not any([seat == '#' for seat in
                                [seat_grid[i][j - 1], seat_grid[i - 1][j - 1], seat_grid[i - 1][j]]]):
                        row = list(new_seat_grid[i])
                        row[j] = '#'
                        new_seat_grid[i] = "".join(row)

                # Bottom row: check above, right, left and diagonally
                elif i == len(seat_grid) - 1 and j in range(1, len(seat_grid[i]) - 1):
                    if seat_grid[i][j] == '#':
                        if sum([seat == '#' for seat in
                                [seat_grid[i][j - 1], seat_grid[i - 1][j - 1], seat_grid[i - 1][j],
                                 seat_grid[i - 1][j + 1], seat_grid[i][j + 1]]]) >= 4:
                            row = list(new_seat_grid[i])
                            row[j] = 'L'
                            new_seat_grid[i] = "".join(row)
                    elif seat_grid[i][j] == 'L':
                        if not any([seat == '#' for seat in
                                [seat_grid[i][j - 1], seat_grid[i - 1][j - 1], seat_grid[i - 1][j],
                                 seat_grid[i - 1][j + 1], seat_grid[i][j + 1]]]):
                            row = list(new_seat_grid[i])
                            row[j] = '#'
                            new_seat_grid[i] = "".join(row)

                # Left corner: check above, right and diagonally
                elif i == len(seat_grid) - 1 and j == 0:
                    if not any([seat == '#' for seat in
                                [seat_grid[i - 1][j], seat_grid[i - 1][j + 1], seat_grid[i][j + 1]]]):
                        row = list(new_seat_grid[i])
                        row[j] = '#'
                        new_seat_grid[i] = "".join(row)

                # Left row: check above, right, left and diagonally
                elif i in range(1, len(seat_grid) - 1) and j == 0:
                    if seat_grid[i][j] == '#':
                        if sum([seat == '#' for seat in [seat_grid[i - 1][j], seat_grid[i - 1][j + 1], seat_grid[i][j + 1], seat_grid[i + 1][j + 1], seat_grid[i + 1][j]]]) >= 4:
                            row = list(new_seat_grid[i])
                            row[j] = 'L'
                            new_seat_grid[i] = "".join(row)
                    elif seat_grid[i][j] == 'L':
                        if not any([seat == '#' for seat in [seat_grid[i - 1][j], seat_grid[i - 1][j + 1], seat_grid[i][j + 1], seat_grid[i + 1][j + 1], seat_grid[i + 1][j]]]):
                            row = list(new_seat_grid[i])
                            row[j] = '#'
                            new_seat_grid[i] = "".join(row)

                # Middle points: check above, below, right, left and diagonally
                else:
                    if seat_grid[i][j] == '#':
                        if sum([seat == '#' for seat in [seat_grid[i][j - 1], seat_grid[i - 1][j - 1], seat_grid[i - 1][j], seat_grid[i - 1][j + 1], seat_grid[i][j + 1], seat_grid[i + 1][j + 1], seat_grid[i + 1][j], seat_grid[i+1][j - 1]]]) >= 4:
                            row = list(new_seat_grid[i])
                            row[j] = 'L'
                            new_seat_grid[i] = "".join(row)
                    elif seat_grid[i][j] == 'L':
                        if not any([seat == '#' for seat in [seat_grid[i][j - 1], seat_grid[i - 1][j - 1], seat_grid[i - 1][j], seat_grid[i - 1][j + 1], seat_grid[i][j + 1], seat_grid[i + 1][j + 1], seat_grid[i + 1][j], seat_grid[i+1][j - 1]]]):
                            row = list(new_seat_grid[i])
                            row[j] = '#'
                            new_seat_grid[i] = "".join(row)

    return new_seat_grid


def update_until_no_change(seat_grid: list) -> int:

    while True:
        new_seat_grid = update_state(seat_grid)

        if seat_grid == new_seat_grid:
            return num_occupied_seats(seat_grid)
        else:
            seat_grid = new_seat_grid[:]


if __name__ == '__main__':
    start = time.time()
    file_name = 'input.txt'
    seat_grid = read_file(file_name)
    part_1 = update_until_no_change(seat_grid)
    end = time.time()
    print(end - start)
