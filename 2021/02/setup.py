from setuptools import setup
from Cython.Build import cythonize

setup(
    name='AOC day2',
    ext_modules=cythonize("day_2.pyx"),
    zip_safe=False,
)
