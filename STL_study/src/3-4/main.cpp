#include <iostream>
using namespace std;

// 경험치 저장 스택 클래스
template<typename T, int Size>
class Stack
{
      public:
        Stack()
        {
                Clear();
        }
        // 초기화 한다.
        void Clear()
        {
                m_Count = 0;
        }
        //데이터를 담을수 있는 최대 개수
        int GetStackSize(){
                return Size;
        }
        // 스택에 저장된 개수
        int Count()
        {
                return m_Count;
        }
        // 저장된 데이터가 없는가?
        bool IsEmpty()
        {
                return 0 == m_Count ? true : false;
        }
        // 경험치를 저장한다.
        bool push(T data)
        {
                // 저장할 수 있는 개수를 넘는지 조사한다.
                if (m_Count >= Size)
                {
                        return false;
                }
                // 경험치를 저장 후 개수를 하나 늘릮다.
                m_aData[m_Count] = data;
                ++m_Count;
                return true;
        }
        // 스택에서 경험치를 빼낸다.
        T pop()
        {
                // 저장된 것이 없다면 0.0f를 반환한다.
                if (m_Count < 1)
                {
                        return 0;
                }
                // 개수를 하나 감소 후 반환한다.
                --m_Count;
                return m_aData[m_Count];
        }

      private:
        T  m_aData[Size];
        int m_Count;
};

int main()
{
        Stack<int, 100> kStack1;
        cout << "Stack Size : " << kStack1.GetStackSize() << endl;

        Stack<int, 30> kStack2;
        cout << "Stack Size : " << kStack2.GetStackSize() << endl;
}