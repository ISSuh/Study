import sys


def main() :
	arr = []
	for _ in range(int(raw_input())):
    		name = raw_input()
    		score = float(raw_input())
        
   		arr.append([name,score])
		
	result = [x for (x,y) in arr if y == min(y for (x,y) in arr if y != min(y for (x,y) in arr))]
	result.sort()
	
	for x in result : print(x)

if __name__ == "__main__" :
	main()
