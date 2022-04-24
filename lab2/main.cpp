#include <iostream>
#include <fstream>
#include "string"
#include "./src/AVL.h"


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TAVLTree<std::string, unsigned long long> tree;

    std::string c;
    while (std::cin >> c) {
        if (c == "+") {
            std::string key;
            unsigned long long value;
            std::cin >> key;
            std::cin >> value;
            for (auto &item : key) {
                item = tolower(item);
            }
            bool success = tree.Insert(key, value);

            if (success) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "Exist" << std::endl;
            }
        } else if (c == "-") {
            std::string key;
            std::cin >> key;
            for (char &item : key) {
                item = tolower(item);
            }
            bool success = tree.Erase(key);
            if (success) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "NoSuchWord" << std::endl;
            }
        } else if (c == "!") {
            std::string operation, path;
            std::cin >> operation >> path;
            if (operation == "Save") {
                std::ofstream writeFile(path);

                TAVLTree<std::string, unsigned long long>::SaveTree(tree.treeRoot, writeFile);
            } else {
                std::ifstream readFile(path);

                tree.Destroy(tree.treeRoot);

                auto node = TAVLTree<std::string, unsigned long long>::LoadTree(readFile);


                tree.treeRoot = node;
            }

            std::cout << "OK" << std::endl;
        } else {
            for (char &item : c) {
                item = tolower(item);
            }
            auto node = tree.Find(c);

            if (node != nullptr) {
                std::cout << "OK: " << node->value << std::endl;
            } else {
                std::cout << "NoSuchWord" << std::endl;
            }
        }
    }
    return 0;
}
