/*
https://www.acmicpc.net/problem/9251

LCS(Longest Common Subsequence, 최장 공통 부분 수열)문제는 두 수열이 주어졌을 때, 모두의 부분 수열이 되는 수열 중 가장 긴 것을 찾는 문제이다.

예를 들어, ACAYKP와 CAPCAK의 LCS는 ACAK가 된다.

*/

#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    std::string N, M;
    std::cin >> N >> M;

    std::string longLen = N.size() >= M.size() ? N : M;
    std::string shortLen = N.size() < M.size() ? N : M;

    std::vector<std::vector<int>> item(shortLen.size(), std::vector<int>(longLen.size(), 0));

    for(auto i = 0 ; i < shortLen.size() ; ++i){
        for(auto j = 0 ; j < longLen.size() ; ++j){
            if(shortLen[i] == longLen[j]){
                if(i > 0 && j > 0)
                    item[i][j] = item[i-1][j-1] + 1;
                else
                    ++item[i][j];
            }
            else{
                if(i > 0 && j > 0)
                    item[i][j] = item[i-1][j] > item[i][j-1] ? item[i-1][j] : item[i][j-1];
                else if(i > 0 && j <= 0)
                    item[i][j] = item[i-1][j];
                else if(i <=0 && j > 0)
                    item[i][j] = item[i][j-1];
            }
        }
    }

    std::cout << item[shortLen.size()-1][longLen.size()-1] << '\n';
}