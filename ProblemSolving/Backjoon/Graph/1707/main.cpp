/*
https://www.acmicpc.net/problem/1707

그래프의 정점의 집합을 둘로 분할하여, 각 집합에 속한 정점끼리는 서로 인접하지 않도록 분할할 수 있을 때, 그러한 그래프를 특별히 이분 그래프 (Bipartite Graph) 라 부른다.

그래프가 입력으로 주어졌을 때, 이 그래프가 이분 그래프인지 아닌지 판별하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>
#include <queue>

enum COLOR{
    WHITE = 1,
    BLACK = 2,
    NONE = 3
};

void BFS(std::vector<std::vector<int>> &item, int &start, std::vector<COLOR> &color){
    std::queue<int> q; 
    std::vector<int> result;
    std::vector<bool> check(item.size(), false);

    q.push(start);
    color[start] = WHITE;

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
            if(!check[nextNode]){
                q.push(nextNode);
                
                if(color[currentNode] == WHITE)
                    color[nextNode] = BLACK;
                else
                    color[nextNode] = WHITE;
                std::cout << "[" << currentNode << "," << nextNode << "]" << " ";
            }
        }
        std::cout << "\n";
    }

    std::cout << "BFS : ";
    for(auto i = result.begin() ; i != result.end() ; i++)
        std::cout << *i << " ";
    std::cout << "\n";

    std::cout << "COLOR : ";
    for(auto i = result.begin() ; i != result.end() ; i++)
        std::cout << color[*i] << " ";
    std::cout << "\n";
}

int main(){
    std::ios::sync_with_stdio(false);

    int K = 0, V = 0, E = 0;
    std::cin >> K;

    for(auto k = 0 ; k < K ; k++){
        std::cin >> V >> E;

        std::vector<std::vector<int>> item(V+1);
        std::vector<COLOR> color(V+1, NONE);

        for(auto i = 0 ; i < E ; i++){
            int n = 0, m  = 0;
            std::cin >> n >> m;

            item[n].push_back(m);
            item[m].push_back(n);
        }

        for(auto i = 1; i < V+1 ; i++){
            if(color[i] == NONE) 
                BFS(item, i, color);
        }
    }
}