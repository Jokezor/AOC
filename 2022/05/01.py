class Solution:
    def __init__(self, num_stacks):
        f = open("input.txt", "r")

        self.s = f.readlines()
        self.num_stacks = num_stacks

        self.stacks = [[] for _ in range(num_stacks)]
        self.input = []

        initial = self.s[:8]
        print(initial)

        for i in range(len(initial)):
            initial_state = initial[i].split(" ")
            row = [""] * num_stacks

            ind = 0
            blank_count = 0
            for c in initial_state:
                if not c.strip():
                    blank_count += 1
                else:
                    blank_count = 0
                    row[ind] = c.strip().split("[")[1].split("]")[0]
                    ind += 1

                if blank_count == 4:
                    row[ind] = ""
                    ind += 1
                    blank_count = 0
            self.input.append(row)

        for i in range(num_stacks):
            self.stacks[i] += [row[i] for row in self.input if row[i].strip()][::-1]

        self.commands = [
            [
                [
                    int(move[0:2]),
                    int(move.split("from ")[1].split(" to ")[0]),
                    int(move.split("from ")[1].split(" to ")[1].strip()),
                ]
                for move in command.split("move ")
                if move.strip()
            ]
            for command in self.s[10:]
            if command.strip()
        ]

    def part_1(self):
        for command_list in self.commands:
            command = command_list[0]

            self.stacks[command[2] - 1] += [
                self.stacks[command[1] - 1].pop()
                for _ in range(command[0])
                if self.stacks[command[1] - 1]
            ][::-1]
            """
            for _ in range(command[0]):
                if self.stacks[command[1] - 1]:
                    self.stacks[command[2] - 1].append(
                        self.stacks[command[1] - 1].pop()
                    )
                    print(self.stacks)
            """
        result = "".join(
            self.stacks[i][-1] for i in range(len(self.stacks)) if self.stacks[i]
        )
        print(self.commands[0])
        print(result)


if __name__ == "__main__":
    Solution(9).part_1()
