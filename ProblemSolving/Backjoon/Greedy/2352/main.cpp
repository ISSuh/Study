/*
https://www.acmicpc.net/problem/2352

반도체를 설계할 때 n개의 포트를 다른 n개의 포트와 연결해야 할 때가 있다.
예를 들어 왼쪽 그림이 n개의 포트와 다른 n개의 포트를 어떻게 연결해야 하는지를 나타낸다. 하지만 이와 같이 연결을 할 경우에는 연결선이 서로 꼬이기 때문에 이와 같이 연결할 수 없다. n개의 포트가 다른 n개의 포트와 어떻게 연결되어야 하는지가 주어졌을 때, 연결선이 서로 꼬이지(겹치지, 교차하지) 않도록 하면서 최대 몇 개까지 연결할 수 있는지를 알아내는 프로그램을 작성하시오
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

int main(){
    int N = 0 ;
    std::cin >> N;
    
    int size = 0;
    std::vector<int> item(N+1), count(N+1);

    for(auto i = 1 ; i <= N ; ++i){
        int temp = 0;
        std::cin >> temp;

        item[i] = temp;
    }   

    count[1] = item[1];
    size++;
    for(auto i = 2 ; i <= N ; ++i){
        if(count[size] < item[i]) {
            ++size;
            count[size] = item[i];
            std::cout << size << '(' << i << ')' << " / ";

            continue;
        }

        auto it = std::lower_bound(count.begin() + 1, count.begin() + 1 + size, item[i]) - count.begin();
        
        // std::cout << it << '(' << i << ') ' << " / ";
        count[it] = item[i];
    }
    std::cout << '\n';
    std::cout << size << '\n';
}