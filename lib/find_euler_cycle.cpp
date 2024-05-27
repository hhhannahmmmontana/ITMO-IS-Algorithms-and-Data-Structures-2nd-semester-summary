#include "base_includes.h"

bool HasEulerGraph(const std::vector<std::vector<unsigned long>>& graph) {
    // check if any degree is odd
    for (const auto& i : graph) {
        if (i.size() % 2 != 0) {
            return false;
        }
    }
    std::vector<bool> visited(graph.size(), false);
    bool found_one = false; // one or none connectivity components has any edges
    for (unsigned long i = 0; i < visited.size(); ++i) {
        if (!visited[i] && !graph[i].empty()) {
            if (found_one) {
                return false;
            } else {
                // DFS(i, graph, visited);
                found_one = true;
            }
        }
    }
    return true;
}

// trivial realization. works O(|E| * |V|) (|V| because of deletion and finding an edge)
// make sure to copy, we don't want to destroy our previous graph
std::vector<unsigned long> FindEulerCycle(std::vector<std::vector<unsigned long>> graph) {
    if (!HasEulerGraph(graph)) {
        // empty path
        return {};
    }
    std::stack<unsigned long> s;
    s.push(0);
    std::vector<bool> visited(graph.size(), false);
    std::vector<unsigned long> ans;
    ans.reserve(graph.size());
    while (!s.empty()) {
        unsigned long id = s.top();
        while (!graph[id].empty()) {
            unsigned long i = graph[id][0];
            s.push(i);
            graph[id].erase(graph[id].begin());
            graph[i].erase(std::find(graph[i].begin(), graph[i].end(), id));
        }
        s.pop();
        ans.push_back(id);
    }
    return ans;
}

// recursive O(|E|) realization
// pair - edge index and vertex index
// first[i] - first not used edge of vertex i
// visited[e] - is edge e used
void FindEulerCycle_Recursive(unsigned long id, const std::vector<std::vector<std::pair<unsigned long, unsigned long>>>& graph, std::vector<unsigned long>& first, std::vector<bool>& visited, std::vector<unsigned long>& ans) {
    while (first[id] < graph[id].size()) {
        auto info = graph[id][first[id]];
        ++first[id];
        if (!visited[info.first]) {
            visited[info.first] = true;
            FindEulerCycle_Recursive(info.second, graph, first, visited, ans);
            ans.push_back(info.second);
        }
    }
}