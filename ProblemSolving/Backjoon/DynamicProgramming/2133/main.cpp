/*
https://www.acmicpc.net/problem/2133

3×N 크기의 벽을 2×1, 1×2 크기의 타일로 채우는 경우의 수를 구해보자.
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int n = 0;
    
    std::cin >> n;
    
    std::vector<int> item(n+1);
    
    if(n % 2 == 0){
        item[0] = 1; item[2] = 3;

        for(auto i=4 ; i < n+1 ; i += 2){
            item[i] += item[i-2]*3;
            for(auto j=i-4 ; j >= 0 ; j -= 2)
                item[i] += item[j]*2;
        }
    }
    std::cout << item[n] << std::endl;    
}

