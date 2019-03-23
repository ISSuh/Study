/*
https://www.acmicpc.net/problem/1260

그래프를 DFS로 탐색한 결과와 BFS로 탐색한 결과를 출력하는 프로그램을 작성하시오. 단, 방문할 수 있는 정점이 여러 개인 경우에는 정점 번호가 작은 것을 먼저 방문하고, 더 이상 방문할 수 있는 점이 없는 경우 종료한다. 정점 번호는 1번부터 N번까지이다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

void DFS(std::vector<std::vector<int>> &item, int start){
    std::stack<int> s;
    std::vector<bool> check(item.size(),false);
    std::vector<int> result;

    s.push(start);
    // result.push_back(start);

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
            // if(check[nextNode]==false){
            //     result.push_back(nextNode);
				
            //     check[nextNode] = true;
			// 	s.push(currentNode);
			// 	s.push(nextNode);

			// 	break;
			// }

            if(!check[nextNode])
                s.push(nextNode);
        }
    }

    for(auto i = result.begin() ; i != result.end() ; i++)
        std::cout << *i << " ";
    std::cout << "\n";    
}

void BFS(std::vector<std::vector<int>> &item, int start){
    std::queue<int> q;
    std::vector<bool> check(item.size(),false);
    std::vector<int> result;

    q.push(start);
    // result.push_back(start);

    while(!q.empty()){
        int currentNode = q.front();
        q.pop();

        if(check[currentNode])
            continue;
        else
            check[currentNode] = true;

        result.push_back(currentNode);

        for(auto i = item[currentNode].begin() ; i != item[currentNode].end() ; i++){
            int nextNode = *i;
            // if(!check[nextNode]){
            //     result.push_back(nextNode);
            //     check[nextNode] = true;
            //     q.push(nextNode);
            // }
            if(!check[nextNode])
                q.push(nextNode);
        }
    }

    for(auto i = result.begin() ; i != result.end() ; i++)
        std::cout << *i << " ";
    std::cout << "\n";    
}

int main(){
    std::ios::sync_with_stdio(false);

    int N = 0, M = 0, V = 0;
    std::cin >> N >> M >> V;

    std::vector<std::vector<int>> item(N+1);
    
    for(auto i = 0 ; i < M ; i++){
        int n = 0, m  = 0;
        std::cin >> n >> m;

        item[n].push_back(m);
        item[m].push_back(n);
    }
    
    for(auto i = item.begin() ; i != item.end() ; i++)
        std::sort(i->begin(), i->end());

    DFS(item, V);
    BFS(item, V);
}