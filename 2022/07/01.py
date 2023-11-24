from collections import deque

# Find total size of directories.
# Feels like DFS
# We need to:
# 1. read the file
# 2. Parse the file, when we see cd, we need to check if we have
#    the path in the graph, otherwise add it.
# 2. Mark the root as when we get into '/'
# 3. For each ls we should for dir <char>
#    add <char> as a child of the current_root
#    if file, then we add it as a leaf_node with the size.


# Requirements on the graph:
# To support .., we need a link to the parent.
# on cd, we go into that child from the graph.


# 1. read the file
with open("input.txt", "r") as f:
    instructions = [line.strip().split() for line in f.readlines()]


# Skip first instruction
instructions = instructions[1:]
print(instructions)


class GraphNode(object):
    def __repr__(self):
        return f"{self.key}: {self.children}, size: {self.size}"

    def __init__(self, key, size=0, parent=None):
        self.key = key
        self.size = size
        self.children = {}
        self.parent = parent


# 2. parse the instructions
root = GraphNode(key="/")
current_node = root

for instruction in instructions:
    state = instruction[0]

    if state == "$":
        command = instruction[1]
        if command == "ls":
            continue
        elif command == "cd":
            path = instruction[2]

            # Visit parent
            if path == "..":
                current_node = current_node.parent
            elif path == "/":
                current_node = root
            else:
                current_node = current_node.children[path]
    elif state == "dir":
        key = instruction[1]

        if key not in current_node.children:
            new_node = GraphNode(key=key, parent=current_node)
            current_node.children[key] = new_node
    else:
        key = instruction[1]
        size = int(state)
        if key not in current_node.children:
            new_node = GraphNode(key=key, parent=current_node, size=size)
            current_node.children[key] = new_node


print(root)


dirs_to_delete = []


# 3. Get the sizes for all directories
def dfs(node):
    # We want to add in all children.
    for key, child in node.children.items():
        node.size += dfs(child)
    if node.size <= 100000 and node.children:
        dirs_to_delete.append(node.size)
    return node.size


dfs(root)
print(root)

# 4. Calculate the total size of those with at most 100 000
total_size = sum(dirs_to_delete)
print(total_size)
