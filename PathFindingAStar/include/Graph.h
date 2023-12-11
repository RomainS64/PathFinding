#pragma once
#include <unordered_map>
#include <vector>
#include <SFML/System/Vector2.hpp>

struct Node {
    int id;
    sf::Vector2i position;
    
    Node(int nodeId,sf::Vector2i nodePosition):id(nodeId),position(nodePosition){};
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
    void removeEdge(Node* from, Node* to);
    void clearGraph();
    std::vector<Node*> getNeighbors(Node* node);
    double getEdgeCost(Node* from, Node* to);
    
private:
    std::unordered_map<int, Node*> nodes;
    std::unordered_map<int, std::unordered_map<int, double>> edges;
};