#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int n = 0;
    
    std::cin >> n;
    
    std::vector<int> val(n+1);
    
    for(auto i=1 ; i<n+1 ; i++){
        for(auto j=1 ; j*j<=i ; j++){
            if((val[i] > val[i-(j*j)] + 1) || (val[i] == 0)){
                val[i] = val[i-(j*j)] + 1;
            }
        }
    }

    std::cout << val[n] << std::endl;    
}

