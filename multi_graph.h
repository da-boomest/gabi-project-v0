#pragma once 
#include <unordered_map>
#include <unordered_set>
#include <iostream>
using std::cin;
using std::cout;



using std::unordered_map;
using std::unordered_set;

template<typename TNodeInfo,typename TEdgeInfo>
class MultiGraph
{
	private:
		class Node
		{
			private:
				int node_id;
				TNodeInfo info;
			public:
				Node(){}
				Node(const Node&){}
				
				int get_node_id() const;
				void set_node_info(const TNodeInfo&);
				const TNodeInfo& get_node_info() const; 
				~Node(){}
		};
		
		class Edge
		{
			private:
				int edge_id;
				Node& src_node;
				Node& dst_node;
				TEdgeInfo edge_info;
			public:
				Edge(){}
				Edge(const Edge&){}
				
				int get_dege_id() const;
				const Node& get_src_node() const;
				const Node& get_dst_node() const;
				const TEdgeInfo& get_edge_info() const;
				
				void  set_edge_info(const TEdgeInfo&);

				~Edge(){}
		};
		
		typedef struct
		{
			unordered_set<int> edges;
		}Connection;

	protected:
		
		unordered_map<int,Node> nodes;
		unordered_map<int,Edge> edges;
		unordered_map<int,Connection> connections;

		unordered_map<int,unordered_map<int,int>> outbound_connections;
		unordered_map<int,unordered_map<int,int>> inbound_connections;
	public:
		MultiGraph()
		{
		cout<<"instatiating a multigraph ...\n";
		}
		MultiGraph(const MultiGraph&)
		{
		cout<<"copying a multigraph ...\n";
		}

		~MultiGraph()
		{
		cout<<"destroying a multigraph ...\n";
		}
		
		int no_of_nodes() const;
		int no_of_edges() const;
		int no_of_connections() const;
		
		bool is_connection(int,int) const;
		const TNodeInfo& get_node_info(int) const;
		const TEdgeInfo& get_edge_info(int) const;
		const unordered_set<int>& get_edges_between(int,int);
		int get_connection_between(int,int) const;
		const unordered_set<int>& get_edges_on_connection(int) const;
		const unordered_map<int,int>& get_outbound_connections(int) const;
		const unordered_map<int,int>& get_inbound_connections(int) const;

		void add_node(int,const TNodeInfo&);
		void add_edge(int,int,int,const TEdgeInfo&);
		
		void remove_node(int);
		void remove_edge(int);
		void clear_multi_graph();
};
