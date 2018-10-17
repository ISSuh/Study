#include <iostream>

using namespace std;

template <typename T>
class MySingleton
{
      public:
        MySingleton() {}
        ~MySingleton() {}

        static T *GetSington()
        {
                if (NULL == _Singleton)
                        _Singleton = new T;
                return _Singleton;
        }
        static void Release()
        {
                delete _Singleton;
                _Singleton = NULL;
        }

      private:
        static T *_Singleton;
};

template <typename T> 
T *MySingleton<T>::_Singleton = NULL;
class MyObject : public MySingleton<MyObject>
{
      public:
        MyObject() : _nValue(10) {}

        void SetValue(int value) { _nValue = value; }
        int GetValue() { return _nValue; }

      private:
        int _nValue;
};

int main()
{
        MyObject *obj1 = MyObject::GetSington();
        cout << obj1->GetValue() << endl;

        MyObject *obj2 = MyObject::GetSington();
        obj2->SetValue(20);

        cout << obj1->GetValue() << endl;
        cout << obj2->GetValue() << endl;
}