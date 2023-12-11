#include "Graph.h"


void Graph::addNode(Node* node) {
	nodes[node->id] = node;
}

void Graph::addEdge(Node* from, Node* to, double cost) {
	edges[from->id][to->id] = cost;
}

void Graph::removeEdge(Node* from, Node* to)
{
	edges[from->id].erase(to->id);
}

void Graph::clearGraph()
{
	nodes.clear();
	edges.clear();
}

std::vector<Node*> Graph::getNeighbors(Node* node) {
	std::vector<Node*> neighbors;

	if (edges.find(node->id) != edges.end()) {
		for (const auto& neighbor : edges[node->id]) {
			neighbors.push_back(nodes[neighbor.first]);
		}
	}
	return neighbors;
}

double Graph::getEdgeCost(Node* from, Node* to) {
	if (edges.find(from->id) != edges.end() && edges[from->id].find(to->id) != edges[from->id].end()) {
		return edges[from->id][to->id];
	}
	return std::numeric_limits<double>::infinity();
}