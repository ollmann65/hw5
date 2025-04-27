#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


void helper(string &current,
            int idx,
            string floating,
            const set<string>& dict,
            set<string>& results)
{
    int n = current.size();
    if (idx == n) {
        if (floating.empty() && dict.count(current)) {
            results.insert(current);
        }
        return;
    }

    if (current[idx] != '-') {
        
        string pref = current.substr(0, idx + 1);
        auto it = dict.lower_bound(pref);
        if (it != dict.end() && it->compare(0, pref.size(), pref) == 0) {
            helper(current, idx + 1, floating, dict, results);
        }
    } else {
        for (char c = 'a'; c <= 'z'; ++c) {
            current[idx] = c;
            
            string newFloating = floating;
            int pos = -1;
            for (int i = 0; i < (int)newFloating.size(); ++i) {
                if (newFloating[i] == c) { pos = i; break; }
            }
            if (pos != -1) {
                newFloating.erase(pos, 1);
            }
            
            string pref = current.substr(0, idx + 1);
            auto it = dict.lower_bound(pref);
            if (it != dict.end() && it->compare(0, pref.size(), pref) == 0) {
                helper(current, idx + 1, newFloating, dict, results);
            }
            current[idx] = '-';
        }
    }
}
// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    set<string> results;
    string current = in;
    helper(current, 0, floating, dict, results);
    return results;
}

// Define any helper functions here

//the final product