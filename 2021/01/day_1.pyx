# Input the files, clean up new lines and convert to int
input_depths = [int(line.strip()) for line in open('input', 'r')]

def count_depth_increase(list depths) -> int:
    # Loop through and sum up the booleans which are true (greater than the previous depth)
    return sum(depths[ind+1] > depths[ind] for ind in range(len(depths)-1))

def count_sliding_window_depth_increase(list depths) -> List:
    # Add the index, index+1 and index+2 to the sum
    return count_depth_increase([depths[ind] + depths[ind+1] + depths[ind+2] for ind in range(len(depths) - 2)])

################################################
# Testing

# General testing

# Assert that all lines are loaded
assert len(input_depths) == 2000

################################################
# Part 1
# My test
assert count_depth_increase([1,2,3,0]) == 2

# Testing subrange
assert count_depth_increase([109,117,118,98,102]) == 3

# Puzzle input
assert count_depth_increase(input_depths) == 1448

################################################
# Part 2

# Example input
assert count_sliding_window_depth_increase([607,618,618,617,647,716,769,792]) == 5

# Puzzle input
assert count_sliding_window_depth_increase(input_depths) == 1471

