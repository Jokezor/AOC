#!/bin/sh

# 1. get original answers
cat input.txt | ./old > original.txt
cat input.txt | ./new > new.txt

diff original.txt new.txt
