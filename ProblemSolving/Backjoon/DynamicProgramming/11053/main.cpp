/*
https://www.acmicpc.net/problem/11053

수열 A가 주어졌을 때, 가장 긴 증가하는 부분 수열을 구하는 프로그램을 작성하시오.

예를 들어, 수열 A = {10, 20, 10, 30, 20, 50} 인 경우에 가장 긴 증가하는 부분 수열은 A = {10, 20, 10, 30, 20, 50} 이고, 길이는 4이다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int n = 0;
    
    std::cin >> n;
    
    std::vector<int> item(n);
    std::vector<int> val(n);
    
    for (auto i=0; i<n; i++)
        std::cin >> item[i];
    
    val[0] = 1;

    for(auto i=1 ; i<n; i++){
        int maxValueIndex = 0, maxValue = 0;

        for(auto j=0 ; j<i ; j++){
            if((item[i] > item[j]) && (maxValue < val[j])){
                    maxValue = val[j];
                    maxValueIndex = j;
            }
        }

        if(item[i] > item[maxValueIndex])
            val[i] = 1 + val[maxValueIndex];
        else
            val[i] = val[maxValueIndex];    
    }

    std::cout << *std::max_element(val.begin(),val.end()) << std::endl;

}

