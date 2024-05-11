#include "avltree.h"
using namespace std;

int AVLTree::get_height(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

int AVLTree::get_balance(Node* node) {
  if (node == nullptr) {
    return 0;
  } else {
    return get_height(node->left) - get_height(node->right);
  }
}

void AVLTree::set_height(Node* node) {
  if (node) {
    node->height = max(get_height(node->left), get_height(node->right)) + 1;
  }
}

Node* AVLTree::right_rotate(Node* y) {
  Node* x = y->left;
  Node* temp = x->right;
  x->right = y;
  y->left = temp;
  set_height(y);
  set_height(x);
  return x;
}

Node* AVLTree::left_rotate(Node* x) {
  Node* y = x->right;
  Node* temp = y->left;
  y->left = x;
  x->right = temp;
  set_height(x);
  set_height(y);
  return y;
}

Node* AVLTree::rebalance(Node* t) {
  set_height(t);

  int b = get_balance(t);
  if (b > 1) {
    if (get_balance(t->left) < 0) {
      t->left = left_rotate(t->left);
    }
    return right_rotate(t);
  }
  if (b < -1) {
    if (get_balance(t->right) > 0) {
      t->right = right_rotate(t->right);
    }
    return left_rotate(t);
  }

  return t;
}

Node* AVLTree::insert_node(Node* t, string key) {
  if (t == nullptr) {
    return new Node(key);
  }

  if (key < t->key) {
    t->left = insert_node(t->left, key);
  } else if (key > t->key) {
    t->right = insert_node(t->right, key);
  } else {
    return t;
  }
  return rebalance(t);
}

Node* AVLTree::find_node(Node* t, string key) {
  if (t == nullptr || t->key == key) {
    return t;
  }
  if (key < t->key) {
    return find_node(t->left, key);
  } else {
    return find_node(t->right, key);
  }
}

Node* left_most(Node* t) {
  Node* curr = t;
  while (curr && curr->left != nullptr) {
    curr = curr->left;
  }
  return curr;
}

Node* AVLTree::delete_node(Node* t, string key) {
  if (t == nullptr) {
    return t;
  }

  if (key < t->key) {
    t->left = delete_node(t->left, key);
  } else if (key > t->key) {
    t->right = delete_node(t->right, key);
  } else {
    if (t->left == nullptr || t->right == nullptr) {
      Node* temp = t->left ? t->left : t->right;

      if (temp == nullptr) {
        temp = t;
        t = nullptr;
      } else {
        *t = *temp;
      }

      delete temp;
    } else {
      Node* temp = left_most(t->right);

      t->key = temp->key;
      t->right = delete_node(t->right, temp->key);
    }
  }

  if (t == nullptr) {
    return t;
  }

  return rebalance(t);
}

AVLTree::AVLTree() : BST("AVLTree") {}

void AVLTree::insert(const string& key) {
  root = insert_node(root, key);
  count++;
}

bool AVLTree::find(const string& key) const {
  return find_node(root, key) != nullptr;
}

void AVLTree::remove(const string& key) {
  if (find(key)) {
    root = delete_node(root, key);
    count--;
  }
}

bool AVLTree::is_empty() const{
    return root == nullptr;
}

int AVLTree::get_height() const{
    return get_height(root);
}