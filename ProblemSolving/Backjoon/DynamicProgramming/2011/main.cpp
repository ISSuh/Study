/*
https://www.acmicpc.net/problem/2011

상근이와 선영이가 다른 사람들이 남매간의 대화를 듣는 것을 방지하기 위해서 대화를 서로 암호화 하기로 했다. 그래서 다음과 같은 대화를 했다.

    상근: 그냥 간단히 암호화 하자. A를 1이라고 하고, B는 2로, 그리고 Z는 26으로 하는거야.
    선영: 그럼 안돼. 만약, "BEAN"을 암호화하면 25114가 나오는데, 이걸 다시 글자로 바꾸는 방법은 여러 가지가 있어.
    상근: 그렇네. 25114를 다시 영어로 바꾸면, "BEAAD", "YAAD", "YAN", "YKD", "BEKD", "BEAN" 총 6가지가 나오는데, BEAN이 맞는 단어라는건 쉽게 알수 있잖아?
    선영: 예가 적절하지 않았네 ㅠㅠ 만약 내가 500자리 글자를 암호화 했다고 해봐. 그 때는 나올 수 있는 해석이 정말 많은데, 그걸 언제 다해봐?
    상근: 얼마나 많은데?
    선영: 구해보자!

어떤 암호가 주어졌을 때, 그 암호의 해석이 몇 가지가 나올 수 있는지 구하는 프로그램을 작성하시오.
*/
#include <iostream>
#include <string>
#include <vector>

int main(){
    std::string N;
    std::getline(std::cin,N);
    
    size_t lenN = N.size();
    std::vector<int> item(lenN+1);

    if(N.size() < 2){
        switch (atoi(N.c_str())){
            case 0:
                std::cout << 0 << std::endl;
                return 0;
            default:
                std::cout << 1 << std::endl;
                return 0;
        }
    }
    
    item[0] = 1; item[1] = 1;
    for(auto i = 2 ; i < lenN+1 ; i++){
        if(N[i-1] > '0')
            item[i] = item[i-1] % 1000000;;

        if(10 <= std::atoi(N.substr(i-2,2).c_str()) && std::atoi(N.substr(i-2,2).c_str()) <= 26)
            item[i] = (item[i] + item[i-2]) % 1000000;    
        
    }

    std::cout << item[lenN] << std::endl;
}

