def read_file(file_name: str) -> list:
    return [{line.split('contain')[0].replace(' ', '')[:-1]: [bag.replace(' ', '')[1:].replace('.', '')
                                                              if (bag.replace(' ', '')[0]) == '1'
                                                              else bag.replace(' ', '')[1:].replace('.', '')[:-1]
                                                              for bag in line.split('contain')[1].split(',')]}
            for line in open(file_name, 'r').read().split('\n')]


def list_to_dict(bag_holds: list) -> dict:

    new_set = {}
    for bag_dict in bag_holds:
        key = list(bag_dict.keys())[0]
        new_set[key] = bag_dict[key]
    return new_set


def find_gold_bag(bag_list: list, bag_holds: dict) -> int:
    #print(bag_holds)

    #print(bag_list, bag_holds)
    for bag in bag_list:
        if bag != 'ootherbag':
            print(bag, bag_holds[bag])
        if bag == 'shinygoldbag':
            return 1
        elif bag == 'ootherbag':
            return 0
        else:
            return find_gold_bag(bag_holds[bag], bag_holds)


def search_all_bags(bag_holds: dict) -> int:

    tot = 0
    for bag_list in bag_holds.values():
        tot += find_gold_bag(bag_list, bag_holds)
    return tot


if __name__ == '__main__':
    file_name = 'example_input.txt'
    bag_holds = read_file(file_name)
    bag_holds = list_to_dict(bag_holds)
    print(search_all_bags(bag_holds))



# What if we build a dict/tree structure:
# ex: bag_holds = {'dark_orange': ['bright_whitebag', 'red_bag'], 'bright_whitebag': ['shiny gold bag'], 'red_bag': []}
# Loop through the set keys,


