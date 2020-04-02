#pragma once 
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::istream;
using std::ostream;


using std::unordered_map;
using std::unordered_set;
using std::vector;
using std::string;

class MultiGraphException
{
	private:
		string msg;
	public:
		MultiGraphException(const string& _msg):msg{_msg}{}
		friend ostream& operator<<(ostream& os,const MultiGraphException& mge);
		const string& get_msg() const;
};


const string& MultiGraphException::get_msg() const
{
	return this->msg;
}
ostream& operator<<(ostream& os,const MultiGraphException& mge)
{
	os<<mge.msg;
	return os;
}

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
				Node(int _node_id,const TNodeInfo& _info):node_id{_node_id},info{_info}{}
				
				Node(const Node& other):node_id{other.node_id},info{other.info}
				{
				}
				
				int get_node_id() const
				{
					return this->node_id;
				}
				void set_node_info(const TNodeInfo& _info)
				{
					this->info = _info;
				}
				const TNodeInfo& get_node_info() const
				{
					return this->info;
				} 
				~Node(){}
		};
		
		class Edge
		{
			private:
				int edge_id;
				int src_node;
				int dst_node;
				TEdgeInfo edge_info;
			public:
				Edge(){}

				Edge(int _edge_id,int _src_node,int _dst_node,const TEdgeInfo& _edge_info):
				edge_id{_edge_id},
				src_node{_src_node},
				dst_node{_dst_node},
				edge_info{_edge_info}
				{
				}

				Edge(const Edge& edge):
				edge_id{edge.edge_id},
				src_node{edge.src_node},
				dst_node{edge.dst_node},
				edge_info{edge.edge_info}
				{
				}
				
				int get_edge_id() const
				{
					return this->edge_id;
				}
				const int get_src_node() const
				{
					return this->src_node;
				}
				const int get_dst_node() const
				{
					return this->dst_node;
				}
				const TEdgeInfo& get_edge_info() const
				{
					return this->edge_info;
				}
				
				void  set_edge_info(const TEdgeInfo& _edge_info)
				{
					this->edge_info = _edge_info;
				}

				~Edge(){}
		};
		
		typedef struct
		{
			unordered_set<int> edges;
		}Connection;
		
		int base_id_connections;
		void add_edge_to_connection(int connection_id,int edge_id)
		{
			auto connection = this->connections.at(connection_id);
			connection.edges.insert(edge_id);
		}
	protected:
		
		unordered_map<int,Node> nodes;
		unordered_map<int,Edge> edges;
		unordered_map<int,Connection> connections;

		unordered_map<int,unordered_map<int,int>> outbound_connections;
		unordered_map<int,unordered_map<int,int>> inbound_connections;
	public:
		MultiGraph():base_id_connections{0}
		{
		
		cout<<"instatiating a multigraph ...\n";
		}
		MultiGraph(const MultiGraph&):base_id_connections{0}
		{
		cout<<"copying a multigraph ...\n";
		}

		~MultiGraph()
		{
		cout<<"destroying a multigraph ...\n";
		}
		
		int no_of_nodes() const
		{
			return this->nodes.size();
		}
		int no_of_edges() const
		{
			return this->edges.size();
		}
		int no_of_connections() const
		{
			return this->connections.size();
		}
		
		bool is_connection(int src_node,int dst_node) const
		{
			auto out_connections =this->outbound_connections.find(src_node);
			if (out_connections == this->outbound_connections.end())
				return false;
			auto it = (*out_connections).second.find(dst_node);
			return it != (*out_connections).second.end();
		}

		const TNodeInfo& get_node_info(int node_id) const
		{
			const Node& n=  this->nodes.at(node_id);

			return n.get_node_info();
		}

		const TEdgeInfo& get_edge_info(int edge_id) const
		{
			const Edge& e=  this->edges.at(edge_id);

			return e.get_edge_info();

		}

		const unordered_set<int>& get_edges_between(int src_node,int dst_node)
		{
			auto out_connections =this->outbound_connections.at(src_node);
			auto it = out_connections.find(dst_node);
			int connection_id = (*it).second;
			auto con_it = this->connections.find(connection_id);
			return (*con_it).second.edges;
		}
		int get_connection_between(int src_node,int dst_node) const
		{
			auto out_connections =this->outbound_connections.find(src_node);
			if (out_connections == this->outbound_connections.end())
				throw MultiGraphException{"no connections for source node!"};
			auto it = (*out_connections).second.find(dst_node);
			if ( it == (*out_connections).second.end())
				throw MultiGraphException{"no connections for destination node!"};
			return (*it).second;
	
		}
		const unordered_set<int>& get_edges_on_connection(int) const
		{
			return unordered_set<int>{};
		}
		const unordered_map<int,int>& get_outbound_connections(int) const
		{
			return unordered_map<int,int>{};
		}
		const unordered_map<int,int>& get_inbound_connections(int) const
		{
			return unordered_map<int,int>{};
		}
		void add_node(int node_id,const TNodeInfo& node_info)
		{
			auto it = this->nodes.find(node_id);
			if ( it != this->nodes.end())
				{
				throw MultiGraphException("existing node id!");
				}
			Node n{node_id,node_info};
			this->nodes.insert({node_id,n});
		}

		void add_edge(int edge_id,int src_node,int dst_node,const TEdgeInfo& edge_info)
		{
			auto it = this->edges.find(edge_id);
			cout<<"check if there is no other edge with same id ... \n";
			if ( it != this->edges.end())
				{
				throw MultiGraphException("existing edge id!");
				}
			cout<<"check if there is a valid source id ... \n";
			auto it_src = this->nodes.find(src_node);
			if ( it_src == this->nodes.end())
				{
				throw MultiGraphException("inexisting src node id!");
				}
			cout<<"check if there is a valid dest id ... \n";

			auto it_dst = this->nodes.find(dst_node);
			if ( it_dst == this->nodes.end())
				{
				throw MultiGraphException("inexisting dst node id!");
				}
			cout<<"create edge and insert it ... \n";

			Edge e{edge_id,src_node,dst_node,edge_info};
			this->edges.insert({edge_id,e});


			if (!this->is_connection(src_node,dst_node))
			{
				Connection c;
				this->connections.insert({this->base_id_connections,c});
			
				auto it_out_connections = this->outbound_connections.find(src_node);
				if (it_out_connections == this->outbound_connections.end())
				{
					unordered_map<int,int> out_connections;
					this->outbound_connections.insert({src_node,out_connections});
					it_out_connections = this->outbound_connections.find(src_node);
				}
			
				auto& out_cons = (*it_out_connections).second;
				auto it_dest_node = out_cons.find(dst_node);
				if (it_dest_node == out_cons.end())
				{
					out_cons.insert({dst_node,this->base_id_connections});
					it_dest_node = out_cons.find(dst_node);
				}
				this->base_id_connections++;	
			}

			int connection_id =  this->get_connection_between(src_node,dst_node);
			this->add_edge_to_connection(connection_id,edge_id);
		}

		void remove_node(int)
		{
		}

		void remove_edge(int)
		{
		}

		void clear_multi_graph()
		{
		}
};

