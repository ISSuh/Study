#include <iostream>
#include <vector>

int main(){
    int N = 0;
    long long sum = 0;
    
    std::cin >> N;

    std::vector<std::vector<int>> item(N,std::vector<int>(10));
    
    for(auto i=0 ; i<10 ; i++)
        item[0][i] = 1;
    

    for(auto i=1 ; i<N ; i++){
        for(auto j=0 ; j<10 ; j++){
            for(auto k=0 ; k<=j ; k++)
                item[i][j] += (item[i-1][k]) % 10007;
        }
    }


    for(auto i=0 ; i<10 ; i++)
        sum += item[N-1][i];
    
    std::cout << sum % 10007 << std::endl;

    return 0;
}
