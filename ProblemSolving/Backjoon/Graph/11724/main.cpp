/*
https://www.acmicpc.net/problem/11724

방향 없는 그래프가 주어졌을 때, 연결 요소 (Connected Component)의 개수를 구하는 프로그램을 작성하시오.
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

    int N = 0, M = 0, count = 0;
    std::cin >> N >> M;

    std::vector<std::vector<int>> item(N+1);
    std::vector<bool> check(N+1,false);
    
    for(auto i = 0 ; i < M ; i++){
        int n = 0, m  = 0;
        std::cin >> n >> m;

        item[n].push_back(m);
        item[m].push_back(n);
    }

    for(auto i = 1; i < item.size() ; i++){
        if(!check[i]){
            // DFS(item, check, i);
            BFS(item, check, i);
            count++;
        }
    }

    std::cout << count << "\n";
}