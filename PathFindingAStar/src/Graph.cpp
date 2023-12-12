#include "Graph.h"


void Graph::AddNode(Node* node) {
	_nodes[node->id] = node;
}

void Graph::AddEdge(Node* from, Node* to, double cost) {
	_edges[from->id][to->id] = cost;
}

void Graph::RemoveEdge(Node* from, Node* to)
{
	_edges[from->id].erase(to->id);
}

void Graph::ClearGraph()
{
	_nodes.clear();
	_edges.clear();
}
Graph::~Graph()
{
	for (auto node : _nodes)
	{
		delete node.second;
	}
}


std::vector<Node*> Graph::GetNeighbors(Node* node) {
	std::vector<Node*> neighbors;

	if (_edges.find(node->id) != _edges.end()) {
		for (const auto& neighbor : _edges[node->id]) {
			neighbors.push_back(_nodes[neighbor.first]);
		}
	}
	return neighbors;
}

double Graph::GetEdgeCost(Node* from, Node* to) {
	if (_edges.find(from->id) != _edges.end() && _edges[from->id].find(to->id) != _edges[from->id].end()) {
		return _edges[from->id][to->id];
	}
	return std::numeric_limits<double>::infinity();
}