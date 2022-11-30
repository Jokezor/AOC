import unittest
from .day5 import binary_search, search_boarding_passes


class MyTestCase(unittest.TestCase):
    def test_example_0_boarding_pass(self):
        id = binary_search('FBFBBFFRLR')
        self.assertEqual(id, 357)

    def test_example_1_boarding_pass(self):
        id = binary_search('BFFFBBFRRR')
        self.assertEqual(id, 567)

    def test_example_2_boarding_pass(self):
        id = binary_search('FFFBBBFRRR')
        self.assertEqual(id, 119)

    def test_example_3_boarding_pass(self):
        id = binary_search('BBFFBBFRLL')
        self.assertEqual(id, 820)

    def test_highest_id(self):
        boarding_passes = ['FBFBBFFRLR', 'BFFFBBFRRR', 'FFFBBBFRRR', 'BBFFBBFRLL']
        highest_id = search_boarding_passes(boarding_passes)
        self.assertEqual(highest_id, 820)


if __name__ == '__main__':
    unittest.main()
