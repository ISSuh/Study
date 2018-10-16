#include <iostream>

template <typename T> T Max(T a, T b){
    return a > b ? a : b;
}

int main(){
    int Char1_HP = 300;
    int Char2_HP = 400;

    int MaxCharHP = Max(Char1_HP,Char2_HP);   

    std::cout << "HP 중 가장 큰 값은" << MaxCharHP << "입니다.\n" << std::endl;

    float Char1_Exp = 250.0f;
    float Char2_Exp = 250.57f;

    auto MaxCharExp = Max(Char1_Exp,Char2_Exp);
    std::cout << "HP 중 가장 큰 값은" << MaxCharExp << "입니다.\n" << std::endl;
}