import functools
# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


def read_file():
    # Use a breakpoint in the code line below to debug your script.
    f = open('input.txt', 'r')
    return f


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    file = read_file()
    num_correct_passwords = 0
    for row in file:
        min = row.split(' ')[0].split('-')[0]
        max = row.split(' ')[0].split('-')[1]
        letter = row.split(' ')[1].split(':')[0]
        password = row.split(' ')[2].split('\n')[0]
        count = 0

        """ Part 1
        """
        for char in password:
            if char == letter:
                count += 1

        if (count >= int(min)) and count <= int(max):
            num_correct_passwords += 1

        """
        Part 2
        """
        for ind, char in enumerate(password):
            # print(ind, char, letter)
            if ind+1 == int(min) and char == letter:
                print(ind)
                count = 1
            if ind+1 == int(max) and char == letter:
                if count == 0:
                    # print(ind)
                    count = 1
                else:
                    count = 0

        #if count == 1:
        #    num_correct_passwords += 1
    print(num_correct_passwords)
