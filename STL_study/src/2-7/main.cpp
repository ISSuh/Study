#include <iostream>

template <typename T1, typename T2> const T1& Max(const T1 &a,const T2 &b){
    return a > b ? a : b;
}

int main(){
    int Char1_MP = 300;
    double Char1_SP = 400.25;
    double MaxValue1 = Max(Char1_MP, Char1_SP);
    std::cout << "MP와 SP 중 가장 큰값은" << MaxValue1 << "입니다." << std::endl
         << std::endl;
    double MaxValue2 = Max(Char1_SP, Char1_MP);
    std::cout << "MP와 SP 중 가장 큰값은" << MaxValue2 << "입니다." << std::endl
         << std::endl;
}