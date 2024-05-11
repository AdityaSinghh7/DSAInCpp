#include "ladder.h"
using namespace std;

void error(string word1, string word2, string msg) {
  cout << "ERROR: " << word1 << " " << word2 << " " << msg << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
  int len1 = str1.size();
  int len2 = str2.size();
  if (str1 == str2 && d >= 0) {
    return true;
  }
  if (abs(len1 - len2) > d) {
    return false;
  }
  int edit_count = 0;
  int i = 0, j = 0;
  while (i < len1 && j < len2) {
    if (str1[i] != str2[j]) {
      if (edit_count == d) {
        return false;
      }
      if (len1 > len2) {
        i++;
      } else if (len1 < len2) {
        j++;
      } else {
        i++;
        j++;
      }
      edit_count++;
    } else {
      i++;
      j++;
    }
  }
  if (i < len1 || j < len2) {
    edit_count++;
  }
  return edit_count == d;
}

bool is_adjacent(const string& word1, const string& word2) {
  return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word,
                                    const string& end_word,
                                    const set<string>& word_list) {
  queue<vector<string> > ladder_queue;
  ladder_queue.push({begin_word});
  set<string> visited;
  visited.insert(begin_word);
  while (!ladder_queue.empty()) {
    vector<string> ladder = ladder_queue.front();
    ladder_queue.pop();
    string last_word = ladder.back();
    for (const string& word : word_list) {
      if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
        visited.insert(word);
        vector<string> new_ladder = ladder;
        new_ladder.push_back(word);
        if (word == end_word) {
          return new_ladder;
        }
        ladder_queue.push(new_ladder);
      }
    }
  }
  return {};
}

void load_words(set<string>& word_list, const string& file_name) {
  ifstream word_file(file_name);
  string word;
  while (word_file >> word) {
    word_list.insert(word);
  }
}

void print_word_ladder(const vector<string>& ladder) {
  if (!ladder.empty()) {
    cout << "Word ladder found: ";
    for (const auto& word : ladder) {
      cout << word << " ";
    }
    cout << endl;
  } else {
    cout << "No word ladder found.\n";
  }
}

void verify_word_ladder() {
  set<string> word_list;
  load_words(word_list, "words.txt");
  string begin_word, end_word;
  cout << "Enter the start word: ";
  cin >> begin_word;
  cout << "Enter the end word: ";
  cin >> end_word;
  if (begin_word == end_word) {
    error(begin_word, end_word, "The start and end words are the same.");
    return;
  }
  vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
  print_word_ladder(ladder);
}
