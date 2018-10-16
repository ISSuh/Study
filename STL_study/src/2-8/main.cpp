#include <iostream>

template <typename T1, typename T2> T2 Max(const T1 &a,const T2 &b){
    std::cout << "Max(const T& a, const T& b) 템플릿 버전 사용 \n"; 
    return a > b ? a : b;
}

template <> double Max(const double& a, const double& b){
    std::cout << "Max(const T& a, const T& b) 전문화 버전 사용 \n"; 
    return a > b ? a : b;
}

int main(){
    double Char1_MP = 300;
    double Char1_SP = 400.25;
    double MaxValue1 = Max(Char1_MP, Char1_SP);
    std::cout << "MP와 SP 중 가장 큰 값은" << MaxValue1 << "입니다." << std::endl
         << std::endl;
         
    int Char2_MP = 300;
    double Char2_SP = 400.25;
    double MaxValue2 = Max(Char2_MP, Char2_SP);
    std::cout << "MP와 SP 중 가장 큰 값은" << MaxValue2 << "입니다." << std::endl
         << std::endl;
}