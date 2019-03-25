/*
https://www.acmicpc.net/problem/10451

1부터 N까지 정수 N개로 이루어진 순열을 나타내는 방법은 여러 가지가 있다. 예를 들어, 8개의 수로 이루어진 순열 (3, 2, 7, 8, 1, 4, 5, 6)을 배열을 이용해 표현하면

와 같다. 또는, Figure 1과 같이 방향 그래프로 나타낼 수도 있다.

순열을 배열을 이용해

로 나타냈다면, i에서 πi로 간선을 이어 그래프로 만들 수 있다.

Figure 1에 나와있는 것 처럼, 순열 그래프 (3, 2, 7, 8, 1, 4, 5, 6) 에는 총 3개의 사이클이 있다. 이러한 사이클을 "순열 사이클" 이라고 한다.

N개의 정수로 이루어진 순열이 주어졌을 때, 순열 사이클의 개수를 구하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

void DFS(std::vector<std::vector<int>> &item, std::vector<bool> &check, int &start){
    std::stack<int> s;

    s.push(start);

    while(!s.empty()){
        int currentNode = s.top();
        s.pop();

        if(check[currentNode])
            continue;
        else
            check[currentNode] = true;

        for(auto i =  item[currentNode].rbegin();  i != item[currentNode].rend() ; i++){
            int nextNode = *i;

            if(!check[nextNode])
                s.push(nextNode);
        }
    }
}

void BFS(std::vector<std::vector<int>> &item, std::vector<bool> &check, int &start){
    std::queue<int> q;

    q.push(start);

    while(!q.empty()){
        int currentNode = q.front();
        q.pop();

        if(check[currentNode])
            continue;
        else
            check[currentNode] = true;

        for(auto i = item[currentNode].begin() ; i != item[currentNode].end() ; i++){
            int nextNode = *i;
            if(!check[nextNode])
                q.push(nextNode);
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);

    int T =  0;
    std::cin >> T;

    while(T--){
        int N = 0, count = 0;
        std::cin >> N;

        std::vector<std::vector<int>> item(N+1);
        std::vector<bool> check(N+1,false);

        for(auto i = 1 ; i < N+1 ; i++){
            int n = 0;
            std::cin >> n;

            item[i].push_back(n);
        }

        for(auto i = 1 ; i < N+1 ; i++){
            if(!check[i]){
                DFS(item, check, i);
                // BFS(item, check, i);
                count++;
            }
        }
        
        std::cout << count << "\n";
    }
}