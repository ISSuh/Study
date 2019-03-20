#-*- coding: utf-8 -*-
'''
https://www.acmicpc.net/problem/10845

정수를 저장하는 큐를 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.

명령은 총 여섯 가지이다.

    push X: 정수 X를 큐에 넣는 연산이다.
    pop: 큐에서 가장 앞에 있는 정수를 빼고, 그 수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
    size: 큐에 들어있는 정수의 개수를 출력한다.
    empty: 큐가 비어있으면 1, 아니면 0을 출력한다.
    front: 큐의 가장 앞에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
    back: 큐의 가장 뒤에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.

'''

from __future__ import print_function
import sys

class myQueue :
    def __init__(self) :
        self.arr = []
    
    def size(self) : 
        return len(self.arr)
    
    def empty(self) :
        if not self.arr:
            return 1
        else :
            return 0

    def push(self,val) :
        self.arr.append(val)

    def pop(self) : 
        if self.empty() == 1 :
            return -1
        else :
            return self.arr.pop(0)

    def front(self) :
        if self.empty() == 1:
            return -1
        else :
            return self.arr[0]

    def back(self) :
        if self.empty() == 1:
            return -1
        else :
            return self.arr[-1]
    
            
if __name__ == "__main__" :
    N = int(raw_input())

    mqueue = myQueue()

    for i in range(0,N) : 
        command = map(str, raw_input().split(' '))
        
        if command[0] == "push" : 
            mqueue.push(int(command[1]))
        elif command[0] == "pop" : 
            print(mqueue.pop())
        elif command[0] == "size" : 
            print(mqueue.size())
        elif command[0] == "empty" : 
            print(mqueue.empty())
        elif command[0] == "front" : 
            print(mqueue.front())
        elif command[0] == "back" : 
            print(mqueue.back())
