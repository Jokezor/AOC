def read_vent_report_part_2(vent_file):
    # Return the frequency dict
    frequency_dict = {}

    with open(vent_file, 'r') as f:
        for line in f:
            # Convert it to x and y values
            point_1, point_2 = line.strip().split(' -> ')
            point_1 = [int(char) for char in point_1.split(',')]
            point_2 = [int(char) for char in point_2.split(',')]
            
            # Check if horizontal
            if point_1[0] == point_2[0]:
                # Check which is the greater point to iterate towards 
                if point_1[1] <= point_2[1]:
                    # Should be inclusive
                    range_covered = range(point_1[1], point_2[1] + 1)
                else:
                    range_covered = range(point_1[1], point_2[1] - 1, -1)

                for ind in range_covered:
                    # Use the convention of x_ind, y_ind for the index name
                    index_covered = f'{point_1[0]}, {ind}'
                    
                    # Increment if the index has been visited by other lines
                    if index_covered in frequency_dict:
                        frequency_dict[index_covered] += 1
                    else:
                        frequency_dict[index_covered] = 1
    
            # Check if vertical
            elif point_1[1] == point_2[1]:
                # Check which is the greater point to iterate towards 

                if point_1[0] <= point_2[0]:
                    # Should be inclusive
                    range_covered = range(point_1[0], point_2[0] + 1)
                else:
                    range_covered = range(point_1[0], point_2[0] - 1, -1)

                for ind in range_covered:
                    # Use the convention of x_ind, y_ind for the index name
                    index_covered = f'{ind}, {point_1[1]}'
                    
                    # Increment if the index has been visited by other lines
                    if index_covered in frequency_dict:
                        frequency_dict[index_covered] += 1
                    else:
                        frequency_dict[index_covered] = 1
    
            # Diagonal
            else:
                while True:
                    # Use the convention of x_ind, y_ind for the index name
                    index_covered = f'{point_1[0]}, {point_1[1]}'
                    
                    # Increment if the index has been visited by other lines
                    if index_covered in frequency_dict:
                        frequency_dict[index_covered] += 1
                    else:
                        frequency_dict[index_covered] = 1

                    if point_1 == point_2: break

                    if point_1[0] < point_2[0]:
                        point_1[0] += 1
                    elif point_1[0] > point_2[0]:
                        point_1[0] -= 1
                    
                    if point_1[1] < point_2[1]:
                        point_1[1] +=1
                    elif point_1[1] > point_2[1]:
                        point_1[1] -= 1

    return frequency_dict


def read_vent_report_part_1(vent_file):
    # Return the frequency dict
    frequency_dict = {}

    with open(vent_file, 'r') as f:
        # What if I were to take the range from x1 to x2 and y1 to y2
        # For example: 6,4 -> 2,0
        # It covers a diagonal line.'
        # How to represent this using integers?
        # We should ignore diagonal lines for now.

        for line in f:
            # Use a frequency dict with the indices of the line ranges as keys
            # That way we can easily just fetch all with a value of 2 or 
            # greater.

            # When comparing, just check all with value above or equal to 2.

            # Convert it to x and y values
            point_1, point_2 = line.strip().split(' -> ')
            point_1 = [int(char) for char in point_1.split(',')]
            point_2 = [int(char) for char in point_2.split(',')]
            
            # Check if horizontal
            if point_1[0] == point_2[0]:
                # Check which is the greater point to iterate towards 
                if point_1[1] <= point_2[1]:
                    # Should be inclusive
                    range_covered = range(point_1[1], point_2[1] + 1)
                else:
                    range_covered = range(point_1[1], point_2[1] - 1, -1)

                for ind in range_covered:
                    # Use the convention of x_ind, y_ind for the index name
                    index_covered = f'{point_1[0]}, {ind}'
                    
                    # Increment if the index has been visited by other lines
                    if index_covered in frequency_dict:
                        frequency_dict[index_covered] += 1
                    else:
                        frequency_dict[index_covered] = 1
    
            # Check if vertical
            elif point_1[1] == point_2[1]:
                # Check which is the greater point to iterate towards 

                if point_1[0] <= point_2[0]:
                    # Should be inclusive
                    range_covered = range(point_1[0], point_2[0] + 1)
                else:
                    range_covered = range(point_1[0], point_2[0] - 1, -1)

                for ind in range_covered:
                    # Use the convention of x_ind, y_ind for the index name
                    index_covered = f'{ind}, {point_1[1]}'
                    
                    # Increment if the index has been visited by other lines
                    if index_covered in frequency_dict:
                        frequency_dict[index_covered] += 1
                    else:
                        frequency_dict[index_covered] = 1
    
    return frequency_dict

def points_of_overlapping_part_1(vent_file):
    frequency_report = read_vent_report_part_1(vent_file)
    print(sum(covered >= 2 for covered in list(frequency_report.values())))
    return sum(covered >= 2 for covered in list(frequency_report.values()))

def points_of_overlapping_part_2(vent_file):
    frequency_report = read_vent_report_part_2(vent_file)
    print(sum(covered >= 2 for covered in list(frequency_report.values())))
    return sum(covered >= 2 for covered in list(frequency_report.values()))


###############################################################
# Test part 1
assert points_of_overlapping_part_1('example_input') == 5
assert points_of_overlapping_part_1('input') == 7142


###############################################################
# Test part 2
assert points_of_overlapping_part_2('example_input') == 12
assert points_of_overlapping_part_2('input') == 20012
