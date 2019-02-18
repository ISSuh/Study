#!/bin/python

import math
import os
import random
import re
import sys

# Complete the countingValleys function below.
def countingValleys(n, s):
    count = 0
    level = 0
    path = []

    for x in s :
        if x == 'U' :
            level += 1
            if level <= 0 :
                path.pop()

                if len(path) == 0 :
                    count += 1

        else : 
            level -= 1
            if level < 0 :
                path.append(x)

    return count
    
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(raw_input())

    s = raw_input()

    result = countingValleys(n, s)

    fptr.write(str(result) + '\n')

    fptr.close()

