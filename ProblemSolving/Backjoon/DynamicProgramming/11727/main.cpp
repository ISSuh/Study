#include <iostream>
#include <vector>

int main(){
    int n = 0;

    std::cin >> n;
    
    if(n){
        std::vector<int> item(n);
        item[0] = 1;    item[1] = 3;

        for(auto i = 2 ;  i < item.size() ; i++)
            item[i] = (item[i-1] + (item[i-2] * 2)) % 10007;

        std::cout << item.back() << std::endl;
    }
    else
        std::cout << 0 << std::endl;

    return 0;
}
