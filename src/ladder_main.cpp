#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "ladder.h"
using namespace std;

int main() {
    cout << "Enter the start word: ";
    string start_word;
    cin >> start_word;
    cout << "Enter the end word: ";
    string end_word;
    cin >> end_word;
    for (auto &c : start_word) c = tolower(c);
    for (auto &c : end_word) c = tolower(c);
    if (start_word == end_word) {
        error(start_word, end_word, "Start and end words are the same.");
        return 0;
    }
    set<string> word_list;
    load_words(word_list, "words.txt");
    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    if (!ladder.empty()) {
        print_word_ladder(ladder);
    } else {
        error(start_word, end_word, "No ladder found.");
    }
    return 0;
}
