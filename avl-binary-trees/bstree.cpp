#include "bstree.h"
using namespace std;
Node* BSTree::insert_node(Node* t, string key) {
  if (t == nullptr) {
    return new Node(key);
  } else if (key < t->key) {
    t->left = insert_node(t->left, key);
  } else {
    t->right = insert_node(t->right, key);
  }
  t->height = max(compute_height(t->left), compute_height(t->right)) + 1;
  return t;
}
Node* BSTree::find_node(Node* t, string key) {
  if (t == nullptr) {
    return nullptr;
  } else if (t->key == key) {
    return t;
  } else if (key < t->key) {
    return find_node(t->left, key);
  } else {
    return find_node(t->right, key);
  }
}
Node* BSTree::left_most(Node* t) {
  Node* current = t;
  while (current && current->left != nullptr) {
    current = current->left;
  }
  return current;
}
Node* BSTree::delete_node(Node* t, string key) {
  if (t == nullptr) {
    return t;
  }
  if (key < t->key) {
    t->left = delete_node(t->left, key);
  } else if (key > t->key) {
    t->right = delete_node(t->right, key);
  } else {
    if (t->left == nullptr) {
      Node* temp = t->right;
      delete t;
      return temp;
    } else if (t->right == nullptr) {
      Node* temp = t->left;
      delete t;
      return temp;
    }
    Node* temp = left_most(t->right);
    t->key = temp->key;
    t->right = delete_node(t->right, temp->key);
  }
  t->height = 1 + std::max(compute_height(t->left), compute_height(t->right));
  return t;
}
int BSTree::compute_height(Node* t) {
  if (t == nullptr)
    return 0;
  else
    return t->height;
}
BSTree::BSTree() : BST("BSTree") {}

void BSTree::insert(const string& key) {
  root = insert_node(root, key);
  ++count;
}

bool BSTree::find(const string& key) const {
  return find_node(root, key) != nullptr;
}

void BSTree::remove(const string& key) {
  if (find(key)) {
    root = delete_node(root, key);
    count--;
  }
}

bool BSTree::is_empty() const { return root == nullptr; }

int BSTree::get_height() const { return compute_height(root); }
