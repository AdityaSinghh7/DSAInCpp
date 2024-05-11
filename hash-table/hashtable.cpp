#include "hashtable.h"
#include "stats.h"
#include "hasher.h"

#include <fstream>
#include <iostream>
#include <ostream>
using namespace std;

#include "Timer.h"

ListNode *ListNode::find(string key, ListNode *L) {
  ListNode *temp = L;
  while (temp) {
    if (temp->data == key) {
      return temp;
    }
    temp = temp->next;
  }
  return nullptr;
}

ListNode *ListNode::insert(string key, ListNode *L) {
  ListNode *new_node = new ListNode(key, nullptr);
  new_node->next = L;
  return new_node;
}

ListNode *ListNode::remove(string key, ListNode *L) {
  if (L == nullptr) {
    return nullptr;
  }

  if (L->data == key) {
    ListNode *next_node = L->next;
    delete L;
    return next_node;
  }

  ListNode *current = L;
  while (current->next != nullptr && current->next->data != key) {
    current = current->next;
  }

  if (current->next != nullptr) {
    ListNode *node_to_delete = current->next;
    current->next = current->next->next;
    delete node_to_delete;
  }

  return L;
}
void ListNode::print(ostream &out, ListNode *L) {
  ListNode *current = L;
  while (current != nullptr) {
    out << current->data << " ";
    current = current->next;
  }
}
int ListNode::length(ListNode *L) {
  int len = 0;
  ListNode *current = L;
  while (current != nullptr) {
    len++;
    current = current->next;
  }
  return len;
}
void ListNode::delete_list(ListNode *L) {
  ListNode *current = L;
  while (current != nullptr) {
    ListNode *temp = current->next;
    delete current;
    current = temp;
  }
}

void HashTable::insert(const string &word) {
  size_t index = hasher.hash(word, capacity);
  buf[index] = ListNode::insert(word, buf[index]);
}

bool HashTable::find(const string &word) {
  size_t index = hasher.hash(word, capacity);
  return ListNode::find(word, buf[index]) != nullptr;
}

void HashTable::remove(const string &word) {
  size_t index = hasher.hash(word, capacity);
  buf[index] = ListNode::remove(word, buf[index]);
}

bool HashTable::is_empty() {
  for (size_t i = 0; i < capacity; ++i) {
    if (buf[i] != nullptr) {
      return false;
    }
  }
  return true;
}

bool HashTable::is_full() { return false; }

void HashTable::print(ostream &out) {
  for (size_t i = 0; i < capacity; ++i) {
    ListNode::print(out, buf[i]);
  }
}

HashTable::~HashTable() {
  for (size_t i = 0; i < capacity; ++i) {
    ListNode::delete_list(buf[i]);
  }
  delete[] buf;
}

size_t HashTable::number_of_entries() {
  size_t count = 0;
  for (size_t i = 0; i < capacity; ++i) {
    count += ListNode::length(buf[i]);
  }
  return count;
}

size_t HashTable::number_of_chains() { return capacity; }

void HashTable::get_chain_lengths(vector<int> &v) {
  v.clear();
  v.reserve(capacity);
  for (size_t i = 0; i < capacity; ++i) {
    v.push_back(ListNode::length(buf[i]));
  }
}

void error(string word, string msg) {
  cout << "Error: " << msg << ": " << word << endl;
}

void insert_all_words(string file_name, HashTable &L) {
  Timer t;
  double eTime;
  ifstream in(file_name);
  int limit = NWORDS;
  t.start();
  for (string word; (in >> word) && limit > 0; --limit) {
    L.insert(word);
  }
  t.elapsedUserTime(eTime);
  in.close();
  cout << "\t\tI = " << eTime << endl;
}

void find_all_words(string file_name, HashTable &L) {
  Timer t;
  double eTime;
  ifstream in(file_name);
  int limit = NWORDS;
  t.start();
  for (string word; (in >> word) && limit > 0; --limit) {
    L.find(word);
  }
  t.elapsedUserTime(eTime);
  in.close();
  cout << "\t\tI = " << eTime << endl;
}

void remove_all_words(string file_name, HashTable &L) {
  Timer t;
  double eTime;
  ifstream in(file_name);
  int limit = NWORDS;
  t.start();
  for (string word; (in >> word) && limit > 0; --limit) {
    L.remove(word);
  }
  t.elapsedUserTime(eTime);
  in.close();
  cout << "\t\tI = " << eTime << endl;
}

void measure_hashtable(string file_name, HashTable &L) {
  cout << L.get_name() << endl;
  insert_all_words(file_name, L);
  vector<int> chain_lengths;
  L.get_chain_lengths(chain_lengths);
  Stats stats(L.get_name(), chain_lengths);
  stats.print(cout);
  find_all_words(file_name, L);
  remove_all_words(file_name, L);
  if (!L.is_empty()) {
    error(L.get_name(), " is not empty");
  }
}

void measure_hashtables(string input_file) {
  Hasher *H[] = {new MyHasher{}};
  int S[] = {100};
  for (auto size : S) {
    for (auto h : H) {
      HashTable ht(*h, size);
      measure_hashtable(input_file, ht);
    }
  }
}