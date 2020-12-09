def read_file(file_name: str) -> list:
    return [int(line.strip('\n')) for line in open(file_name, 'r')]


# Use a list of numbers
# The idea is to subtract the value
def find_outlier(numbers: list, preamble_length: int) -> int:

    one_hot_list = [numbers[index] if not any([numbers[index] - numbers[ind] in
                                               (numbers[index-preamble_length:ind] + numbers[ind+1:index])
                                               for ind in range(index - preamble_length, index)]) else False
                    for index in range(preamble_length, len(numbers))]

    for element in one_hot_list:
        if element:
            return element


def find_encryption(numbers: list, outlier: int) -> int:
    result = outlier
    for outer_index in range(0, len(numbers)):
        for inner_index in range(len(numbers), outer_index, -1):
            result -= sum(numbers[outer_index:inner_index])
            if result == 0:
                return sorted(numbers[outer_index:inner_index])[0] + sorted(numbers[outer_index:inner_index])[-1]
            if result < 0:
                result = outlier


if __name__ == '__main__':
    file_name = 'input.txt'
    numbers = read_file(file_name)
    preamble_length = 25
    # Part 1
    outlier = find_outlier(numbers=numbers, preamble_length=preamble_length)
    print(outlier)

    # Part 2
    encryption_key = find_encryption(numbers=numbers, outlier=outlier)
    print(encryption_key)
