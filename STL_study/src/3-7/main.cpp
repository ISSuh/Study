#include <iostream>
#include <string.h>

using namespace std;

const int MAX_ID_LENGTH = 21;

// 경험치 저장 스택 클래스
template <typename T>
class Stack
{
      public:
        explicit Stack(int size)
        {
                m_Size = size;
                m_aData = new T[m_Size];
                Clear();
        }

        ~Stack()
        {
                delete[] m_aData;
        }
        // 초기화 한다.
        void Clear()
        {
                m_Count = 0;
        }
        //데이터를 담을수 있는 최대 개수
        int GetStackSize()
        {
                return m_Size;
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
                if (m_Count >= m_Size)
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
        T *m_aData;
        int m_Count;
        int m_Size;
};

template <>
class Stack<char *>
{
      public:
        explicit Stack(int size)
        {
                m_Size = size;
                m_ppData = new char *[m_Size];
                for (int i = 0; i < m_Size; i++)
                {
                        m_ppData[i] = new char[MAX_ID_LENGTH];
                }
                Clear();
        }
        ~Stack()
        {
                for (int i = 0; i < m_Size; i++)
                {
                        delete[] m_ppData[i];
                }

                delete[] m_ppData;
        }
        void Clear()
        {
                m_Count = 0;
        }
        int Count()
        {
                return m_Count;
        }
        bool IsEmpty()
        {
                return 0 == m_Count ? true : false;
        }
        int GetStackSize()
        {
                return m_Size;
        }
        bool push(char *pID)
        {
                // 저장할 수 있는 개수를 넘는지 조사한다.
                if (m_Count >= m_Size)
                {
                        return false;
                }
                // 저장 후 개수를 하나 늘릮다.
                strcpy(m_ppData[m_Count], pID);
                m_ppData[m_Count][MAX_ID_LENGTH - 1] = '\0';
                ++m_Count;
                return true;
        }
        // 스택에서 빼낸다.
        char *pop()
        {
                // 저장된 것이 없다면 0을 반환한다.
                if (m_Count < 1)
                {
                        return 0;
                }
                // 개수를 하나 감소 후 반환한다.        
                --m_Count;
                return m_ppData[m_Count];
        }

      private:
        char **m_ppData;
        int m_Count;
        int m_Size;
};

int main()
{
        Stack<int> kStack1(64);
        cout << "스택의 크기는? " << kStack1.GetStackSize() << endl;
        kStack1.push(10);
        kStack1.push(11);
        kStack1.push(12);
        int Count1 = kStack1.Count();
        for (int i = 0; i < Count1; ++i)
        {
                cout << "유저의 레벨 변화 -> " << kStack1.pop() << endl;
        }
        cout << endl;
        char GameID1[MAX_ID_LENGTH] = "NiceChoi";
        char GameID2[MAX_ID_LENGTH] = "SuperMan";
        char GameID3[MAX_ID_LENGTH] = "Attom";
        // Stack 클래스 템플릿의 char* 전문화 버전을 생성한다.
        Stack<char *> kStack2(64);
        kStack2.push(GameID1);
        kStack2.push(GameID2);
        kStack2.push(GameID3);
        int Count2 = kStack2.Count();
        for (int i = 0; i < Count2; ++i)
        {
                cout << "같이 게임을 한유저의 ID -> " << kStack2.pop() << endl;
        }
}