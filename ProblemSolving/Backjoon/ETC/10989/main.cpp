/*
https://www.acmicpc.net/problem/10989

N개의 수가 주어졌을 때, 이를 오름차순으로 정렬하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <map>

int main()
{
    std::ios::sync_with_stdio(false);
    
    int n = 0;
	std::cin >> n;
	std::map<int,int> item;

	for (auto i = 0; i < n; i++){
		int temp = 0;
        std::cin >> temp;

        item[temp]++;
    }

	for (auto i = item.begin() ; i != item.end() ; i++)
        for(auto j = 0 ; j < i->second ; j++)
            std::cout << i->first << "\n";
}
