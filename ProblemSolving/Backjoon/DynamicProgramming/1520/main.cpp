/*
https://www.acmicpc.net/problem/1520

여행을 떠난 세준이는 지도를 하나 구하였다. 이 지도는 아래 그림과 같이 직사각형 모양이며 여러 칸으로 나뉘어져 있다. 한 칸은 한 지점을 나타내는데 각 칸에는 그 지점의 높이가 쓰여 있으며, 각 지점 사이의 이동은 지도에서 상하좌우 이웃한 곳끼리만 가능하다.



현재 제일 왼쪽 위 칸이 나타내는 지점에 있는 세준이는 제일 오른쪽 아래 칸이 나타내는 지점으로 가려고 한다. 그런데 가능한 힘을 적게 들이고 싶어 항상 높이가 더 낮은 지점으로만 이동하여 목표 지점까지 가고자 한다. 위와 같은 지도에서는 다음과 같은 세 가지 경로가 가능하다.





지도가 주어질 때 이와 같이 제일 왼쪽 위 지점에서 출발하여 제일 오른쪽 아래 지점까지 항상 내리막길로만 이동하는 경로의 개수를 구하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

int DFS(std::vector<std::vector<int>> &val, int h, int w){
    std::stack<int> s;
    std::vector<std::vector<bool>> check(item.size(),false);

    s.push(val[1][1]);
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
}

int main(){
    int N = 0, M = 0;
    std::cin >> N >> M;

    std::vector<std::vector<int>> item(N+1, std::vector<int>(M+1, 0));
    std::vector<std::vector<int>> val(N+1, std::vector<int>(M+1, 0));
    

    for(auto i = 1 ; i <= N ; ++i)
        for(auto j = 1 ; j <= M ; ++j)
            std::cin >> item[i][j];

    for(auto i=1 ; i<=N ; ++i){
        for(auto j=1 ; j<=M ; ++j){
            if(i > 1 && j > 1){
                if(item[i][j] < item[i][j-1] && item[i][j] < item[i-1][j])
                    val[i][j] = val[i][j-1] + val[i-1][j];
                else if(item[i][j] < item[i][j-1] && item[i][j] >= item[i-1][j])
                    val[i][j] = val[i][j-1];
                else if(item[i][j] >= item[i][j-1] && item[i][j] < item[i-1][j])
                    val[i][j] = val[i-1][j];
                else
                    val[i][j] = 0;
            }
            else{
                if(item[i][j] < item[i][j-1] || item[i][j] < item[i-1][j])
                    ++val[i][j];
                else
                    val[i][j] = 0;
            }
        }
    }

    val[1][1] = 1;

    for(auto i=1 ; i<=N ; ++i){
        for(auto j=1 ; j<=M ; ++j){

        }
    }

    count = DFS(val);

    std::cout << '\n';
    for(auto &i : val){
        for(auto &j : i)
            std::cout << j << " ";
        std::cout << '\n';
    }

    std::cout << val[N][M] << '\n';
}


