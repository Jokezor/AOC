from setuptools import setup
from Cython.Build import cythonize

setup(
    name='AOC day3',
    ext_modules=cythonize("day_3.pyx"),
    zip_safe=False,
)
