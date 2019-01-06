#!/bin/python

import math
import os
import random
import re
import sys

# Complete the solve function below.
def solve(s):
    temp = True
    result = ''

    for i,c in enumerate(s) :
        if(temp == True) : 
            result += c.upper()
            temp = False
        else :
            result += c

        if(c == ' ') :
            temp = True
    
    return result

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s = raw_input()

    result = solve(s)

    fptr.write(result + '\n')

    fptr.close()

