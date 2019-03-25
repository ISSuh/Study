/*
https://www.acmicpc.net/problem/10872

0보다 크거나 같은 정수 N이 주어진다. 이때, N!을 출력하는 프로그램을 작성하시오.
*/
#include <iostream>

int main(){
    int n = 0;
    long long factorial = 1;
    std::cin >> n;

    for (auto i = 1; i <= n; i++)
        factorial *= i;

    std::cout << factorial << "\n";
}
