from setuptools import setup
from Cython.Build import cythonize

setup(
    name='AOC day4',
    ext_modules=cythonize("day_4.pyx"),
    zip_safe=False,
)
