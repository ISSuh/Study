/*
https://www.acmicpc.net/problem/11054

수열 S가 어떤 수 Sk를 기준으로 S1 < S2 < ... Sk-1 < Sk > Sk+1 > ... SN-1 > SN을 만족한다면, 그 수열을 바이토닉 수열이라고 한다.

예를 들어, {10, 20, 30, 25, 20}과 {10, 20, 30, 40}, {50, 40, 25, 10} 은 바이토닉 수열이지만,  {1, 2, 3, 2, 1, 2, 3, 2, 1}과 {10, 20, 30, 40, 20, 30} 은 바이토닉 수열이 아니다.

수열 A가 주어졌을 때, 그 수열의 부분 수열 중 바이토닉 수열이면서 가장 긴 수열의 길이를 구하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int n = 0;
    
    std::cin >> n;
    
    std::vector<int> item(n);
    std::vector<int> val(n), reverseVal(n);
    
    for (auto i=0; i<n; i++)
        std::cin >> item[i];
    
    val[0] = 1;
    for(auto i=1 ; i<n; ++i){
        int maxValueIndex = 0, maxValue = 0;

        for(auto j=0 ; j<i ; ++j){
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

    reverseVal[n-1] = 1;
    for(auto i=n-2 ; i>=0; --i){
        int maxValueIndex = n-1, maxValue = 0;

        for(auto j=n-1 ; j>=i ; --j){
            if((item[i] > item[j]) && (maxValue < reverseVal[j])){
                    maxValue = reverseVal[j];
                    maxValueIndex = j;
            }
        }

        if(item[i] > item[maxValueIndex])
            reverseVal[i] = 1 + reverseVal[maxValueIndex];
        else
            reverseVal[i] = reverseVal[maxValueIndex];    
    }

    for(auto i=0 ; i < n ; ++i)
        val[i] = val[i] + reverseVal[i];
        
    std::cout << *std::max_element(val.begin(),val.end())-1 << std::endl;

}


