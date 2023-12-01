with open("input.txt", "r") as f:
    instructions = f.read().splitlines()

nums = []


def is_digit(c):
    return 0 <= ord(c) - ord("0") <= 9


num_map = {
    "one": "1",
    "two": "2",
    "three": "3",
    "four": "4",
    "five": "5",
    "six": "6",
    "seven": "7",
    "eight": "8",
    "nine": "9",
}


for instruction in instructions:
    first_num = ""
    second_num = ""

    num_pos = 0

    # Here we can keep running substring.
    # Just look in the substring, keep index of known nums.
    for i in range(len(instruction)):
        c = instruction[i]

        # First check substring
        for key, value in num_map.items():
            if key in instruction[slice(num_pos, i + 1)]:
                if first_num:
                    second_num = value
                else:
                    first_num = value
                num_pos = i

        if is_digit(c):
            if first_num:
                second_num = c
            else:
                first_num = c
            num_pos = i

    calibration_value = first_num + (second_num or first_num)
    nums.append(int(calibration_value))


print(nums)
print(sum(nums))
