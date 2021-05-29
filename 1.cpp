#include <iostream>
#include <memory>
#include <vector>
#include <deque>
#include <list>
using namespace std;

template<class T, class Sequence=deque<T> >
class stack1 {
public:
    Sequence c; // 底层容器
};


int main()
{
	stack1<int> s1;
	stack1<int,deque<string>> s2;
	s2.c.push_back("a");
	s2.c.push_back(1);
	return 0;
}