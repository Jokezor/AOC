# 1. read the file
with open("input.txt", "r") as f:
    instructions = [line.strip().split() for line in f.readlines()]


# Skip first instruction
instructions = instructions[1:]


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


dirs = []


# 3. Get the sizes for all directories
def dfs(node):
    # We want to add in all children.
    for key, child in node.children.items():
        node.size += dfs(child)
    if node.children:
        dirs.append(node.size)
    return node.size


dfs(root)
print(root)

total_size = sum(dirs)
print(total_size)

# part 2.
# Check (700 000 - total size)
# And take the minimum value greater than it.
free_space = 70000000 - root.size
space_to_free = 30000000 - free_space
print(space_to_free)


min_dir = root.size

for size in dirs:
    if size >= space_to_free:
        min_dir = min(min_dir, size)

print(min_dir)
