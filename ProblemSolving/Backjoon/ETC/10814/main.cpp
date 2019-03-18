/*
https://www.acmicpc.net/problem/10814

온라인 저지에 가입한 사람들의 나이와 이름이 가입한 순서대로 주어진다. 이때, 회원들을 나이가 증가하는 순으로, 나이가 같으면 먼저 가입한 사람이 앞에 오는 순서로 정렬하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>
#include <algorithm>

struct data{
    int num;
    std::string name;
    int index;
};

bool compare(data &v1, data &v2){
    if(v1.num == v2.num)
        return v1.index < v2.index;
    else
        return v1.num < v2.num;
}

int main(){
    int N = 0;
    std::cin >> N;

    std::vector<data> item(N);

    for (auto i = 0; i < N ; i++){
            std::cin >> item[i].num >> item[i].name;
            item[i].index = i;
    }
    
    std::sort(item.begin(), item.end(), compare);

    for (auto i = 0; i < N ; i++)
        std::cout << item[i].num << " " << item[i].name << "\n"; 
}
