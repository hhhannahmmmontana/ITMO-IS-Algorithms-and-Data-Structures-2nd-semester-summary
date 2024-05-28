#include "base_includes.h"

bool DFS(unsigned long id, std::vector<unsigned long>& matching, std::vector<bool>& visited, const std::vector<std::vector<unsigned long>>& left_part) {
    if (visited[id]) {
        return false;
    }
    visited[id] = true;
    for (auto i : left_part[id]) {
        if (matching[i] == ULONG_MAX || DFS(matching[i], matching, visited, left_part)) {
            matching[i] = id;
            return true;
        }
    }
    return false;
}

std::vector<unsigned long> Kun(const std::vector<std::vector<unsigned long>>& left_part, unsigned long right_amount) {
    std::vector<unsigned long> pairs(right_amount, ULONG_MAX);
    for (unsigned long i = 0; i < left_part.size(); ++i) {
        std::vector<bool> visited(left_part.size(), false);
        DFS(i, pairs, visited, left_part);
    }
    return pairs;
}