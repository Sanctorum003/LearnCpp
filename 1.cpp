#include <iostream>
using namespace std;

int main()
{
    const int a = 1;
    int c = 2;
    const int *const b = &a;
    *b = 1;
    b = &c;
    cout<<*b<<endl;
    return 0;
}
