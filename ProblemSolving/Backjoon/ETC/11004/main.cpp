/*
https://www.acmicpc.net/problem/11004

수 N개 A1, A2, ..., AN이 주어진다. A를 오름차순 정렬했을 때, 앞에서부터 K번째 있는 수를 구하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    std::ios::sync_with_stdio(false);

    int N = 0, K = 0;
    std::cin >> N >> K;

    std::vector<int> item(N);
    
    for(auto i = 0 ; i < N ; i++)
        std::cin >> item[i];

    std::sort(item.begin(), item.end());

    std::cout << item[K-1] << "\n";
}
