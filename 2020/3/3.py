f = open('input.txt', 'r')
lines = [line.strip('\n') for line in f]

# Part 1
ind = 0
num_trees = 0
for line in lines:
    if line[ind % (len(line))] == '#':
        num_trees += 1
    # Debugging line
    # print(ind % (len(line)), num_trees, "".join('O' if ind_0 == (ind % (len(line))) else char for ind_0, char in enumerate(line)))
    ind += 3

print(num_trees)

# Part 2
slopes = {'slope1': {'right': 1, 'down': 1, 'num_trees': 0}, 'slope2': {'right': 3, 'down': 1, 'num_trees': 0},
          'slope3': {'right': 5, 'down': 1, 'num_trees': 0}, 'slope4': {'right': 7, 'down': 1, 'num_trees': 0},
          'slope5': {'right': 1, 'down': 2, 'num_trees': 0}}

prod = 1
for slope in slopes:
    line_ind = 0
    ind = 0
    while line_ind < len(lines):
        if lines[line_ind][ind % len(lines[line_ind])] == "#":
            slopes[slope]['num_trees'] += 1
        # Debugging line
        #print(ind % len(lines[line_ind]), slopes[slope]['num_trees'],
        #      "".join('O' if ind_0 == (ind % len(lines[line_ind])) else char for ind_0, char in enumerate(lines[line_ind])))
        line_ind += slopes[slope]['down']
        ind += slopes[slope]['right']

    prod *= slopes[slope]['num_trees']

print(prod)

