#include "holder.h"

#include <fstream>
#include <iostream>
#include <ostream>

#include "Timer.h"

using namespace std;

ostream &operator<<(ostream &out, Holder &L) {
  L.print(out);
  return out;
}

// Array Stack beginning

ArrayStack::ArrayStack(int cap)
    : Stack("Array Stack"), capacity(cap), size(0), buf(new string[cap]) {}
void ArrayStack::push(const string &word) {
  if (is_full()) {
    cout << "stack overflow!" << endl;
  }
  buf[size++] = word;
}
void ArrayStack::pop() {
  if (is_empty()) {
    cout << "stack underflow!" << endl;
  }
  --size;
}
string ArrayStack::top() { return buf[size - 1]; }
bool ArrayStack::is_empty() { return size == 0; }
bool ArrayStack::is_full() { return size == capacity; }
void ArrayStack::print(ostream &out) {
  for (int i = size - 1; i >= 0; --i) {
    out << buf[i] << " ";
  }
}
ArrayStack::~ArrayStack() { delete[] buf; }
// Array stack completed

// Linked Stack beginning
LinkedStack::LinkedStack() : Stack("Linked Stack"), head(nullptr) {}
void LinkedStack::push(const string &word) {
  ListNode *newNode = new ListNode(word, head);
  head = newNode;
}
void LinkedStack::pop() {
  ListNode *to_be_deleted = head;
  head = head->next;
  delete to_be_deleted;
}
string LinkedStack::top() { return head->data; }
bool LinkedStack::is_empty() { return head == nullptr; }
bool LinkedStack::is_full() { return false; }
void LinkedStack::print(ostream &out) {
  ListNode *current = head;
  while (current) {
    out << current->data << " ";
    current = current->next;
  }
}
LinkedStack::~LinkedStack() {
  while (head) {
    ListNode *temp = head->next;
    delete head;
    head = temp;
  }
}
// Linked Stack Completed

// Array Queue Beginning
ArrayQueue::ArrayQueue(int cap)
    : Queue("Array Queue"),
      capacity(cap + 1),
      front(0),
      rear(0),
      buf(new string[capacity]) {}

void ArrayQueue::enq(const string &word) {
  buf[rear] = word;
  rear = (rear + 1) % capacity;
}

void ArrayQueue::deq() { front = (front + 1) % capacity; }

string ArrayQueue::next() { return buf[front]; }

bool ArrayQueue::is_empty() { return front == rear; }

bool ArrayQueue::is_full() { return (rear + 1) % capacity == front; }

void ArrayQueue::print(ostream &out) {
  for (int i = front; i != rear; i = (i + 1) % capacity) {
    out << buf[i] << " ";
  }
}

ArrayQueue::~ArrayQueue() { delete[] buf; }

// Array Queue Completed

// Linked Queue Beginning
LinkedQueue::LinkedQueue()
    : Queue("Linked List Queue"), head(nullptr), tail(nullptr) {}

void LinkedQueue::enq(const string &word) {
  ListNode *newnode = new ListNode(word, nullptr);
  if (is_empty()) {
    head = newnode;
    tail = newnode;
  } else {
    tail->next = newnode;
    tail = newnode;
  }
}

void LinkedQueue::deq() {
  ListNode *temp = head;
  head = head->next;
  if (head == nullptr) {
    tail = nullptr;
  }
  delete temp;
}

string LinkedQueue::next() { return head->data; }

bool LinkedQueue::is_empty() { return head == nullptr; }

bool LinkedQueue::is_full() { return false; }

void LinkedQueue::print(ostream &out) {
  ListNode *current = head;
  while (current) {
    out << current->data << " ";
    current = current->next;
  }
}

LinkedQueue::~LinkedQueue() {
  while (head) {
    ListNode *temp = head->next;
    delete head;
    head = temp;
  }
}

// Linked Queue Completed

// Measurement methods

void error(string word, string msg) {
  cout << "Error: " << msg << ": " << word << endl;
}

void insert_all_words(int k, string file_name, Holder &L) {
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

void remove_all_words(int k, string file_name, Holder &L) {
  Timer t;
  double eTime;
  ifstream in(file_name);
  int limit = k * NWORDS / 10;
  t.start();
  for (string word; (in >> word) && limit > 0; --limit) {
    L.remove();
  }
  t.elapsedUserTime(eTime);
  in.close();
  cout << "\t\tI = " << eTime << endl;
}

void measure_holder(string file_name, Holder &L) {
  cout << L.name << endl;
  for (int K = 1; K <= 10; ++K) {
    cout << "\tK = " << K << endl;
    insert_all_words(K, file_name, L);
    remove_all_words(K, file_name, L);
    if (!L.is_empty()) {
      error(L.name, " is not empty");
    }
  }
}

void measure_holders(string input_file) {
  ArrayStack Arraystack(NWORDS);
  LinkedStack LS;
  ArrayQueue Arrayqueue(NWORDS);
  LinkedQueue LQ;
  measure_holder(input_file, Arraystack);
  measure_holder(input_file, LS);
  measure_holder(input_file, Arrayqueue);
  measure_holder(input_file, LQ);
}