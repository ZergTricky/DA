//
// Created by egorb on 18.09.2022.
//

#ifndef LAB5_TYPES_H
#define LAB5_TYPES_H

#include "string"
#include "map"
#include "climits"
#include "iostream"
#include "assert.h"

class Edge;

class Node;

class Edge {
public:
    Edge() : destination(nullptr), positionStart(0), length(0) {}

    Edge(Node *dest, std::size_t start, std::size_t length) : destination(dest), positionStart(start),
                                                              length(length) {}

    Node *GetDestination() const noexcept {
        return destination;
    }

    const char GetChar(const std::string &str, std::size_t index) const {
        return str[positionStart + index];
    }

    const std::size_t GetLength() const noexcept {
        return length;
    }

    const std::size_t GetStart() const noexcept {
        return positionStart;
    }

    ~Edge() = default;

private:
    Node *destination;
    std::size_t positionStart;
    std::size_t length;
};

class Node {
public:
    Node() : suffixLink(nullptr), neighbors() {}

    Node(Node *link) : suffixLink(link), neighbors() {}

    bool CanGo(const char where) const noexcept {
        return neighbors.count(where) != 0;
    }

    Node *Go(const char where) {
        return neighbors[where].GetDestination();
    }

    void SetLink(Node *link) noexcept {
        suffixLink = link;
    }

    void AddEdge(const char letter, Node *otherNode, std::size_t start, std::size_t length) {
        neighbors.emplace(letter, Edge(otherNode, start, length));
    }

    void DeleteEdge(const char letter) {
        neighbors.erase(letter);
    }

    ~Node() = default;

    std::map<char, Edge> neighbors;
    Node *suffixLink;
};


#endif //LAB5_TYPES_H
