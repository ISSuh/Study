#!/usr/bin/python

if __name__=='__main__' : 
    woman, man, intern = map(int,raw_input().split())
    
    while intern > 0 :
        if woman/2 >= man :
            woman -= 1
        else :
            man -= 1

        intern -= 1
    
    if(woman/2 <= man) :
        print(woman)
    else :
        print(man)


