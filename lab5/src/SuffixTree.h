//
// Created by egorb on 18.09.2022.
//

#ifndef LAB5_SUFFIXTREE_H
#define LAB5_SUFFIXTREE_H

#include "Types.h"
#include "iostream"

std::size_t Infinity = ULLONG_MAX;

class SuffixTree {
public:
    SuffixTree(const std::string &str) : root(new Node()), _str(str), numberOfNodes(1) {
        root->suffixLink = root;
        int currentPosition = 0;

        Node *currentNode = root;
        std::size_t shift = 0;
        char where = 0;
        for (auto c: str) {
            Node *last = nullptr;
            while (1) {
                if (shift == 0) {
                    if (last != nullptr) {
                        last->suffixLink = currentNode;
                    }
                    // we are on node
                    if (currentNode->CanGo(c)) {
                        // if we can go by new letter
                        if (currentNode->neighbors[c].GetLength() == 1) {
                            // it's one size edge
                            // don't change shift but change current node
                            currentNode = currentNode->Go(c);
                        } else {
                            // edge size is at least two, don't change node, remember the letter and shift
                            where = c;
                            shift = 1;

                            // finish for current letter
                        }
                        break;
                    } else {
                        // we don't have an edge for letter c, create leaf
                        currentNode->AddEdge(c, new Node(), currentPosition, Infinity);
                        numberOfNodes++;
                        if (currentNode == root) {
                            // just finish
                            shift = 0;
                            break;
                        } else {
                            // otherwise
                            assert(currentNode->suffixLink != nullptr);
                            // move to suffixLink
                            last = currentNode;
                            currentNode = currentNode->suffixLink;
                        }
                    }
                } else {
                    char nextChar = currentNode->neighbors[where].GetChar(_str, shift);

                    if (nextChar == c) {
                        // just move forward and finish
                        ++shift;
                        if (shift == currentNode->neighbors[where].GetLength()) {
                            currentNode = currentNode->neighbors[where].GetDestination();
                            shift = 0;
                        }

                        break;
                    } else {
                        // we have to split current edge
                        assert(currentNode->neighbors[where].GetLength() > shift);

                        Node *split = new Node();
                        numberOfNodes++;
                        if (last != nullptr) {
                            last->suffixLink = split;
                        }

                        char t = currentNode->neighbors[where].GetChar(_str, shift);
                        std::size_t st = currentNode->neighbors[where].GetStart();
                        std::size_t length = currentNode->neighbors[where].GetLength();

                        split->AddEdge(t, currentNode->neighbors[where].GetDestination(), st + shift, length - shift);
                        split->AddEdge(c, new Node(), currentPosition, Infinity);
                        ++numberOfNodes;

                        currentNode->DeleteEdge(where);
                        currentNode->AddEdge(where, split, st, shift);

                        last = split;

                        // find next node
                        if (currentNode == root) {
                            std::size_t needLength = shift - 1;

                            if (needLength == 0) {
                                shift = 0;
                                currentNode = root;
                                continue;
                            }

                            char q = currentNode->neighbors[where].GetChar(_str, 1);
                            while (needLength > 0) {
                                if (currentNode->neighbors[q].GetLength() <= needLength) {
                                    needLength -= currentNode->neighbors[q].GetLength();
                                    currentNode = currentNode->Go(q);
                                    if (needLength > 0) {
                                        q = root->neighbors[where].GetChar(_str, shift - needLength);
                                    } else {
                                        shift = 0;
                                    }
                                } else {
                                    shift = needLength;
                                    where = q;
                                    break;
                                }
                            }
                        } else {
                            std::size_t needLength = shift;
                            Node *startNode = currentNode;
                            currentNode = currentNode->suffixLink;

                            char q = where;
                            while (needLength > 0) {
                                if (currentNode->neighbors[q].GetLength() <= needLength) {
                                    needLength -= currentNode->neighbors[q].GetLength();
                                    currentNode = currentNode->Go(q);
                                    if (needLength > 0) {
                                        q = startNode->neighbors[where].GetChar(_str, shift - needLength);
                                    } else {
                                        shift = 0;
                                    }
                                } else {
                                    shift = needLength;
                                    where = q;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            ++currentPosition;
        }
    }

    const Node *GetRoot() const noexcept {
        return root;
    }

    const std::size_t GetNumberOfNodes() const noexcept {
        return numberOfNodes;
    }

    const std::string FindCut(const std::size_t length) {
        Node *currentNode = root;
        std::size_t shift = 0;
        std::string result;
        while (result.size() < length) {
            result += currentNode->neighbors.begin()->second.GetChar(_str, shift);
            ++shift;
            if (shift == currentNode->neighbors.begin()->second.GetLength()) {
                shift = 0;
                currentNode = currentNode->neighbors.begin()->second.GetDestination();
            }
        }

        return result;
    }

    ~SuffixTree() {
        destroy(root);
    }

private:

    Node *root;
    const std::string &_str;
    std::size_t numberOfNodes = 0;

    void destroy(Node *node) {
        for (auto &edge: node->neighbors) {
            Node *where = edge.second.GetDestination();
            destroy(where);
        }
        delete node;
    }
};

#endif //LAB5_SUFFIXTREE_H
