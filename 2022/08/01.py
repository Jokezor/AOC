# Number of trees visible on the perimiter is
# N * 2 + M * 2 - 4


# In my map, how many trees are visible from outside the grid?
# So we could use a lookup on the row, col for the different heights
# That would allow us to query it faster instead of having for each
# tree, search the whole row and col each time.
# We only need to know, is there any tree from our position that
# is higher or equal to us?
# So we could use some sort of sorted mechanism by index.

# For this example, lets first make sure we can count the number of visible trees
# To the same count as the example.


f = open("input.txt", "r")
patch = [[int(tree) for tree in line.strip()] for line in f.readlines()]

N = len(patch)
M = len(patch[0])

visisble_trees = 2 * N + 2 * M - 4

# Map:
# ()


def any_taller(height, trees):
    return any(list(map(lambda tree: tree >= height, trees)))


for i in range(1, N - 1):
    for j in range(1, M - 1):
        current_row = patch[i]
        current_col = [row[j] for row in patch]

        tree = current_row[j]

        # Check left
        if not any_taller(tree, current_row[0:j]):
            visisble_trees += 1
            continue

        # Check right
        if not any_taller(tree, current_row[j + 1 :]):
            visisble_trees += 1
            continue

        # Check up
        if not any_taller(tree, current_col[0:i]):
            visisble_trees += 1
            continue

        # Check down
        if not any_taller(tree, current_col[i + 1 :]):
            visisble_trees += 1
            continue

print(visisble_trees)
