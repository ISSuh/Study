#include <iostream>

using namespace std;

template <typename T, int VAL> T AddValue(T const& CurValue){
    return CurValue + VAL;
}

const int EVENT_ADD_HP_VALUE = 50;
// 이벤트에 의해 추가 될 HP 값
const int EVENT_ADD_EXP_VALUE = 30;
// 이벤트에 의해 추가 될 경험치
const int EVENT_ADD_MONEY_VALUE = 10000;
// 이벤트에 의해 추가 될 돈

int main()
{
    int Char_HP = 250;
    cout << Char_HP << "에서 이벤트에 의해" << 
            AddValue<int, EVENT_ADD_HP_VALUE>(Char_HP) << " 로 변경" << endl;

    float Char_EXP = 378.89f;
    cout << Char_EXP << "에서 이벤트에 의해" << 
            AddValue<float, EVENT_ADD_EXP_VALUE>(Char_EXP) << " 로 변경" << endl;

    uint64_t Char_MONEY = 34567890;
    cout << Char_MONEY << "에서 이벤트에 의해" << 
            AddValue<uint64_t, EVENT_ADD_MONEY_VALUE>(Char_MONEY) << " 로 변경" << endl;
}