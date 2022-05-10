#ifndef TRIE_H
#define TRIE_H

#include "Node.h"
#include "queue"

template<typename Alphabet>
class Trie {
public:
    Trie() {
        root = new Node<Alphabet>;
    }

    void Destroy(Node<Alphabet> *current) {
        if (current == nullptr)return;

        for (std::pair<const Alphabet, Node<Alphabet> *> &item : current->go) {
            Destroy(item.second);
        }

        delete current;
    }

    void InsertWord(const std::vector<Alphabet> &word) {
        Node<Alphabet> *current = root;

        for (const auto &item : word) {
            if (current->CanGo(item)) {
                current = current->go[item];
            } else {
                current->go[item] = new Node<Alphabet>;
                current = current->go[item];
            }
        }
        current->isTerminal = true;
    }

    Node<Alphabet> *Find(const std::vector<Alphabet> &word) {
        Node<Alphabet> *current = root;
        for (const auto &item : word) {
            if (current->CanGo(item)) {
                current = current->go[item];
            } else {
                return nullptr;
            }
        }
        return current;
    }

    void SetSuffixLinks() {
        // simply BFS
        std::queue<Node<Alphabet> *> Q;
        Q.push(root);
        while (!Q.empty()) {
            Node<Alphabet> *vertex = Q.front();
            Q.pop();
            for (std::pair<const Alphabet, Node<Alphabet> *> &item : vertex->go) {
                const Alphabet &where = item.first;
                Node<Alphabet> *what = item.second;

                Node<Alphabet> *current = vertex->suffixLink;

                //suffixLink

                while (current != nullptr && !current->CanGo(where)) {
                    current = current->suffixLink;
                }

                what->suffixLink = (current != nullptr ? current->go[where] : root);

                //terminalLink

                what->terminalLink = (what->suffixLink->isTerminal ? what->suffixLink
                                                                   : what->suffixLink->terminalLink);

                Q.push(what);
            }
        }
    }

    void PushToTerminal(Node<Alphabet> *current, const int position) {
        if (current == nullptr) {
            return;
        }
        if (current->isTerminal) {
            current->positions.push_back(position);
        }

        PushToTerminal(current->terminalLink, position);
    }

    Node<Alphabet> *GetRoot() {
        return root;
    }

    ~Trie() {
        Destroy(root);
    }

private:
    Node<Alphabet> *root;
};

#endif //TRIE_H