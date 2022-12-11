# Does not work.

with open("input.txt", "r") as f:
    s = [line.strip() for line in f.readlines()]

myList = [1] * 4000

ind = 1

# Part 1
for line in s:
    instruction = line.split(" ")

    C = instruction[0]

    if C == "noop":
        myList[ind + 1] = myList[ind]
        ind += 1
    elif C == "addx":
        V = int(instruction[1])
        myList[ind + 1] = myList[ind]
        myList[ind + 2] = myList[ind] + V
        ind += 2

cycles = [20, 60, 100, 140, 180, 220]
result = sum([myList[cycle] * cycle for cycle in cycles])

# Part 2
CRT = ["." * 40 for _ in range(6)]

# Go through all CRT positions from 1 to 240.
# Check if the value of the position is within [pos - 1, pos, pos + 1]
# If so, then write a #
for row_number, row in enumerate(CRT):
    for col_number, col in enumerate(row):
        mid = (row_number) * 40 + (col_number + 1)
        col_range = [myList[mid] - 1, myList[mid], myList[mid] + 1]

        # Check if the sprite is in the pixel position
        if any(col_number in col_range):
            CRT[row_number] = (
                CRT[row_number][:col_number] + "#" + CRT[row_number][col_number + 1 :]
            )

for line in CRT:
    print(line)

expected = [
    "##..##..##..##..##..##..##..##..##..##..",
    "###...###...###...###...###...###...###.",
    "####....####....####....####....####....",
    "#####.....#####.....#####.....#####.....",
    "######......######......######......####",
    "#######.......#######.......#######.....",
]

assert CRT == expected
with open("input.txt", "r") as f:
    s = [line.strip() for line in f.readlines()]

myList = [1] * 4000

ind = 1

# Part 1
for line in s:
    instruction = line.split(" ")

    C = instruction[0]

    if C == "noop":
        myList[ind + 1] = myList[ind]
        ind += 1
    elif C == "addx":
        V = int(instruction[1])
        myList[ind + 1] = myList[ind]
        myList[ind + 2] = myList[ind] + V
        ind += 2

cycles = [20, 60, 100, 140, 180, 220]
result = sum([myList[cycle] * cycle for cycle in cycles])

# Part 2
CRT = ["." * 40 for _ in range(6)]

# Go through all CRT positions from 1 to 240.
# Check if the value of the position is within [pos - 1, pos, pos + 1]
# If so, then write a #
for row_number, row in enumerate(CRT):
    for col_number, col in enumerate(row):
        mid = (row_number) * 40 + (col_number + 1)
        col_range = [myList[mid] - 1, myList[mid], myList[mid] + 1]

        # Check if the sprite is in the pixel position
        if any(col_number in col_range):
            CRT[row_number] = (
                CRT[row_number][:col_number] + "#" + CRT[row_number][col_number + 1 :]
            )

for line in CRT:
    print(line)

expected = [
    "##..##..##..##..##..##..##..##..##..##..",
    "###...###...###...###...###...###...###.",
    "####....####....####....####....####....",
    "#####.....#####.....#####.....#####.....",
    "######......######......######......####",
    "#######.......#######.......#######.....",
]

assert CRT == expected
