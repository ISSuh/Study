#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int n = 0, min = 99999999;
    
    std::cin >> n;
    
    std::vector<int> val(n+1);

    val[1] = 1;
    for(auto i=1 ; i<n+1 ; i++){
        std::vector<int> minVal;
        
        for(auto j=1 ; j*j<=i ; j++)
            if(min > val[i-(j*j)] + 1)
                minVal.push_back(val[i-(j*j)] + 1);

        val[i] = *std::min_element(minVal.begin(),minVal.end());
    }

    std::cout << val[n] << std::endl;    
}

