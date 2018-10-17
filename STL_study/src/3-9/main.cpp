#include <iostream>

using namespace std;

template< typename T >
class TestP{
public:
        void Add(){
                cout << "일반 템플릿 사용\n";
        }

};

template< typename T >
class TestP<T*>{
public:
        void Add(){
                cout << "포인터를 사용한 부분 전문화 템플릿 사용\n";
        }
};

int main(){
        TestP<int> test1;
        test1.Add();

        TestP<int*> test2;
        test2.Add();
}