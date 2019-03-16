/*
https://www.acmicpc.net/problem/1931

한 개의 회의실이 있는데 이를 사용하고자 하는 N개의 회의들에 대하여 회의실 사용표를 만들려고 한다. 각 회의 I에 대해 시작시간과 끝나는 시간이 주어져 있고, 각 회의가 겹치지 않게 하면서 회의실을 사용할 수 있는 최대수의 회의를 찾아라. 단, 회의는 한번 시작하면 중간에 중단될 수 없으며 한 회의가 끝나는 것과 동시에 다음 회의가 시작될 수 있다. 회의의 시작시간과 끝나는 시간이 같을 수도 있다. 이 경우에는 시작하자마자 끝나는 것으로 생각하면 된다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

bool comp(std::vector<int> &v1, std::vector<int> &v2){
    if(v1[1] == v2[1])
        return v1[0] < v2[0];
    else
        return v1[1] < v2[1];
}

int main(){
    int N = 0, count = 0, temp = 0;
    std::cin >> N;

    std::vector<std::vector<int>> item(N,std::vector<int>(2));

    for(auto i = 0 ; i < N ; i++)
        for(auto j = 0 ; j < 2 ; j++)
            std::cin >> item[i][j];

    std::sort(item.begin(),item.end(), comp);

    for(auto i = 0 ; i < N ; i++){
        if(temp <= item[i][0]){
            temp = item[i][1];
            count++;
        }
    }   
    
    std::cout << count << "\n";
}