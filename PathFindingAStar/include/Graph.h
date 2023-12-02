#pragma once
#include <unordered_map>
#include <vector>
#include <SFML/System/Vector2.hpp>

class Node {
public:
    int id;  // Un identifiant unique pour chaque n�ud
    Node(int nodeId):id(nodeId){};
};

class Graph {
public:
    Graph() = default;
    virtual ~Graph()
    {
        for (auto node : nodes)delete node.second;
    };
    void addNode(Node* node);
    void addEdge(Node* from, Node* to, double cost = 1.0);
    std::vector<Node*> getNeighbors(Node* node);
    double getEdgeCost(Node* from, Node* to);
    
private:
    std::unordered_map<int, Node*> nodes;
    std::unordered_map<int, std::unordered_map<int, double>> edges;
};