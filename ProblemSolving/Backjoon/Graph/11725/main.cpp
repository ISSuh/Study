/*
https://www.acmicpc.net/problem/11725

루트 없는 트리가 주어진다. 이때, 트리의 루트를 1이라고 정했을 때, 각 노드의 부모를 구하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

void DFS(std::vector<std::vector<int>> &item, int start, std::vector<int> &result){
    std::stack<int> s;
    std::vector<bool> check(item.size(),false);
    s.push(start);

    while(!s.empty()){
        int currentNode = s.top();
        s.pop();

        if(check[currentNode])
            continue;
        else
            check[currentNode] = true;
        
        result.push_back(currentNode);

        for(auto i =  item[currentNode].rbegin();  i != item[currentNode].rend() ; i++){
            int nextNode = *i;
            
            if(!check[nextNode]){ 
                s.push(nextNode);
                result[nextNode] = currentNode;
            }
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);

    int N = 0;
    std::cin >> N;

    std::vector<std::vector<int>> item(N+1);
    std::vector<int> result(N+1);
    
    for(auto i = 0 ; i < N-1 ; i++){
        int n = 0, m  = 0;
        std::cin >> n >> m;

        item[n].push_back(m);
        item[m].push_back(n);
    }

    DFS(item, 1, result);

    for(auto i = 2 ; i <= N ; i++)
        std::cout << result[i] << "\n";
}