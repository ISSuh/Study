#!/usr/bin/python

if __name__=='__main__' : 
    E,S,M = map(int,raw_input().split(' '))

    x = 1
    while True : 
        if (x-E)%15 == 0 and (x-S)%28 == 0 and  (x-M)%19 == 0 :
            break
        
        x += 1

    print(x)
