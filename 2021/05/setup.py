from setuptools import setup
from Cython.Build import cythonize

setup(
    name='AOC day5',
    ext_modules=cythonize("day_5.pyx", language_level="3"),
    zip_safe=False,
)
