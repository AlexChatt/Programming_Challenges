#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

// A hash function used to hash a pair of any kind
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);

        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }

        // If hash1 == hash2, their XOR is zero.
        return hash1;
    }
};

struct hash_pair_list {
    template <class T1>
    size_t operator()(const T1& p) const
    {
        int hash = 0;
        for (auto it = p.begin(); it != p.end(); ++it)
        {
            hash = std::hash<T1>{}(*it) ^ hash;
        }

        return hash;
    }
};

template<typename T>
void printVector(const T& V) {
    std::cout << "( ";
    std::copy(V.cbegin(), V.cend(), std::ostream_iterator<typename T::value_type>(std::cout, " "));
    std::cout << ")";
}
