/*
https://www.acmicpc.net/problem/11650

2차원 평면 위의 점 N개가 주어진다. 좌표를 x좌표가 증가하는 순으로, x좌표가 같으면 y좌표가 증가하는 순서로 정렬한 다음 출력하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>
#include <algorithm>

bool compare(std::vector<int> &v1, std::vector<int> &v2){
    if(v1[0] == v2[0])
        return v1[1] < v2[1];
    else
        return v1[0] < v2[0];
}

int main(){
    int N = 0;
    std::cin >> N;

    std::vector<std::vector<int>> item(N, std::vector<int>(2));

    for (auto i = 0; i < N ; i++)
        for(auto j = 0 ; j < 2 ; j++)
            std::cin >> item[i][j];
    
    std::sort(item.begin(), item.end(), compare);

    for (auto i = 0; i < N ; i++){
        for(auto j = 0 ; j < 2 ; j++)
            std::cout << item[i][j] << " ";
        std::cout << "\n";
    }    
}
