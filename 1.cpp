#include <iostream>
using namespace std;


// 线程安全的单例模式

class A
{
public:
	void print()
	{
		cout << 2 << endl;
	}
};

class Singleton
{
private:
	Singleton() { }
	~Singleton() { }
	Singleton(const Singleton &);
	Singleton & operator = (const Singleton &);

public:
	static Singleton& GetInstance()
	{
		static Singleton instance;
		static A a;
		a.print();
		// cout << &instance << endl;
		instance.print();
		return instance;
	}

	void print()
	{
		// b.print();
		cout << 2 << endl;
	}
};

int main(void)
{
	Singleton::GetInstance();//.print();
	
	// system("pasue");
	return 0;
}