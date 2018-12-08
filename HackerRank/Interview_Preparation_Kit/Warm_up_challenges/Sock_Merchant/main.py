#!/bin/python

import math
import os
import random
import re
import sys

# Complete the sockMerchant function below.
def sockMerchant(n, ar):
    result = 0
    socks = dict()

    for x in ar :
        if x in socks :
            socks[x] = socks[x] + 1
        else :
            socks[x] =1
    
    for k in socks.keys() :
        result += socks[k] / 2

    return result

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(raw_input())

    ar = map(int, raw_input().rstrip().split())

    result = sockMerchant(n, ar)

    fptr.write(str(result) + '\n')

    fptr.close()

