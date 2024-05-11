#include "bst.h"
using namespace std;
#include <fstream>
#include <istream>

#include "timer.h"

void BST::pre_order_print(ostream& out, Node* t) {
  if (t == nullptr) {
    return;
  }
  out << t->key << " ";
  pre_order_print(out, t->left);
  pre_order_print(out, t->right);
}
void BST::in_order_print(ostream& out, Node* t) {
  if (t == nullptr) {
    return;
  }
  in_order_print(out, t->left);
  out << t->key << " ";
  in_order_print(out, t->right);
}
void BST::post_order_print(ostream& out, Node* t) {
  if (t == nullptr) {
    return;
  }
  post_order_print(out, t->left);
  post_order_print(out, t->right);
  out << t->key << " ";
}
void delete_tree(Node* t) {
  if (t) {
    delete_tree(t->left);
    delete_tree(t->right);
    delete t;
  }
}
BST::~BST() { delete_tree(root); }
ostream& operator<<(ostream& out, BST& L) {
  L.print(out);
  return out;
}
void insert_all_words(int k, string file_name, BST& L) {
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
  cout << "\t\tInsert = " << eTime << endl;
}

void find_all_words(int k, string file_name, BST& L) {
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
  cout << "\t\tRemove = " << eTime << endl;
}

void remove_all_words(int k, string file_name, BST& L) {
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
  cout << "\t\tRemove = " << eTime << endl;
}
void error(string word, string msg) {
  cout << "Error: " << msg << ": " << word << endl;
}