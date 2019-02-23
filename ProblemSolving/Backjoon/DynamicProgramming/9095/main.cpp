#include <iostream>
#include <vector>

int main(){
    int T = 0;
    
    std::cin >> T;
    
    std::vector<int> N(T,0);
    
    for(auto t = 0 ; t < T ; t++)
        std::cin >> N[t];    
    
    for(auto n = N.begin() ; n != N.end() ; n ++){
        if(*n > 3){
            std::vector<int> item(*n);

            item[0] = 1; item[1] = 2; item[2] = 4;
            for(auto i = 3 ; i < *n ; i++)
                item[i] = item[i-1] + item[i-2] + item[i-3];


            std::cout << item.back() << std::endl;
        }
        else{
            switch (*n){
                case 1 :
                    std::cout << 1 << std::endl;
                    break;
                case 2 :
                    std::cout << 2 << std::endl;
                    break;
                case 3 :
                    std::cout << 4 << std::endl;
                    break;
            }
        }
    }    

    return 0;
}
