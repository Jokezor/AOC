# Keep an array of the operations
# Go through the array instructions sequentially. Store the index in a dict. If there already is that ind in the dict,
# then print out the accumulator
# while(key not in set)
# Need to find combination of

def read_file(file_name: str) -> list:
    return [{line.strip('\n').split(' ')[0]: line.strip('\n').split(' ')[1]} for line in open(file_name, 'r')]


def sequential_singularity_finder_part_1(instruction_list: list) -> int:

    visited_indices = set()
    index = 0
    value = 0

    while index < len(instruction_list):
        if index in visited_indices:
            return value
        else:
            visited_indices.add(index)
        instruction = instruction_list[index]
        visited_indices.add(index)

        if 'acc' in instruction:
            value = eval(str(value) + instruction['acc'])
            index += 1
        elif 'nop' in instruction:
            index += 1
        elif 'jmp' in instruction:
            index = eval(str(index) + instruction['jmp'])


def sequential_singularity_finder_part_2(instruction_list: list) -> int:

    visited_indices = set()
    index = 0
    value = 0
    infinite_loop_found = 0

    while index < len(instruction_list):
        if index in visited_indices:
            infinite_loop_found = 1
        else:
            visited_indices.add(index)
        instruction = instruction_list[index]
        visited_indices.add(index)

        if 'acc' in instruction:
            value = eval(str(value) + instruction['acc'])
            index += 1
        elif 'nop' in instruction:
            index += 1
        elif 'jmp' in instruction:
            index = eval(str(index) + instruction['jmp'])


if __name__ == '__main__':
    file_name = 'input.txt'
    instruction_list = read_file(file_name)
    value_before_singularity_1 = sequential_singularity_finder_part_1(instruction_list=instruction_list)
    value_before_singularity_2 = sequential_singularity_finder_part_2(instruction_list=instruction_list)
    print(value_before_singularity_1, value_before_singularity_2)