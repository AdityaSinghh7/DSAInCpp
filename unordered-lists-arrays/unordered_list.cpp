#include "unordered_list.h"

#include <fstream>
#include <iostream>
#include <ostream>

#include "Timer.h"

using namespace std;

UnorderedArrayList::UnorderedArrayList(int max_len)
    : UnorderedList("Unordered Array List"), capacity(max_len), size(0) {
  buf = new string[capacity];
}
int UnorderedArrayList::find_index(const string& word) {
  for (int i = 0; i < size; i++) {
    if (buf[i] == word) {
      return i;
    }
  }
  return -1;
}
void UnorderedArrayList::insert(const string& word) { buf[size++] = word; }
bool UnorderedArrayList::find(const string& word) {
  return find_index(word) != -1;
}
void UnorderedArrayList::remove(const string& word) {
  int index = find_index(word);
  if (index != -1) {
    buf[index] = buf[--size];
  }
}
bool UnorderedArrayList::is_empty() { return size == 0; }
bool UnorderedArrayList::is_full() { return size == capacity; }
void UnorderedArrayList::print(ostream& out) {
  for (int i = 0; i < size; i++) {
    out << buf[i] << " ";
  }
}
UnorderedArrayList::~UnorderedArrayList() { delete[] buf; }
UnorderedLinkedList::UnorderedLinkedList()
    : UnorderedList("Unordered Linked List"), head(nullptr) {}
void UnorderedLinkedList::insert(const string& word) {
  head = new ListNode(word, head);
}
bool UnorderedLinkedList::find(const string& word) {
  return ListNode::find(word, head) != nullptr;
}
void UnorderedLinkedList::remove(const string& word) {
  ListNode::remove(word, head);
}
bool UnorderedLinkedList::is_empty() { return head == nullptr; }
bool UnorderedLinkedList::is_full() { return false; }
UnorderedLinkedList::~UnorderedLinkedList() { ListNode::delete_list(head); }
void UnorderedLinkedList::print(ostream& out) { ListNode::print(out, head); }
ListNode* ListNode::find(const string& word, ListNode* L) {
  while (L != nullptr) {
    if (L->data == word) return L;
    L = L->next;
  }
  return nullptr;
}
void ListNode::delete_list(ListNode* L) {
  while (L != nullptr) {
    ListNode* temp = L->next;
    delete L;
    L = temp;
  }
}
void ListNode::remove(const string& word, ListNode*& L) {
  ListNode** temp = &L;
  while (*temp) {
    if ((*temp)->data == word) {
      ListNode* nextNode = (*temp)->next;
      delete *temp;
      *temp = nextNode;
    } else {
      temp = &((*temp)->next);
    }
  }
}
void ListNode::print(ostream& out, ListNode* L) {
  for (ListNode* temp = L; temp != nullptr; temp = temp->next) {
    out << temp->data << " ";
  }
}
ostream& operator<<(ostream& out, UnorderedList& L) {
  L.print(out);
  return out;
}
void error(string word, string msg) {
  cout << "Error: " << msg << ": " << word << endl;
}
void insert_all_words(int k, string file_name, UnorderedList& L) {
  Timer t;
  double eTime;
  ifstream in(file_name);
  int limit = k * NWORDS / 10;
  t.start();
  for (string word; (in >> word) && limit > 0; --limit) {
    L.insert(word);
  }
  t.elapsedUserTime(eTime);
  in.close();
  cout << "\t\tI = " << eTime << endl;
}
void find_all_words(int k, string file_name, UnorderedList& L) {
  Timer t;
  double eTime;
  ifstream in(file_name);
  int limit = k * NWORDS / 10;
  t.start();
  for (string word; (in >> word) && limit > 0; --limit) {
    L.find(word);
  }
  t.elapsedUserTime(eTime);
  in.close();
  cout << "\t\tI = " << eTime << endl;
}
void remove_all_words(int k, string file_name, UnorderedList& L) {
  Timer t;
  double eTime;
  ifstream in(file_name);
  int limit = k * NWORDS / 10;
  t.start();
  for (string word; (in >> word) && limit > 0; --limit) {
    L.remove(word);
  }
  t.elapsedUserTime(eTime);
  in.close();
  cout << "\t\tI = " << eTime << endl;
}
void measure_UnorderedList_methods(string file_name, UnorderedList& L) {
  cout << L.name << endl;
  for (int K = 1; K <= 10; ++K) {
    cout << "\tK = " << K << endl;
    insert_all_words(K, file_name, L);
    find_all_words(K, file_name, L);
    remove_all_words(K, file_name, L);
    if (!L.is_empty()) {
      error(L.name, " is not empty");
    }
  }
}
void measure_lists(string input_file) {
  UnorderedArrayList A(NWORDS);
  UnorderedLinkedList L;
  measure_UnorderedList_methods(input_file, A);
  measure_UnorderedList_methods(input_file, L);
}