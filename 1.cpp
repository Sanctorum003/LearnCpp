#include <iostream>
using namespace std;

class A
{
public:
	A(int _a = 0):a(_a){}

	int getA()const
	{
		A* b = new A();
		a = 2;
		return a;
	}

	int a;
};

int main()
{
	A a;
	return 0;
}