/*
https://www.acmicpc.net/problem/11653

정수 N이 주어졌을 때, 소인수분해하는 프로그램을 작성하시오.
*/
#include <iostream>
#include <math.h>

int main(){
    int N = 0, A = 2;
    std::cin >> N;

    while (A <= sqrt(N)){
        for (A; A <= sqrt(N); A++){
            if (N % A == 0){
                std::cout << A << '\n';
                
                N /= A;
                break;
            }
        }
    }

    std::cout << N << '\n';
}
