def recursiveSearch(d: dict, dictList: list) -> bool:
    if(d.get("name") == "shiny gold"):
        return True

    for bag in d.keys():
        if bag == "name":
            continue
        newDtoSearch = [d for d in dictList if d["name"] == bag]
        print(bag, newDtoSearch)
        print(dictList)
        if(recursiveSearch(*newDtoSearch, dictList) == True):
            return True

    return False


def createDictionary(line: str) -> dict:
    newDict = dict()
    if "no" in line:
        newDict["name"] = line.split('bags')[0].strip(' ')
        return newDict

    l = line.strip('\n').replace('bags', 'bag').replace('contain', '').replace(',', '').split('bag')
    name = l[0].strip(' ')
    newDict["name"] = name
    for i in range(1,len(l)-1):
        bag = l[i].strip(' ')
        value = bag[0]
        key = bag[2:]
        newDict[key] = value

    return newDict


def recursiveCount(d: dict, dictList: list) -> int:
    if (len(d) == 1):
        return 1

    sum = 0
    for bag in d.keys():
        if bag == "name":
            continue
        newDtoSearch = [d for d in dictList if d["name"] == bag]
        multiplier = int(d.get(bag))
        sum += multiplier * recursiveCount(*newDtoSearch, dictList)

    return sum + 1


def main():
    f = open("example_input.txt", "r");

    listOfDicts = list()
    for line in f:
        d = createDictionary(line)
        listOfDicts.append(d)

    # search part 1
    count = 0
    for d in listOfDicts:
        if(recursiveSearch(d, listOfDicts)):
            count += 1
    print("part 1: ", (count-1)) # minus 1 for the shiny gold bag

    # search part 2
    d = [d for d in listOfDicts if d["name"] == "shiny gold"]
    count = recursiveCount(*d, listOfDicts)
    print("part 2: ", (count-1)) # minus 1 for the shiny gold bag

    f.close()

if __name__ == '__main__':
    main()