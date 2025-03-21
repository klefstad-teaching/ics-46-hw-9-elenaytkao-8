#include "ladder.h"
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;

#define my_assert(e) (cout << #e << ((e) ? " passed" : " failed") << endl)

void error(string w1, string w2, string m) {
    cerr << m << " (" << w1 << " -> " << w2 << ")" << endl;
}

bool edit_distance_within(const string &s1, const string &s2, int d) {
    int n1 = s1.size();
    int n2 = s2.size();
    if (abs(n1 - n2) > d) return false;
    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
    for (int i = 0; i <= n1; i++) dp[i][0] = i;
    for (int j = 0; j <= n2; j++) dp[0][j] = j;
    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost});
        }
    }
    return dp[n1][n2] <= d;
}

bool is_adjacent(const string &w1, const string &w2) {
    return edit_distance_within(w1, w2, 1);
}

void load_words(set<string> &wlist, const string &file_name) {
    ifstream fin(file_name);
    string w;
    while (fin >> w) {
        for (auto &c : w) c = tolower(c);
        wlist.insert(w);
    }
}

static vector<string> generate_neighbors(const string &word, const set<string> &dict) {
    vector<string> neighbors;
    int n = word.size();
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < n; i++) {
        string temp = word.substr(0, i) + word.substr(i + 1);
        if (dict.find(temp) != dict.end()) {
            neighbors.push_back(temp);
        }
        for (char c : alphabet) {
            if (c == word[i]) continue;
            string rep = word;
            rep[i] = c;
            if (dict.find(rep) != dict.end()) {
                neighbors.push_back(rep);
            }
        }
    }
    for (int i = 0; i <= n; i++) {
        for (char c : alphabet) {
            string ins = word.substr(0, i) + c + word.substr(i);
            if (dict.find(ins) != dict.end()) {
                neighbors.push_back(ins);
            }
        }
    }
    sort(neighbors.begin(), neighbors.end());
    return neighbors;
}

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list) {
    if (word_list.find(end_word) == word_list.end()) {
        return {};
    }
    queue<vector<string>> q;
    q.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!q.empty()) {
        vector<string> current = q.front();
        q.pop();
        string last = current.back();
        vector<string> nbrs = generate_neighbors(last, word_list);
        for (auto &w : nbrs) {
            if (visited.find(w) == visited.end()) {
                visited.insert(w);
                vector<string> next_path = current;
                next_path.push_back(w);
                if (w == end_word) {
                    return next_path;
                }
                q.push(next_path);
            }
        }
    }
    return {};
}

void print_word_ladder(const vector<string> &ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found.\n";
        return;
    }
    cout << "Word ladder found: ";
    for (int i = 0; i < (int)ladder.size(); i++) {
        cout << ladder[i];
        if (i < (int)ladder.size() - 1) cout << " ";
    }
    cout << " \n";
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
