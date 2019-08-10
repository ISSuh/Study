/*
https://www.acmicpc.net/problem/1541

세준이는 양수와 +, -, 그리고 괄호를 가지고 길이가 최대 50인 식을 만들었다. 그리고 나서 세준이는 괄호를 모두 지웠다.

그리고 나서 세준이는 괄호를 적절히 쳐서 이 식의 값을 최소로 만들려고 한다.

괄호를 적절히 쳐서 이 식의 값을 최소로 만드는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <numeric>

int main(){
    std::string S;
    std::cin >> S;

    std::vector<int> item;

    char* tok = strtok(&S[0], "-");
    while(tok!=NULL){
        std::string t = tok;
        int index = 0;
        int sum = 0;
        for(auto i = 0 ; i < t.size() ; ++i){
            if(t[i] == '+'){
                sum += std::stoi(t.substr(index, i - index));
                index = i+1;
            }
            else if(i == t.size() - 1)
                sum += std::stoi(t.substr(index, t.size() - index));
            
        }
        item.push_back(sum * -1);
		
        tok = strtok(NULL,"-");
	}

    if(S[0] != '-')
        item[0] *= -1;

    std::cout << std::accumulate(item.begin(), item.end(),0) << '\n';    
}