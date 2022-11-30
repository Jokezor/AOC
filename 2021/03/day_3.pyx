reports = [line.strip() for line in open('input', 'r')]
example = [line.strip() for line in open('example_input', 'r')]


def calc_life_support(reports):
    return calc_oxygen(reports) * calc_co2(reports)

def calc_co2(reports):
    report_copy = reports[:]
    bits = len(report_copy[0])

    while len(report_copy) > 1:
        for i in range(0, bits):
            ones = []
            zeroes = []

            for ind, report in enumerate(report_copy):
                if report[i] == '1':
                    ones.append(ind)
                elif report[i] == '0':
                    zeroes.append(ind)

            if len(ones) < len(zeroes):
                num_deleted = 0
                for index in zeroes:
                    report_copy.pop(index - num_deleted)
                    num_deleted += 1
                    if len(report_copy) == 1: return int(report_copy[0], 2)
            else:
                num_deleted = 0
                for index in ones:
                    report_copy.pop(index - num_deleted)
                    num_deleted += 1
                    if len(report_copy) == 1: return int(report_copy[0], 2)

def calc_oxygen(reports):
    report_copy = reports[:]
    bits = len(report_copy[0])

    while len(report_copy) > 1:
        for i in range(0, bits):
            ones = []
            zeroes = []

            for ind, report in enumerate(report_copy):
                if report[i] == '1':
                    ones.append(ind)
                elif report[i] == '0':
                    zeroes.append(ind)

            if len(ones) >= len(zeroes):
                num_deleted = 0
                for index in zeroes:
                    report_copy.pop(index - num_deleted)
                    num_deleted += 1
                    if len(report_copy) == 1: return int(report_copy[0], 2)
            else:
                num_deleted = 0
                for index in ones:
                    report_copy.pop(index - num_deleted)
                    num_deleted += 1
                    if len(report_copy) == 1: return int(report_copy[0], 2)

def calc_power(reports):
    gamma_rate = ""
    epsilon_rate = ""

    for i in range(0, len(reports[0])):
        ones = 0
        zeroes = 0

        for report in reports:
            if report[i] == '1':
                ones += 1
            elif report[i] == '0':
                zeroes += 1

        if ones > zeroes:
            gamma_rate += '1'
            epsilon_rate += '0'
        else:
            gamma_rate += '0'
            epsilon_rate += '1'

    gamma_rate = int(gamma_rate, 2)
    epsilon_rate = int(epsilon_rate, 2)

    return gamma_rate * epsilon_rate

#################################################################
# Part 1 Testing

assert calc_power(example) == 198
assert calc_power(reports) == 4139586


#################################################################
# Part 2 Testing

assert calc_life_support(example) == 230
assert calc_life_support(reports) == 1800151
