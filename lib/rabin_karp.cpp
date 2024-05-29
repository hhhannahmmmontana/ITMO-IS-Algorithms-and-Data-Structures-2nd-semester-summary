#include "base_includes.h"

unsigned long RabinKarp(const std::string& s, const std::string& m) {
    unsigned long ans = 0;
    unsigned long max_k = 1;
    unsigned long hash_s = 0;
    unsigned long hash_m = 0;
    for (unsigned long i = 0; i < m.size(); ++i) {
        hash_s += s[i] * max_k;
        hash_m += m[i] * max_k;
        max_k *= k;
    }
    if (hash_s == hash_m) {
        ans += (s.substr(0, m.size()) == m);
    }
    for (unsigned long i = m.size(); i < s.size(); ++i) {
        hash_s = k * hash_s - max_k * s[i - m.size()] + s[i];
        if (hash_s == hash_m) {
            ans += (s.substr(i - m.size() + 1, m.size()) == m);
        }
    }
    return ans;
}