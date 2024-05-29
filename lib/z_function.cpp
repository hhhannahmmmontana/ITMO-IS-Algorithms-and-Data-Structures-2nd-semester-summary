#include "base_includes.h"

std::vector<unsigned long> Create(const std::string& str) {
    std::vector<unsigned long> z(str.size());
    z[0] = str.size();
    unsigned long left = 0, right = 0;
    for (int i = 1; i < str.size(); ++i) {
        z[i] = std::max(right - i, z[i - left]);
        while (i + z[i] < str.size() && str[z[i]] == str[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] > right) {
            left = i;
            right = i + z[i];
        }
    }
    return z;
}

std::vector<unsigned long> FindPatterns(const std::string& str, const std::string& pattern) {
    // no # in both strings
    std::vector<unsigned long> z = Create(pattern + '#' + str);
    std::vector<unsigned long> ans;
    for (unsigned long i = pattern.size() + 1; i < z.size(); ++i) {
        if (z[i] == pattern.size()) {
            ans.push_back(i - pattern.size() - 1);
        }
    }
    return ans;
}

std::string MakeString(const std::vector<unsigned long>& z, const std::string& alphabet) {
    std::string str;
    unsigned long alphabet_pos = 0;
    unsigned long prefix_length = 0;
    unsigned long j = 0;
    str += alphabet[alphabet_pos++];
    for (unsigned long i = 1; i < z.size(); ++i) {
        if (z[i] == 0 && prefix_length == 0) {
            if (alphabet_pos < alphabet.size()) {
                str += alphabet[alphabet_pos];
            } else {
                str += alphabet[alphabet_pos - 1];
            }
        } else if (z[i] > prefix_length) {
            prefix_length = z[i];
            j = 0;
        } else {
            str += str[j];
            ++j;
            --prefix_length;
        }
    }
    return str;
}