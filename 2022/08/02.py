f = open("example_input.txt", "r")
patch = [[int(tree) for tree in line.strip()] for line in f.readlines()]

N = len(patch)
M = len(patch[0])

visisble_trees = 2 * N + 2 * M - 4


def any_taller(height, trees):
    seen_trees = 0

    for tree in trees:
        if tree >= height:
            break
        seen_trees += 1

    return max(1, seen_trees)


max_scenic_score = 0
best_place = (0, 0)

for i in range(1, N - 1):
    for j in range(1, M - 1):
        current_row = patch[i]
        current_col = [row[j] for row in patch]
        trees_seen = 0

        tree = current_row[j]

        # Check left
        left_seen = any_taller(tree, current_row[0:j:][::-1])

        # Check right
        right_seen = any_taller(tree, current_row[j + 1 :][::-1])

        # Check up
        up_seen = any_taller(tree, current_col[0:i][::-1])

        # Check down
        down_seen = any_taller(tree, current_col[i + 1 :][::-1])

        scenic_score = left_seen * right_seen * up_seen * down_seen

        if i == 3 and j == 2:
            print(tree, scenic_score)
            print(left_seen, right_seen, up_seen, down_seen)

        if scenic_score > max_scenic_score:
            max_scenic_score = scenic_score
            best_place = (i, j)

print(max_scenic_score, best_place)
