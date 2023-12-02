import re

# Solve the problm
with open("input.txt", "r") as f:
    instructions = [line.strip() for line in f.readlines()]

# instructions = [line.strip() for line in input().split("\n")]

# Get game id.
# Keep count of max in each subset.
# Take max of max for each subset.

possible_games = []
games = {}

max_red = 12
max_green = 13
max_blue = 14

red_pattern = re.compile(r"\d+\sred")
blue_pattern = re.compile(r"\d+\sblue")
green_pattern = re.compile(r"\d+\sgreen")
separator_pattern = re.compile(r";")


for game in instructions:
    prev_ind = 0
    game_id = -1

    subsets = []

    i = 0

    game_id_end = game.find(":")
    game_id = int(game[5:game_id_end])

    prev_ind = game_id_end
    separator_ind = game.find(";")

    separators = [match.start()
                  for match in re.finditer(separator_pattern, game)]
    separators.append(len(game))

    for separator in separators:
        sub_string = game[prev_ind:separator]
        subset = {}

        # Then between the ranges.
        red_numbers = red_pattern.findall(sub_string)
        blue_numbers = blue_pattern.findall(sub_string)
        green_numbers = green_pattern.findall(sub_string)

        if red_numbers:
            subset["red"] = int(red_numbers[0].split()[0])

        if blue_numbers:
            subset["blue"] = int(blue_numbers[0].split()[0])

        if green_numbers:
            subset["green"] = int(green_numbers[0].split()[0])

        prev_ind = separator + 1
        subsets.append(subset)
    games[game_id] = subsets


# print(games)


for game_id, subsets in games.items():
    if all(
        [
            subset.get("blue", 0) <= max_blue
            and subset.get("red", 0) <= max_red
            and subset.get("green", 0) <= max_green
            for subset in subsets
        ]
    ):
        possible_games.append(game_id)


print(possible_games, sum(possible_games))
