/*
https://www.acmicpc.net/problem/11652

준규는 숫자 카드 N장을 가지고 있다. 숫자 카드에는 정수가 하나 적혀있는데, 적혀있는 수는 -262보다 크거나 같고, 262보다 작거나 같다.

준규가 가지고 있는 카드가 주어졌을 때, 가장 많이 가지고 있는 정수를 구하는 프로그램을 작성하시오. 만약, 가장 많이 가지고 있는 정수가 여러 가지라면, 작은 것을 출력한다.
*/

#include <iostream>
#include <map>
#include <limits>

int main(){
    std::ios::sync_with_stdio(false);

    int N = 0, maxCount = 0;
    long long min = std::numeric_limits<long long>::max();

    std::cin >> N;

    std::map<long long, int> item;

    for (auto i = 0; i < N ; i++){
        long long temp = 0;
        std::cin >> temp;

        int count = ++item[temp];

        if(maxCount < count)
            maxCount = count;
    }    

    for(auto i = item.begin() ; i != item.end() ; i++)
        if(maxCount == i->second && min > i->first)
            min = i->first;

    std::cout << min << "\n";
}
