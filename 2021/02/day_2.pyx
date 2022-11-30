instructions = [line.split() for line in open('input', 'r')]

def final_position(instructions):
    depth, horizontal = 0, 0
    
    for instruction in instructions:
        if instruction[0] == 'forward':
            horizontal += int(instruction[1])
        if instruction[0] == 'up':
            depth -= int(instruction[1])
        if instruction[0] == 'down':
            depth += int(instruction[1])

    return depth*horizontal

def final_position_with_aim(instructions):
    aim, depth, horizontal = 0, 0, 0

    for instruction in instructions:
        if instruction[0] == 'forward':
            horizontal += int(instruction[1])
            depth += aim*int(instruction[1])
        if instruction[0] == 'up':
            aim -= int(instruction[1])
        if instruction[0] == 'down':
            aim += int(instruction[1])
    return depth*horizontal


###############################################
# Testing Part 1

# Example input
assert final_position([['forward', '5'],['down', '5'],['forward', '8'],['up', '3'],['down', '8'],['forward', '2']]) == 150

# Puzzle input
assert final_position(instructions) == 2070300


###############################################
# Testing Part 2
assert final_position_with_aim([['forward', '5'],['down', '5'],['forward', '8'],['up', '3'],['down', '8'],['forward', '2']]) == 900

assert final_position_with_aim(instructions) == 2078985210


