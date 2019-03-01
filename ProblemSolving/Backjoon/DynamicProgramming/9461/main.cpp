/*
https://www.acmicpc.net/problem/9461

오른쪽 그림과 같이 삼각형이 나선 모양으로 놓여져 있다. 첫 삼각형은 정삼각형으로 변의 길이는 1이다. 그 다음에는 다음과 같은 과정으로 정삼각형을 계속 추가한다. 나선에서 가장 긴 변의 길이를 k라 했을 때, 그 변에 길이가 k인 정삼각형을 추가한다.

파도반 수열 P(N)은 나선에 있는 정삼각형의 변의 길이이다. P(1)부터 P(10)까지 첫 10개 숫자는 1, 1, 1, 2, 2, 3, 4, 5, 7, 9이다.
*/
#include <iostream>
#include <vector>

int main(){
    int N = 0;
    std::cin >> N;
    
    for(auto n = 0 ; n < N ; n++){
        int p = 0;
        std::cin >> p;
        if(p > 5){
            std::vector<long long> item(p+1);

            item[0] = 0;
            item[1] = 1; item[2] = 1; item[3] = 1;
            item[4] = 2; item[5] = 2;

            for(auto i = 6 ; i < p+1 ; i++)
                item[i] = item[i-1] + item[i-5];

            std::cout << item[p] << std::endl;
        }
        else{
            switch(p){
                case 1:
                case 2:
                case 3:
                    std::cout << 1 << std::endl;
                    break;
                case 4:
                case 5:
                    std::cout << 2 << std::endl;
                    break;
            }
        }
    }    
}

