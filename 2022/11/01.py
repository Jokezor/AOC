class Monkey:
    def __init__(self, raw_monkey_data):
        self.raw_monkey_data = raw_monkey_data
        self.items = self.parse_items()
        self.operation = self.parse_operation()
        self.test = self.parse_test()
        self.rules = self.parse_rules()

    def __str__(self):
        return f"{self.items} with {self.operation}"

    def __repr__(self):
        return f"{self.items} with {self.operation}"

    def parse_items(self):
        return list(
            map(
                lambda i: int(i.strip()),
                self.raw_monkey_data.split("\n")[1]
                .strip()
                .split("Starting items: ")[1]
                .strip()
                .split(","),
            )
        )

    def parse_operation(self):
        return self.raw_monkey_data.split("\n")[2].strip().split("Operation: ")[1]

    def parse_test(self):
        pass

    def parse_rules(self):
        pass


class Solution:
    def __init__(self):
        f = open("example_input.txt", "r")
        raw_monkeys_data = f.read().split("\n\n")

        self.monkeys = [Monkey(raw_monkey_data) for raw_monkey_data in raw_monkeys_data]

        # Parse the input,
        # put into multiple arrays
        # Or into multiple classes.

    def part_1(self):
        print(self.monkeys)


if __name__ == "__main__":
    Solution().part_1()
