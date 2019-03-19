/*
https://www.acmicpc.net/problem/10825


도현이네 반 학생 N명의 이름과 국어, 영어, 수학 점수가 주어진다. 이때, 다음과 같은 조건으로 학생의 성적을 정렬하는 프로그램을 작성하시오.

    국어 점수가 감소하는 순서로
    국어 점수가 같으면 영어 점수가 증가하는 순서로
    국어 점수와 영어 점수가 같으면 수학 점수가 감소하는 순서로
    모든 점수가 같으면 이름이 사전 순으로 증가하는 순서로 (단, 아스키 코드에서 대문자는 소문자보다 작으므로 사전순으로 앞에 온다.)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

struct data{
    std::string name;
    int korean;
    int english;
    int math;
};

bool compare(data &v1, data &v2){
    if(v1.korean == v2.korean){
        if(v1.english == v2.english){
            if(v1.math == v2.math)
                return v1.name < v2.name;
            else
                return v1.math > v2.math; 
        }
        else
            return v1.english < v2.english;
    }
    else
        return v1.korean > v2.korean;
}

int main(){
    int N = 0;
    std::cin >> N;

    std::vector<data> item(N);

    for (auto i = 0; i < N ; i++)
            std::cin >> item[i].name >> item[i].korean >> item[i].english >> item[i].math;
    
    std::sort(item.begin(), item.end(), compare);

    for (auto i = 0; i < N ; i++)
        std::cout << item[i].name << "\n"; 
}
