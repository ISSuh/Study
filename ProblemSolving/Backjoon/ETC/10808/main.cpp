/*
https://www.acmicpc.net/problem/10808

알파벳 소문자로만 이루어진 단어 S가 주어진다. 각 알파벳이 단어에 몇 개가 포함되어 있는지 구하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>

int main(){
    std::ios::sync_with_stdio(false);

    std::string S;
    std::cin >> S;

    std::vector<int> item(26,0);

    for (auto i = 0 ; i < S.length() ; i++)
        item[S[i]-97]++;

    for (auto i = 0 ; i < 26 ; i++)
        std::cout << item[i] << " ";

    std::cout << "\n";
}
