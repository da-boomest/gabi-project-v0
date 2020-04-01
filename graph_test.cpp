#include "multi_graph.h"
#include <iostream>
using std:: cin;
using std::cout;


void test_multi_graph()
{
cout<<"starting testing multi graph ...\n";
MultiGraph<int,int> mg;
MultiGraph<int,int> cmg{mg};
MultiGraph<int,int> ccmg = mg;
MultiGraph<int,int> *dmg = new MultiGraph<int,int>();
delete dmg;
cout<<"finishing testing multi graph ...\n";
}

int main()
{
	test_multi_graph();
	return 0;
}
