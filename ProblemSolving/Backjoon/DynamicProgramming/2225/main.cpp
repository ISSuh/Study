/*
https://www.acmicpc.net/problem/2225

0부터 N까지의 정수 K개를 더해서 그 합이 N이 되는 경우의 수를 구하는 프로그램을 작성하시오.

덧셈의 순서가 바뀐 경우는 다른 경우로 센다(1+2와 2+1은 서로 다른 경우). 또한 한 개의 수를 여러 번 쓸 수도 있다.

*/
#include <iostream>
#include <vector>

int main(){
    int N = 0, K = 0;
    std::cin >> N >> K;

    std::vector<std::vector<long long>> item(N+1,std::vector<long long>(K+1,1));

    for(auto i = 1 ; i < N+1 ; i++)
        for(auto j = 2 ; j < K+1 ; j++)
            for(auto k = 1 ; k <= i ; k++)
                item[i][j] += item[k][j-1] % 1000000000;
    
    std::cout << item[N][K] % 1000000000 << std::endl;
}

