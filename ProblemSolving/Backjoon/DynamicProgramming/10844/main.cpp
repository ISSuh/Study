#include <iostream>
#include <vector>

int main(){
    int N = 0;
    long long sum = 0;
    
    std::cin >> N;

    std::vector<std::vector<int>> item(N, std::vector<int>(10));

    for(auto i = 1 ; i < 10 ; i++)
        item[0][i] = 1;

    for(auto i = 1 ; i < item.size() ; i++){
        for(auto j = 0 ; j < 10 ; j++){
            if(j == 0)
                item[i][j] = item[i-1][j+1] % 1000000000;
            else if(j == 9)
                item[i][j] = item[i-1][j-1] % 1000000000;
            else
                item[i][j] = (item[i-1][j-1] + item[i-1][j+1]) % 1000000000;
        }
    }

    for(auto i = 0 ; i < 10 ; i++)
        sum += item[N-1][i] % 1000000000;
    
    std::cout << sum % 1000000000<< std::endl;

    return 0;
}
