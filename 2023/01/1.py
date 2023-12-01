with open("input.txt", "r") as f:
    instructions = f.read().splitlines()

nums = []

for instruction in instructions:
    first_num = ""
    second_num = ""
    for c in instruction:
        if 0 <= ord(c) - ord("0") <= 9:
            if first_num:
                second_num = c
            else:
                first_num = c

    calibration_value = first_num + (second_num or first_num)
    nums.append(int(calibration_value))


print(nums)
print(sum(nums))
