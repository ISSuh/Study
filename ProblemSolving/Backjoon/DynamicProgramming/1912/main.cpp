#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int n = 0;
    
    std::cin >> n;
    
    std::vector<int> item(n);
    std::vector<int> val(n);
    
    for (auto i=0 ; i<n ; i++)
        std::cin >> item[i];
    
    val[0] = item[0];

    for(auto i=1 ; i<n ; i++)
        val[i] = std::max(item[i] + val[i-1], item[i]);

    std::cout << *std::max_element(val.begin(), val.end()) << std::endl;
}

