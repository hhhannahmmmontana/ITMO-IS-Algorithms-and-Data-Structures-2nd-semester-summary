#include "base_includes.h"

unsigned long dsu_find_parent(unsigned long a, std::vector<unsigned long>& dsu) {
    if (a != dsu[a]) {
        dsu[a] = dsu_find_parent(dsu[a], dsu);
    }
    return dsu[a];
}

void dsu_merge(unsigned long a, unsigned long b, std::vector<unsigned long>& dsu, std::vector<unsigned long>& rang) {
    a = dsu_find_parent(a, dsu);
    b = dsu_find_parent(b, dsu);
    if (a == b) {
        return;
    }
    if (rang[b] > rang[a]) {
        std::swap(a, b);
    }
    dsu[b] = a;
    if (rang[a] == rang[b]) {
        ++rang[a];
    }
}

bool dsu_is_parent_same(unsigned long a, unsigned long b, std::vector<unsigned long>& dsu) {
    return dsu_find_parent(a, dsu) == dsu_find_parent(b, dsu);
}

// using list of edges
std::list<std::pair<unsigned long, unsigned long>> Kraskal(unsigned long V, std::vector<std::pair<unsigned long, unsigned long>> edges) {
    std::vector<unsigned long> dsu(V);
    for (int i = 0; i < V; ++i) {
        dsu[i] = i;
    }
    std::vector<unsigned long> rang(V, 0);
    std::list<std::pair<unsigned long, unsigned long>> ans;
    // actually it should be sorted by weight, but i don't want to write the whole structure for a simple idea
    std::sort(edges.begin(), edges.end());
    for (auto i : edges) {
        if (!dsu_is_parent_same(i.first, i.second, dsu)) {
            dsu_merge(i.first, i.second, dsu, rang);
            ans.push_back(i);
        }
    }
    return ans;
}