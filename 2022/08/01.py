class Solution:
    def __init__(self):
        f = open("example_input.txt", "r")
        self.s = [line.strip() for line in f.readlines()]

    def part_1(self):
        print(self.s)


if __name__ == "__main__":
    Solution().part_1()
