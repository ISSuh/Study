/*
https://www.acmicpc.net/problem/10820

문자열 N개가 주어진다. 이때, 문자열에 포함되어 있는 소문자, 대문자, 숫자, 공백의 개수를 구하는 프로그램을 작성하시오.

각 문자열은 알파벳 소문자, 대문자, 숫자, 공백으로만 이루어져 있다.

*/

#include <iostream>
#include <vector>

int main(){
    std::ios::sync_with_stdio(false);

    std::string S;
    
    while(std::getline(std::cin,S)){
        int bigACount = 0, smallACount = 0, numCount = 0, emptyCount = 0; 
        for (auto i = 0 ; i < S.length() ; i++){
            if(97 <= S[i] && S[i] <= 122)
                smallACount++;
            else if (65 <= S[i] && S[i] <= 90)
                bigACount++;
            else if (S[i] == ' ')
                emptyCount++;
            else 
                numCount++;
        }

        std::cout << smallACount << " " << bigACount << " " << numCount << " " << emptyCount << "\n";
    }
}
