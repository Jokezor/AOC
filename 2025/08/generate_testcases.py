import random


"""
Should output something like:
5
1 3
1
2
1 8
4
12
3 5
6 2 9
8 4 11
2 7
2 8
2 9
3 2
0 1 0
1 0 1
"""
def generate_test_cases(t):
    file_name = "tests.txt"

    n_high = 3
    k_high = 10

    with open(file_name, "w+") as f:
        f.write(f"{t}\n")

        for _ in range(t):
            n = random.randint(1, n_high)
            k = random.randint(1, k_high)

            f.write(f"{n} {k}\n")

            # Now to add a.
            for i in range(n):
                f.write(f"{random.randint(0, k_high)} ")
            f.write("\n")

            # add b
            for i in range(n):
                f.write(f"{random.randint(0, k_high)} ")
            f.write("\n")

        

if __name__ == '__main__':
    generate_test_cases(2)
