import unittest
from .day6 import reduce_array


class SeparateFunctionsTestCase(unittest.TestCase):
    def test_reduce(self):
        num_questions = [1, 2, 3, 5, 6]
        self.assertEqual(reduce_array(num_questions), 17)


if __name__ == '__main__':
    unittest.main()
