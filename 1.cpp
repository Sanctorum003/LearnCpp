#include <iostream>
using namespace std;

class A
{
    private: 
       
    public:
        using ll = long long;
        ll a = 0;

        class B 
        {
            public:
                ll b;
        }

};

int main(void)
{
    A *a = new A();
    A::ll a;
    return 0;
}