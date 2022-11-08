#include "iostream"
#include "vector"
#include "algorithm"

using graph_t = std::vector<std::vector<int>>;

void dfs(int currentNode, const graph_t &graph, std::vector<char> &visited, std::vector<int> &component) {
    visited[currentNode] = 1;
    component.push_back(currentNode);
    for (const int to: graph[currentNode]) {
        if (!visited[to]) {
            dfs(to, graph, visited, component);
        }
    }
}

int main() {
    int numNodes, numEdges;
    std::cin >> numNodes >> numEdges;
    graph_t graph(numNodes);
    for (int i = 0; i < numEdges; ++i) {
        int src, dst;
        std::cin >> src >> dst;
        --src;
        --dst;
        graph[src].push_back(dst);
        graph[dst].push_back(src);
    }
    std::vector<char> visited(numNodes, 0);
    for (int start = 0; start < numNodes; ++start) {
        if (visited[start])continue;
        std::vector<int> component;
        dfs(start, graph, visited, component);
        std::sort(component.begin(), component.end());
        for (int node: component) {
            std::cout << node + 1 << " ";
        }
        std::cout << "\n";
    }
    return 0;
}