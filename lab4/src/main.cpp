#include "iostream"
#include "string"
#include "Trie.h"


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<unsigned int>> patternWords;
    std::string s;

    std::getline(std::cin, s);
    std::string current;
    std::vector<std::string> input;
    for (auto &c : s) {
        if ((c >= '0' && c <= '9') || c == '?') {
            current += c;
        } else {
            if (!current.empty()) {
                input.push_back(current);
            }
            current.clear();
        }
    }
    if (!current.empty()) {
        input.push_back(current);
    }
    std::vector<unsigned int> word;

    size_t len = 0;
    std::vector<size_t> pos;

    size_t patternLength = 0;

    for (const std::string &item : input) {
        if (item == "?") {
            ++len;
            ++patternLength;
            if (!word.empty()) {
                patternWords.push_back(word);
            }
            word.clear();
        } else {
            if (!item.empty()) {
                if (word.empty()) {
                    pos.push_back(len);
                }
                word.push_back((unsigned int) std::stoll(item));
                ++len;
                ++patternLength;
            }
        }
    }
    if (!word.empty()) {
        patternWords.push_back(word);
    }
    const size_t need = patternWords.size();

    Trie<unsigned int> AhoKorasik;

    for (const std::vector<unsigned int> &word : patternWords) {
        AhoKorasik.InsertWord(word);
    }

    std::vector<std::pair<size_t, size_t>> answerPosition;
    std::vector<unsigned int> text;

    size_t row = 0;

    while (std::getline(std::cin, s)) {
        size_t col = 0;
        current.clear();
        for (auto &c : s) {
            if (c >= '0' && c <= '9') {
                current += c;
            } else {
                if (!current.empty()) {
                    text.push_back((unsigned int) std::stoll(current));
                    answerPosition.emplace_back(row, col);
                    ++col;
                }
                current.clear();
            }
        }
        if (!current.empty()) {
            text.push_back((unsigned int) std::stoll(current));
            answerPosition.emplace_back(row, col);
        }
        ++row;
    }

    AhoKorasik.SetSuffixLinks();

    Node<unsigned int> *node = AhoKorasik.GetRoot();

    for (size_t i = 0; i < text.size(); ++i) {
        const unsigned int item = text[i];
        while (node != nullptr && !node->CanGo(item)) {
            node = node->suffixLink;
        }
        node = (node == nullptr ? AhoKorasik.GetRoot() : node->go[item]);

        AhoKorasik.PushToTerminal(node, i);
    }

    std::vector<int> counter(text.size(), 0);

    for (size_t i = 0; i < patternWords.size(); ++i) {
        const std::vector<unsigned int> &word = patternWords[i];
        Node<unsigned int> *vertex = AhoKorasik.Find(word);
        for (int &it : vertex->positions) {
            int where = it - word.size() - pos[i] + 1;
            if (where >= 0)counter[where]++;
        }
    }
    for (size_t i = 0; i + patternLength - 1 < text.size(); ++i) {
        if (counter[i] == need) {
            std::cout << answerPosition[i].first + 1 << ", " << answerPosition[i].second + 1 << "\n";
        }
    }
    return 0;
}