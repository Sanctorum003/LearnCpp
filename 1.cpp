#include <iostream>
using namespace std;

int main()
{
    int a[] = {1,2,3,4,5,};
    int *p = &a[2];
    cout<<p[1]<<" "<<p[-1]<<endl;

    return 0;
}
