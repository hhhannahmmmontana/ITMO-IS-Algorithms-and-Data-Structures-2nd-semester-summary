#include "base_includes.h"

std::vector<unsigned long> Create(const std::string& str) {
    std::vector<unsigned long> result(str.size());
    result[0] = 0;
    for (int i = 1; i < str.size(); ++i) {
        unsigned long temp = result[i - 1];
        while (temp > 0 && str[i] != str[k]) {
            temp = result[temp - 1];
        }
        if (str[i] == str[temp]) {
            ++temp;
        }
        result[i] = temp;
    }
    return result;
}

std::vector<unsigned long> ZFunction(const std::vector<unsigned long>& z_func) {
    std::vector<unsigned long> pref(z_func.size(), 0);
    for (unsigned long i = 1; i < pref.size(); ++i) {
        for (unsigned long j = z_func[i]; j > 0; --j) {
            if (pref[i + (j - 1)] > 0) {
                break;
            } else {
                pref[i + (j - 1)] = j;
            }
        }
    }
    return pref;
}

std::string MakeString(const std::vector<unsigned long>& pref, const std::string& alphabet) {
    std::string ans;
    unsigned long alphabet_pos = 0;
    for (unsigned long i : pref) {
        if (i == 0) {
            ans += alphabet[alphabet_pos++];
        } else {
            ans += ans[i - 1];
        }
    }
    return ans;
}