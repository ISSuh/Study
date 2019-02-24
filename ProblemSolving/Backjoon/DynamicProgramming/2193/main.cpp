#include <iostream>
#include <vector>

int main(){
    int n = 0;

    std::cin >> n;
    std::vector<long long> item(n);

    item[0] = 1;
    item[1] = 1;

    for(auto i = 2 ; i < item.size() ; i++)
        item[i] = item[i-1] +item[i-2];

    std::cout << item.back() << std::endl;

    return 0;
}

