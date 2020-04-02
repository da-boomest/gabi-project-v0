#include "multi_graph.h"
#include <iostream>
#include <cassert>
#include <sstream>  


using std:: cin;
using std::cout;
using std::stringstream;

void test_multi_graph()
{
cout<<"starting testing multi graph ...\n";
MultiGraph<int,int> mg;
MultiGraph<int,int> cmg{mg};
MultiGraph<int,int> ccmg = mg;
MultiGraph<int,int> *dmg = new MultiGraph<int,int>();
delete dmg;

assert(mg.no_of_nodes()==0);
assert(mg.no_of_edges()==0);
assert(mg.no_of_connections()==0);
mg.add_node(0,23);
assert(mg.no_of_nodes()==1);
try
{
mg.add_node(0,23);
}
catch(const MultiGraphException& exc)
{
	assert(exc.get_msg()=="existing node id!");
}
assert(mg.no_of_nodes()==1);
int info = mg.get_node_info(0);
cout<<info<<"\n";
assert(info==23);

mg.add_node(1,30);
assert(mg.no_of_nodes()==2);
try{
mg.add_edge(0,0,1,45);
}catch(MultiGraphException ex)
{
	cout<<ex.get_msg()<<"\n";
}
assert(mg.no_of_edges()==1);






cout<<"finishing testing multi graph ...\n";
}

int main()
{
	test_multi_graph();
	return 0;
}
