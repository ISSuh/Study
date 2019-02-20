nclude <iostream>
#include <algorithm>
#include <vector>

int func_1(int n){
    if(n % 3 == 0)
        return (int)n/3;
    else
        return 0;    
}

int func_2(int n){
    if(n % 2 == 0)
        return n >> 1;
    else
        return 0;    
}

int func_3(int n){
    return n-1;    
}

int main(){
    int n = 0;

    std::cin >> n;

    if(n > 3){
        int index = 4;
        std::vector<int> result(n+1);

        result[0] = 99999;
        result[1] = 1;
        result[2] = 1;
        result[3] = 1;

        for(auto i=result.begin() + 4 ; i != result.end(); i++){
            std::vector<int> val(3);

            val[0] = 1 + result[func_1(index)];
            val[1] = 1 + result[func_2(index)];
            val[2] = 1 + result[func_3(index)];

            *i = (*std::min_element(val.begin(), val.end()));
            index++;
        }   

        std::cout << result.back() << "\n";
    }
    else{
        switch (n) {
            case 1 :
                std::cout << 0 << "\n";
                break;
            case 2 :
                std::cout << 1 << "\n";
                break;
            case 3 :
                std::cout << 1 << "\n";
                break;
        }
    }
    return 0;
}

