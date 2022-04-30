#ifndef LAB2_AVL_H
#define LAB2_AVL_H

#include "string"
#include "fstream"
#include "stack"

template<typename TKey, typename TValue>
class TAVLTree {
private:
    class TAVLNode {
    public:
        int balance = 0;

        TKey key;
        TValue value;

        TAVLNode *left = nullptr;
        TAVLNode *right = nullptr;

        TAVLNode(const TKey &key, const TValue &val) : key(key), value(val) {}

        TAVLNode(const TKey &key, const TValue &value, const int &balance) : key(key), value(value), balance(balance) {}

        TAVLNode(TKey &&key, TValue &&val) : key(std::move(key)), value(std::move(val)) {}

    };


    TAVLNode *Search(TAVLNode *node, const TKey &key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->key == key) {
            return node;
        }
        if (key < node->key) {
            return Search(node->left, key);
        } else return Search(node->right, key);
    }

    TAVLNode *FindMin(TAVLNode *node) {
        if (node->left == nullptr) {
            return node;
        }
        return FindMin(node->left);
    }

    TAVLNode *FindMax(TAVLNode *node) {
        if (node->right == nullptr) {
            return node;
        }
        return FindMax(node->right);
    }

    void SmallRotateLeft(TAVLNode *node) {
        TAVLNode *right = node->right;

        node->right = right->left;
        right->left = node;

        std::swap(*node, *right);

        node->left = right;
    }

    void SmallRotateRight(TAVLNode *node) {
        TAVLNode *left = node->left;

        node->left = left->right;
        left->right = node;

        std::swap(*node, *left);

        node->right = left;
    }

    void BigRotateLeft(TAVLNode *node) {
        TAVLNode *right = node->right;
        SmallRotateRight(right);
        SmallRotateLeft(node);
    }

    void BigRotateRight(TAVLNode *node) {
        TAVLNode *left = node->left;
        SmallRotateLeft(left);
        SmallRotateRight(node);
    }

    bool Balance(TAVLNode *node, bool isErase) {
        if (node->balance == 0) {
            return isErase;
        } else if (node->balance == 1 || node->balance == -1) {
            return !isErase;
        } else if (node->balance == 2) {
            if (node->left->balance == 1) {
                node->left->balance = 0;
                node->balance = 0;

                SmallRotateRight(node);

            } else if (node->left->balance == 0) {
                node->balance = 1;
                node->left->balance = -1;

                SmallRotateRight(node);

            } else if (node->left->right->balance == -1) {
                node->balance = 0;
                node->left->balance = 1;
                node->left->right->balance = 0;

                BigRotateRight(node);

            } else if (node->left->right->balance == 1) {
                node->balance = -1;
                node->left->balance = 0;
                node->left->right->balance = 0;

                BigRotateRight(node);

            } else if (node->left->right->balance == 0) {
                node->balance = 0;
                node->left->balance = 0;
                node->left->right->balance = 0;

                BigRotateRight(node);

            }
        } else if (node->balance == -2) {
            if (node->right->balance == -1) {
                node->right->balance = 0;
                node->balance = 0;

                SmallRotateLeft(node);

            } else if (node->right->balance == 0) {
                node->balance = -1;
                node->right->balance = 1;

                SmallRotateLeft(node);

            } else if (node->right->left->balance == 1) {
                node->balance = 0;
                node->right->balance = -1;
                node->right->left->balance = 0;

                BigRotateLeft(node);

            } else if (node->right->left->balance == -1) {
                node->balance = 1;
                node->right->balance = 0;
                node->right->left->balance = 0;

                BigRotateLeft(node);

            } else if (node->right->left->balance == 0) {
                node->balance = 0;
                node->right->balance = 0;
                node->right->left->balance = 0;

                BigRotateLeft(node);
            }
        }
        return (isErase ? node->balance == 0 : node->balance != 0);
    }

    bool Insert(TAVLNode *node, TAVLNode *parent, const TKey &key, const TValue &value) {
        if (node == nullptr) {
            node = new TAVLNode(key, value);
            if (parent != nullptr) {
                if (key < parent->key) {
                    parent->left = node;
                } else parent->right = node;
            } else {
                treeRoot = node;
            }
            return true;
        }
        if (key < node->key) {
            bool mustBalance = Insert(node->left, node, key, value);
            if (mustBalance) {
                ++node->balance;

                return Balance(node, false);
            }
            return false;
        } else {
            bool mustBalance = Insert(node->right, node, key, value);
            if (mustBalance) {
                --node->balance;

                return Balance(node, false);
            }
            return false;
        }
    }

    bool Erase(TAVLNode *node, TAVLNode *parent, const TKey &key) {
        if (node->key == key) {
            if (parent != nullptr) {
                if (key < parent->key) {
                    parent->left = (node->left != nullptr ? node->left : node->right);
                } else {
                    parent->right = (node->left != nullptr ? node->left : node->right);
                }
            } else {
                treeRoot = (node->left != nullptr ? node->left : node->right);
            }
            delete node;
            return true;
        }
        if (key < node->key) {
            bool mustBalance = Erase(node->left, node, key);
            if (mustBalance) {
                --node->balance;

                return Balance(node, true);
            }
            return false;
        } else {
            bool mustBalance = Erase(node->right, node, key);
            if (mustBalance) {
                ++node->balance;

                return Balance(node, true);
            }
            return false;
        }
    }

    void Erase(TAVLNode *node, const TKey &key) {
        if (node->right == nullptr && node->left == nullptr) {
            Erase(treeRoot, nullptr, key);
        } else if (node->left != nullptr && node->right != nullptr) {
            TAVLNode *min = FindMin(node->right);

            TKey newKey = min->key;
            TValue newValue = min->value;

            Erase(treeRoot, nullptr, newKey);

            node = Search(treeRoot, key);

            node->key = newKey;
            node->value = newValue;
        } else if (node->left != nullptr) {
            Erase(treeRoot, nullptr, key);
        } else {
            Erase(treeRoot, nullptr, key);
        }
    }

public:

    TAVLNode *treeRoot = nullptr;

    TAVLTree() : treeRoot(nullptr) {}

    void Destroy(TAVLNode *node) {
        if (node == nullptr)return;
        treeRoot = nullptr;
        Destroy(node->left);
        node->left = nullptr;
        Destroy(node->right);
        node->right = nullptr;
        delete node;
    }

    TAVLNode *Find(const TKey &key) {
        return Search(treeRoot, key);
    }

    bool Insert(const TKey &key, const TValue &value) {
        TAVLNode *node = Search(treeRoot, key);

        if (node != nullptr) {
            return false;
        }

        Insert(treeRoot, nullptr, key, value);

        return true;
    }

    bool Erase(const TKey &key) {
        TAVLNode *node = Search(treeRoot, key);

        if (node == nullptr) {
            return false;
        }

        Erase(node, key);

        return true;
    }

    static void LoadTree(TAVLTree &tree, std::ifstream &readFile) {
        tree.Destroy(tree.treeRoot);
        TKey key;
        TValue value;
        int balance;

        std::stack<std::pair<TAVLNode *, int>> Stack;

        while (readFile >> key >> value >> balance) {
            if (key == "0") {
                if (!Stack.empty())Stack.top().second--;
            } else {
                if (Stack.empty()) {
                    tree.treeRoot = new TAVLNode(key, value, balance);
                    Stack.push({tree.treeRoot, 2});
                } else {
                    TAVLNode *node = Stack.top().first;

                    TAVLNode *newNode = new TAVLNode(key, value, balance);

                    if (Stack.top().second == 2) {
                        node->left = newNode;
                    } else node->right = newNode;

                    Stack.push({newNode, 2});
                }
            }
            while (!Stack.empty() && Stack.top().second == 0) {
                Stack.pop();
                if (!Stack.empty()) {
                    Stack.top().second--;
                }
            }
        }
    }

    static void SaveTree(TAVLNode *node, std::ofstream &writeFile) {
        if (node == nullptr) {
            writeFile << "0 0 0\n";
            return;
        }

        writeFile << node->key << " " << node->value << " " << node->balance << "\n";

        SaveTree(node->left, writeFile);
        SaveTree(node->right, writeFile);
    }

    ~TAVLTree() {
        Destroy(treeRoot);
    }
};

#endif //LAB2_AVL_H