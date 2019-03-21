/*
https://www.acmicpc.net/problem/10809

알파벳 소문자로만 이루어진 단어 S가 주어진다. 각각의 알파벳에 대해서, 단어에 포함되어 있는 경우에는 처음 등장하는 위치를, 포함되어 있지 않은 경우에는 -1을 출력하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>

int main(){
    std::ios::sync_with_stdio(false);

    std::string S;
    std::cin >> S;

    std::vector<int> item(26,-1);

    for (auto i = 0 ; i < S.length() ; i++){
        if(item[S[i]-97] == -1)
            item[S[i]-97] = i;
    }

    for (auto i = 0 ; i < 26 ; i++)
        std::cout << item[i] << " ";

    std::cout << "\n";
}
