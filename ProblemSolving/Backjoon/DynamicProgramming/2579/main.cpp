// https://www.acmicpc.net/problem/2579

#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int n = 0, max = 0;
    
    std::cin >> n;
    
    std::vector<int> item(n);
    std::vector<int> val(n);
    
    for (auto j = 0; j < n; j++)
        std::cin >> item[j];
    
    val[0] = item[0];  val[1] = val[0] + item[1];

    for(auto i=2 ; i<n; i++)
        val[i] = std::max({val[i-2]+item[i],item[i]+item[i-1]+val[i-3]});

    std::cout << val.back() << std::endl;
}

