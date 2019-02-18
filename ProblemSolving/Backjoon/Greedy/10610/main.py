f __name__=='__main__' : 
    val = raw_input()
    
    if "0" in val and sum([int(x) for x in val]) % 3 == 0 :
        valInt = [int(x) for x in val]
        valInt.sort(reverse=True)
        print(''.join(str(e) for e in valInt))
    else : 
        print(-1)
    


