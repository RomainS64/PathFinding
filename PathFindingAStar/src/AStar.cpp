#include "AStar.h"

AStar::AStar(Graph& graph) : graph(graph) {}

std::vector<Node*> AStar::findPath(Node* start, Node* goal) {
    std::priority_queue<std::pair<double, Node*>, std::vector<std::pair<double, Node*>>, std::greater<>> openSet;

    // Initialisation des valeurs
    cameFrom.clear();
    gScore.clear();
    fScore.clear();

    openSet.push({ 0.0, start });
    gScore[start] = 0.0;
    fScore[start] = heuristicCost(start, goal);

    while (!openSet.empty()) {
        Node* current = openSet.top().second;
        openSet.pop();

        if (current == goal) {
            // Reconstruct the path
            std::vector<Node*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = cameFrom[current];
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (Node* neighbor : graph.getNeighbors(current)) {
            double tentativeGScore = getGScore(current) + graph.getEdgeCost(current, neighbor);

            if (!gScore.count(neighbor) || tentativeGScore < getGScore(neighbor)) {
                cameFrom[neighbor] = current;
                setGScore(neighbor, tentativeGScore);
                fScore[neighbor] = getGScore(neighbor) + heuristicCost(neighbor, goal);
                openSet.push({ fScore[neighbor], neighbor });
            }
        }
    }

    // No path found
    return std::vector<Node*>();
}

double AStar::heuristicCost(Node* a, Node* b) {
    //distance euclidienne 
    double dx = a->position.x - b->position.x;
    double dy = a->position.y - b->position.y;
    return std::sqrt(dx * dx + dy * dy);
}

double AStar::getGScore(Node* node) {
    return gScore.count(node) ? gScore[node] : std::numeric_limits<double>::infinity();
}

void AStar::setGScore(Node* node, double value) {
    gScore[node] = value;
}