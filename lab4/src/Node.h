#ifndef NODE_H
#define NODE_H

#include "map"
#include "vector"

template<typename Alphabet>
class Node {
public:
    std::map<Alphabet, Node *> go;
    Node *suffixLink;
    Node *terminalLink;

    bool isTerminal;

    std::vector<int> positions;

    Node() : suffixLink{nullptr}, terminalLink{nullptr}, isTerminal{false} {}

    Node(bool isTerminal) : suffixLink{nullptr}, terminalLink{nullptr}, isTerminal{isTerminal} {}

    bool CanGo(const Alphabet &where) {
        return go.count(where) > 0;
    }

    ~Node() = default;
};

#endif //NODE_H