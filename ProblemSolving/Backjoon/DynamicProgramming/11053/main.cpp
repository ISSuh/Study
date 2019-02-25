nclude <iostream>
#include <vector>
#include <algorithm>

int main(){
    int n = 0;
    
    std::cin >> n;
    
    std::vector<int> item(n);
    std::vector<int> val(n);
    
    for (auto i=0; i<n; i++)
        std::cin >> item[i];
    
    val[0] = 1;

    for(auto i=1 ; i<n; i++){
        int maxValueIndex = 0, maxValue = 0;

        for(auto j=0 ; j<i ; j++){
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

    std::cout << *std::max_element(val.begin(),val.end()) << std::endl;

}

