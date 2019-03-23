/*
https://www.acmicpc.net/problem/1260

그래프를 DFS로 탐색한 결과와 BFS로 탐색한 결과를 출력하는 프로그램을 작성하시오. 단, 방문할 수 있는 정점이 여러 개인 경우에는 정점 번호가 작은 것을 먼저 방문하고, 더 이상 방문할 수 있는 점이 없는 경우 종료한다. 정점 번호는 1번부터 N번까지이다.
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