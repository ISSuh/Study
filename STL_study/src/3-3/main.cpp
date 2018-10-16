#include <iostream>
using namespace std;
// 경험치를 저장할 수 있는 최대 개수
const int MAX_EXP_COUNT = 100;
// 경험치 저장 스택 클래스
template<typename T>
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
                if (m_Count >= MAX_EXP_COUNT)
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
                        return 0.0f;
                }
                // 개수를 하나 감소 후 반환한다.
                --m_Count;
                return m_aData[m_Count];
        }

      private:
        T  m_aData[MAX_EXP_COUNT];
        int m_Count;
};

int main()
{
        Stack<double> kExpStack;
        cout << "첫번째 게임 종료- 현재 경험치 145.5f" << endl;
        kExpStack.push(145.5f);
        cout << "두번째 게임 종료- 현재 경험치 183.25f" << endl;
        kExpStack.push(183.25f);
        cout << "세번째 게임 종료- 현재 경험치162.3f" << endl;
        kExpStack.push(162.3f);
        int Count = kExpStack.Count();
        for (int i = 0; i < Count; ++i)
        {
                cout << "현재 경험치->" << kExpStack.pop() << endl;
        }

        cout << endl;

        Stack<uint64_t> kStackMoney;
        cout << "첫번째 게임 종료- 현재 돈 1000023" << endl;
        kStackMoney.push(1000023);
        cout << "두번째 게임 종료- 현재 돈 1000234" << endl;
        kStackMoney.push(1000234);
        cout << "세번째 게임 종료- 현재 돈 1000145" << endl;
        kStackMoney.push(1000145);
        Count = kStackMoney.Count();
        for (int i = 0; i < Count; ++i)
        {
                cout << "현재 돈->" << kStackMoney.pop() << endl;
        }
}