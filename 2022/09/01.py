class Solution:
    def part_2(self):
        # Add (x, y) tuples visited by the tail to the set visited.
        visited = set()

        def needs_to_move(h, t):
            if abs(h[0] - t[0]) >= 2 or abs(h[1] - t[1]) >= 2:
                return True
            return False

        f = open("larger_example.txt", "r")
        s = list(
            map(lambda s: s.split(" "), list(map(lambda s: s.strip(), f.readlines())))
        )

        head = [0, 0]
        tails = [[0, 0] for _ in range(9)]

        visited.add((0, 0))

        for move, move_length in s:
            move_length = int(move_length)

            while move_length > 0:
                match move:
                    case "R":
                        head[0] += 1

                        for ind, tail in enumerate(tails):
                            if ind == 0:
                                tail_head = head
                            else:
                                tail_head = tails[ind - 1]

                            if needs_to_move(tail_head, tails[ind]):
                                if tail_head[1] > tails[ind][1]:
                                    tails[ind][1] += 1
                                elif tail_head[1] < tails[ind][1]:
                                    tails[ind][1] -= 1

                                tails[ind][0] += 1

                                if ind == len(tails) - 1:
                                    visited.add((tails[ind][0], tails[ind][1]))

                    case "L":
                        head[0] -= 1

                        for ind, tail in enumerate(tails):
                            if ind == 0:
                                tail_head = head
                            else:
                                tail_head = tails[ind - 1]

                            if needs_to_move(tail_head, tails[ind]):
                                if tail_head[1] > tails[ind][1]:
                                    tails[ind][1] += 1
                                elif tail_head[1] < tails[ind][1]:
                                    tails[ind][1] -= 1

                                tails[ind][0] -= 1

                                if ind == len(tails) - 1:
                                    visited.add((tails[ind][0], tails[ind][1]))

                        # Check sidestep for tail
                    case "U":
                        head[1] += 1

                        for ind, tail in enumerate(tails):
                            if ind == 0:
                                tail_head = head
                            else:
                                tail_head = tails[ind - 1]

                            if needs_to_move(tail_head, tails[ind]):
                                if tail_head[0] > tails[ind][0]:
                                    tails[ind][0] += 1
                                elif tail_head[0] < tails[ind][0]:
                                    tails[ind][0] -= 1

                                tails[ind][1] += 1

                                if ind == len(tails) - 1:
                                    visited.add((tails[ind][0], tails[ind][1]))

                        # Check sidestep for tail
                    case "D":
                        head[1] -= 1

                        for ind, tail in enumerate(tails):
                            if ind == 0:
                                tail_head = head
                            else:
                                tail_head = tails[ind - 1]

                            if needs_to_move(tail_head, tails[ind]):
                                if tail_head[0] > tails[ind][0]:
                                    tails[ind][0] += 1
                                elif tail_head[0] < tails[ind][0]:
                                    tails[ind][0] -= 1

                                tails[ind][1] -= 1

                                if ind == len(tails) - 1:
                                    visited.add((tails[ind][0], tails[ind][1]))
                move_length -= 1
                print(head, tails)

        print(len(visited))


if __name__ == "__main__":
    Solution().part_2()
