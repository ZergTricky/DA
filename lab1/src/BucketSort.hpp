#ifndef BUCKET_SORT_HPP
#define BUCKET_SORT_HPP

#include "vector"
#include "string"
#include "math.h"


class BucketSort {
public:
    static std::vector<std::pair<double, std::string>> sort(const std::vector<std::pair<double, std::string>> &vector,
                                                            const double lower_bound, const double upper_bound) {
        if (vector.empty()) {
            return vector;
        }
        const size_t VectorSize = vector.size();
        const double BucketSize = (upper_bound - lower_bound) / (double) VectorSize;
        std::vector<std::vector<std::pair<double, std::string>>> Buckets(VectorSize);
        for (int i = 0; i < VectorSize; ++i) {
            if (vector[i].first == upper_bound) {
                Buckets[VectorSize - 1].push_back(vector[i]);
            } else {
                size_t position = floor((vector[i].first - lower_bound) / BucketSize);
                Buckets[position].push_back(vector[i]);
            }
        }
        for (std::vector<std::pair<double, std::string>> &Bucket : Buckets) {
            InsertionSort < std::pair<double, std::string>,
                    PairComparator < std::pair<double, std::string>>>(Bucket);
        }
        int currentPointer = 0;
        std::vector<std::pair<double, std::string>> sortedVector(VectorSize);
        for (const std::vector<std::pair<double, std::string>> &Bucket : Buckets) {
            for (const std::pair<double, std::string> &item : Bucket) {
                sortedVector[currentPointer++] = item;
            }
        }
        return sortedVector;
    }

private:
    template<typename T>
    class PairComparator {
    public:
        bool operator()(const T &lhs, const T &rhs) const {
            return lhs.first < rhs.first;
        }
    };

    template<typename T, typename Comparator = std::less<T>>
    static void InsertionSort(std::vector<T> &vector, Comparator cmp = {}) {
        if (vector.empty())return;
        for (int i = 1; i < vector.size(); ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (cmp(vector[j + 1], vector[j])) {
                    std::swap(vector[j + 1], vector[j]);
                } else break;
            }
        }
    }
};

#endif //BUCKET_SORT_HPP