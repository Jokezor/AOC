def read_vent_report(vent_file):
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
            
            # might be able to make one which works for both digagonala nd horizontal and vertical. that would be great.
            # First try to get one for diagonally, decrement or increment both x and y,
            if point_1[0] <= point_2[0]:
                # Should be inclusive
                xrange = range(point_1[0], point_2[0] + 1)
            else:
                xrange = range(point_1[0], point_2[0] - 1, -1)
            
            if point_1[1] <= point_2[1]:
                # Should be inclusive
                yrange = range(point_1[1], point_2[1] + 1)
            else:
                yrange = range(point_1[1], point_2[1] - 1, -1)
            
            for x_ind in xrange:
                for y_ind in yrange:
                    # Use the convention of x_ind, y_ind for the index name
                    index_covered = f'{x_ind}, {y_ind}'
                    
                    # Increment if the index has been visited by other lines
                    if index_covered in frequency_dict:
                        frequency_dict[index_covered] += 1
                    else:
                        frequency_dict[index_covered] = 1
    
    return frequency_dict

def points_of_overlapping(vent_file):
    frequency_report = read_vent_report(vent_file)
    print(sum(covered >= 2 for covered in list(frequency_report.values())))
    return sum(covered >= 2 for covered in list(frequency_report.values()))


assert points_of_overlapping('example_input') == 12
assert points_of_overlapping('input') == 7142
