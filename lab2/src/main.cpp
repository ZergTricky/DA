#include <iostream>
#include "string"
#include "AVL.h"


int main() {
    std::ios::sync_with_stdio(false);

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
                std::cout << "OK\n";
            } else {
                std::cout << "Exist\n";
            }
        } else if (c == "-") {
            std::string key;
            std::cin >> key;
            for (char &item : key) {
                item = tolower(item);
            }
            bool success = tree.Erase(key);
            if (success) {
                std::cout << "OK\n";
            } else {
                std::cout << "NoSuchWord\n";
            }
        } else if (c == "!") {
            std::string operation, path;
            std::cin >> operation >> path;
            if (operation == "Save") {
                std::ofstream writeFile;
                writeFile.open(path);

                TAVLTree<std::string, unsigned long long>::SaveTree(tree.treeRoot, writeFile);

                writeFile.close();
            } else {
                std::ifstream readFile;
                readFile.open(path);

                TAVLTree<std::string, unsigned long long>::LoadTree(tree, readFile);

                readFile.close();
            }

            std::cout << "OK\n";
        } else {
            for (char &item : c) {
                item = tolower(item);
            }
            auto node = tree.Find(c);

            if (node != nullptr) {
                std::cout << "OK: " << node->value << "\n";
            } else {
                std::cout << "NoSuchWord" << "\n";
            }
        }
    }
    return 0;
}
