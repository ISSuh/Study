/* 
https://www.acmicpc.net/problem/11726

2×n 크기의 직사각형을 1×2, 2×1 타일로 채우는 방법의 수를 구하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>

int main(){
    int n = 0;

    std::cin >> n;
    std::vector<int> item(n);

    item[0] = 1;
    item[1] = 2;

    for(auto i = 2 ; i < item.size() ; i++)
        item[i] = (item[i-1] +item[i-2]) % 10007;
     
    std::cout << item[n-1] << std::endl;

    return 0;
}

