#include <iostream>
using namespace std;

int main()
{
    int i = 0;
    const int ci = i;

    auto k = ci,&l = i;
    auto &m = ci,*p = &ci;
    auto *p2=& ci;

    return 0;
}
