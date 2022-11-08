#include "iostream"
#include "vector"
#include "algorithm"
#include "queue"

using graph_t = std::vector<std::vector<int>>;

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
        std::queue<int> q;
        std::vector<int> component;
        q.push(start);
        visited[start] = 1;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int to: graph[node]) {
                if (!visited[to]) {
                    visited[to] = 1;
                    q.push(to);
                }
            }
        }

        std::sort(component.begin(), component.end());
        for (int node: component) {
            std::cout << node + 1 << " ";
        }
        std::cout << "\n";
    }
    return 0;
}