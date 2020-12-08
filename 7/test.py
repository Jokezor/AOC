import unittest
from .day7 import find_gold_bag, search_all_bags


class SearchAllBagsTestCase(unittest.TestCase):
    def test_search_all_bags(self):
        bag_holds = {'dark_orange': ['bright_whitebag', 'red_bag'], 'bright_whitebag': ['shiny gold bag'], 'red_bag': []}
        self.assertEqual(search_all_bags(bag_holds), 1)


if __name__ == '__main__':
    unittest.main()
