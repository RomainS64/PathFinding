#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>
#include "Graph.h"


class AStar {
public:
    AStar(Graph graph);
    std::vector<Node*> findPath(Node* start, Node* goal);

private:
    Graph graph;
    std::unordered_map<Node*, Node*> cameFrom;
    std::unordered_map<Node*, double> gScore;
    std::unordered_map<Node*, double> fScore;

    double heuristicCost(Node* a, Node* b);
    double getGScore(Node* node);
    void setGScore(Node* node, double value);
};