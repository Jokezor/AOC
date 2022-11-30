import numpy as np

def read_bingo_input(file_path):
    with open(file_path, 'r') as f:
        bingo_numbers = f.readline().strip().split(',') 

        # List to hold all of the boards
        boards = []

        # Iteratively create a new board, copy the board and rewrite this one
        new_board = []

        for line in f:
            if line != '\n':
                # Didnt find an easy solution to handle multiple whitespaces
                new_row = line.strip().replace('  ', ',').replace(' ', ',').split(',')

                # Create dict with zero values
                new_board.append([{char: False} for char in new_row])
            else:
                # Copy over the board since we've now encountered the end of the board 
                if len(new_board): boards.append(new_board[:])        
                new_board = []

        # Append the new board at the file end
        if len(new_board): boards.append(new_board[:])        
    return bingo_numbers, np.array(boards)

def is_bingo(board):
    for index in range(len(board[0])):
        # Check columnwise
        if all(list(called.values())[0] for called in board[:, index]):
            return True
        # Check rowwise
        if all(list(called.values())[0] for called in board[index, :]):
            return True
    return False

def calculate_score(board):
    board_score = 0

    for row in board:
        for column in row:
            # Only count unmarked numbers
            if not list(column.values())[0]:
                board_score += int(list(column.keys())[0])

    return board_score

def play_bingo(bingo_file):
    bingo_numbers, boards = read_bingo_input(bingo_file)

    for number in bingo_numbers:

        for board in boards:
            for row in range(len(board)):
                for column in range(len(board[row])):
                    if number in board[row][column].keys(): 
                        board[row][column][number] = True 
        
                        if is_bingo(board):
                            board_score = calculate_score(board)
                            return board_score * int(number)

def play_bingo_part2(bingo_file):
    bingo_numbers, boards = read_bingo_input(bingo_file)

    # Add the index of the boards that win
    boards_won = []
    for number in bingo_numbers:
        for index in range(len(boards)):
            for row in range(len(boards[index])):
                for column in range(len(boards[index][row])):

                    if number in boards[index][row][column].keys(): 
                        boards[index][row][column][number] = True 
        
                        if is_bingo(boards[index]):
                            # Now all boards have won, take the last one which did
                            if len(boards_won) == len(boards):
                                board_score = calculate_score(boards[boards_won[-1]])
                                return board_score * int(number)
                            # Add the index of boards as they are bingoed
                            elif index not in boards_won:
                                boards_won.append(index)
                        
def test_bingo_input(input_file):
    """
    Test to make sure the data is read properly
    """
    bingo_numbers, boards = read_bingo_input('example_input')
    assert len(boards) == 3
    assert len(bingo_numbers) == 27

####################################################################
# Testing input
test_bingo_input('example_input')

####################################################################
# Part 1
assert play_bingo('example_input') == 4512
assert play_bingo('input') == 41668


####################################################################
# Part 2
assert play_bingo_part2('example_input') == 1924
assert play_bingo_part2('input') == 10478
