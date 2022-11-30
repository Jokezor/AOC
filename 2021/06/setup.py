from setuptools import setup
from Cython.Build import cythonize

setup(
    name='AOC day6',
    ext_modules=cythonize("day_6.pyx", language_level="3"),
    zip_safe=False,
)
