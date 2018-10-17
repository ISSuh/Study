#include <iostream>

using namespace std;

template< typename T1, typename T2 >
class Test{
public:
        T1 Add(T1 a, T2 b){
                cout << "일반 템플릿 사용 \n";
                return a;
        }
};

template< typename T1>
class Test<T1,float>{
public:
        T1 Add(T1 a, float b){
                cout << "부분 전문화 템플릿 사용 \n";
                return a;
        }
};

int main(){
        Test<int, int> test1;
        test1.Add(2,3);

        Test<int,float> test2;
        test2.Add(2, 5.8f);
}