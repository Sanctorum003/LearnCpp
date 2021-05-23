#include <iostream>
using namespace std;

class A
{
public:
	A(int _a = 0):a(_a){}

	static void setA()
	{
		a = 1;
	}

	int a;
};

int main()
{
	A a;
	return 0;
}