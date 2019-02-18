f __name__=='__main__' : 
    n,val = map(int,raw_input().split())

    coin = list()
    count = 0
    index = n-1

    for i in range(0,n) :
        coin.append(int(raw_input()))
    
    while val != 0 :

        if val >= coin[index] :
            count += val / coin[index]
            val -= (val / coin[index]) * coin[index]

        index -= 1
    
    print(count)

