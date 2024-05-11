#include "Timer.h"
#include "sorted_list.h"
using namespace std;
#include <fstream>
#include <iostream>
#include <ostream>

SortedArrayList::SortedArrayList(int cap)
    : SortedList("Sorted Array List"),
      capacity(cap),
      size(0),
      buf(new string[cap]) {}
int SortedArrayList::find_index(const string& word) {
  int low = 0;
  int high = size - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (buf[mid] == word) {
      return mid;
    }
    if (buf[mid] < word) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}
void SortedArrayList::copy_down(int hole) {
  for (int i = size; i > hole; --i) {
    buf[i] = buf[i - 1];
  }
  size++;
}
void SortedArrayList::copy_up(int hole) {
  for (int i = hole; i < size - 1; ++i) {
    buf[i] = buf[i + 1];
  }
  size--;
}
void SortedArrayList::insert(const string& word) {
  int i = size;
  while (i > 0 && word < buf[i - 1]) {
    --i;
  }
  copy_down(i);
  buf[i] = word;
}
bool SortedArrayList::find(const string& word) {
  return find_index(word) != -1;
}
void SortedArrayList::remove(const string& word) {
  int index = find_index(word);
  if (index == -1) {
    return;
  }
  copy_up(index);
}
bool SortedArrayList::is_empty() { return size == 0; }
bool SortedArrayList::is_full() { return size == capacity; }
void SortedArrayList::print(ostream& out) {
  for (int i = 0; i < size; ++i) {
    out << buf[i] << " ";
  }
}
SortedArrayList::~SortedArrayList() { delete[] buf; }
SortedLinkedList::SortedLinkedList()
    : SortedList("Sorted Linked List"), head(nullptr) {}
void SortedLinkedList::insert(const string& word) {
  ListNode* newNode = new ListNode(word, nullptr);
  if (!head || word < head->data) {
    newNode->next = head;
    head = newNode;
  } else {
    ListNode* temp = head;
    while (temp->next && temp->next->data < word) {
      temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
  }
}
bool SortedLinkedList::find(const string& word) {
  ListNode* temp = head;
  while (temp) {
    if (temp->data == word) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}
void SortedLinkedList::remove(const string& word) {
  if (!head) {
    return;
  }
  if (head->data == word) {
    ListNode* temp = head->next;
    delete head;
    head = temp;
    return;
  }
  ListNode* current_node = head;
  while (current_node->next && current_node->next->data != word) {
    current_node = current_node->next;
  }
  if (current_node->next) {
    ListNode* temp = current_node->next->next;
    delete current_node->next;
    current_node->next = temp;
  }
}
bool SortedLinkedList::is_empty() { return head == nullptr; }
bool SortedLinkedList::is_full() { return false; }
void SortedLinkedList::print(ostream& out) {
  ListNode* currentNode = head;
  while (currentNode) {
    out << currentNode->data << " ";
    currentNode = currentNode->next;
  }
}
SortedLinkedList::~SortedLinkedList() {
  while (head) {
    ListNode* temp = head->next;
    delete head;
    head = temp;
  }
}
ostream& operator<<(ostream& out, SortedList& L) {
  L.print(out);
  return out;
}
void error(string word, string msg) {
  cout << "Error: " << msg << ": " << word << endl;
}
void insert_all_words(int k, string file_name, SortedList& L) {
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
void find_all_words(int k, string file_name, SortedList& L) {
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
void remove_all_words(int k, string file_name, SortedList& L) {
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
void measure_SortedList_methods(string file_name, SortedList& L) {
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
  SortedArrayList A(NWORDS);
  SortedLinkedList L;
  measure_SortedList_methods(input_file, A);
  measure_SortedList_methods(input_file, L);
}
SortedLinkedList::iterator::iterator(ListNode* const ptr) : current(ptr) {}
SortedLinkedList::iterator& SortedLinkedList::iterator::operator++() {
  if (current) {
    current = current->next;
  }
  return *this;
}
SortedLinkedList::iterator SortedLinkedList::iterator::operator++(int) {
  iterator temp = *this;
  ++(*this);
  return temp;
}

SortedLinkedList::iterator::reference SortedLinkedList::iterator::operator*()
    const {
  return current->data;
}

SortedLinkedList::iterator::pointer SortedLinkedList::iterator::operator->()
    const {
  return &**this;
}

bool SortedLinkedList::iterator::operator==(iterator const& other) const {
  return current == other.current;
}

bool SortedLinkedList::iterator::operator!=(iterator const& other) const {
  return !(*this == other);
}
SortedLinkedList::iterator SortedLinkedList::begin() { return iterator(head); }

SortedLinkedList::iterator SortedLinkedList::end() { return iterator(nullptr); }