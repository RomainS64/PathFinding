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
    virtual ~Graph();
    virtual void ClearGraph();
    void AddNode(Node* node);
    void AddEdge(Node* from, Node* to, double cost = 1.0);
    void RemoveEdge(Node* from, Node* to);
    std::vector<Node*> GetNeighbors(Node* node);
    double GetEdgeCost(Node* from, Node* to);
    
private:
    std::unordered_map<int, Node*> _nodes;
    std::unordered_map<int, std::unordered_map<int, double>> _edges;
};