#!/bin/sh

# 1. get original answers
cat tests.txt | ./old > original.txt
cat tests.txt | ./new > new.txt

diff original.txt new.txt
