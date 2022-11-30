from setuptools import setup
from Cython.Build import cythonize

setup(
    name='First day of AOC',
    ext_modules=cythonize("day_1.pyx"),
    zip_safe=False,
)

