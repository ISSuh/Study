#include <iostream>
#include <vector>

double getMinimum(std::vector<int> &days, int &L){
    std::vector<std::vector<int>> daysSum(days.size(),std::vector<int>(days.size()));
    double result = 0;
    double min = 999999, temp = 0;
    double sum = 0;

    for(auto i = days.begin() ; i != days.end() ; i++){
        
    }

    result = min;

    return result;
}

int main(){
    int T = 0;
    std::cin >> T;

    while(T--){
        int N = 0, L = 0;
        std::cin >> N >> L;

        std::vector<int> days(N);

        for(auto i = 0 ; i < N ; i++)
            std::cin >> days[i];
            
        printf("%.12f\n",getMinimum(days, L));
    }
}