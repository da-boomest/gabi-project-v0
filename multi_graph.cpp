#include "multi_graph.h" 

template<typename TNodeInfo,typename TEdgeInfo>
int MultiGraph<TNodeInfo,TEdgeInfo>::no_of_nodes() const
{
	return 0;
}

template<typename TNodeInfo,typename TEdgeInfo>
int MultiGraph<TNodeInfo,TEdgeInfo>::no_of_edges() const
{
	return 0;
}

template<typename TNodeInfo,typename TEdgeInfo>
int MultiGraph<TNodeInfo,TEdgeInfo>::no_of_connections() const
{
	return 0;
}

template<typename TNodeInfo,typename TEdgeInfo>
bool MultiGraph<TNodeInfo,TEdgeInfo>::is_connection(int,int) const
{
	return 0;
}

template<typename TNodeInfo,typename TEdgeInfo>
const TNodeInfo& MultiGraph<TNodeInfo,TEdgeInfo>::get_node_info(int) const
{
	return NULL;
}

template<typename TNodeInfo,typename TEdgeInfo>
const TEdgeInfo& MultiGraph<TNodeInfo,TEdgeInfo>::get_edge_info(int) const
{
	return NULL;
}

template<typename TNodeInfo,typename TEdgeInfo>
const unordered_set<int>& MultiGraph<TNodeInfo,TEdgeInfo>::get_edges_between(int,int)
{
	return unordered_set<int>{};
}
                
template<typename TNodeInfo,typename TEdgeInfo>
int MultiGraph<TNodeInfo,TEdgeInfo>::get_connection_between(int,int) const
{
	return 0;
}

template<typename TNodeInfo,typename TEdgeInfo>
const unordered_set<int>& MultiGraph<TNodeInfo,TEdgeInfo>::get_edges_on_connection(int) const
{
	return unordered_set<int>{};
}

template<typename TNodeInfo,typename TEdgeInfo>
const unordered_map<int,int>& MultiGraph<TNodeInfo,TEdgeInfo>::get_outbound_connections(int) const
{
	return unordered_map<int,int>{};

}

template<typename TNodeInfo,typename TEdgeInfo>
const unordered_map<int,int>& MultiGraph<TNodeInfo,TEdgeInfo>::get_inbound_connections(int) const
{
	return unordered_map<int,int>{};

}

template<typename TNodeInfo,typename TEdgeInfo>
void MultiGraph<TNodeInfo,TEdgeInfo>::add_node(int,const TNodeInfo&)
{
}

template<typename TNodeInfo,typename TEdgeInfo>
void MultiGraph<TNodeInfo,TEdgeInfo>::add_edge(int,int,int,const TEdgeInfo&)
{
}

template<typename TNodeInfo,typename TEdgeInfo>
void MultiGraph<TNodeInfo,TEdgeInfo>::remove_node(int)
{
}

template<typename TNodeInfo,typename TEdgeInfo>
void MultiGraph<TNodeInfo,TEdgeInfo>::remove_edge(int)
{
}

template<typename TNodeInfo,typename TEdgeInfo>
void MultiGraph<TNodeInfo,TEdgeInfo>::clear_multi_graph()
{
}

