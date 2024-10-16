
#include "bst-AVL.h"
#include <iostream>

using namespace std;

NodeAvl::NodeAvl(string k) {
  key = k;
  count = height = 1;
  right = left = nullptr;
}

BST_AVL::BST_AVL() : root(nullptr) {}

NodeAvl *BST_AVL::insertNode(NodeAvl *node, string key) {
  if (node == nullptr)
    return new NodeAvl(key);

  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    node->count++; //no duplicates allowed in bst trees

  updateHeight(node);
  return balance(node);
}

void BST_AVL::insert(string key) { root = insertNode(root, key); } //important to update the root bc it can change

NodeAvl *BST_AVL::search(string key) {
  NodeAvl *current = root;
  while (current != nullptr) {
    if (key < current->key)
      current = current->left;
    else if (key > current->key)
      current = current->right;
    else
      return current;
  }
  return nullptr;
}

int BST_AVL::getCount(NodeAvl *node) { return node->count; }

int BST_AVL::getHeight(NodeAvl *node) {
  if (node == nullptr)
    return 0;
  return node->height;
}

int BST_AVL::getBalance(NodeAvl *node) {
  if (node == nullptr)
    return 0;
  return getHeight(node->left) - getHeight(node->right);
}

NodeAvl *BST_AVL::rotateLeft(NodeAvl *node) {
  NodeAvl *newRoot = node->right;
  node->right = newRoot->left;
  newRoot->left = node;
  updateHeight(node);
  updateHeight(newRoot);
  return newRoot;
}

NodeAvl *BST_AVL::rotateRight(NodeAvl *node) {
  NodeAvl *newRoot = node->left;
  node->left = newRoot->right;
  newRoot->right = node;
  updateHeight(node);
  updateHeight(newRoot);
  return newRoot;
}

NodeAvl *BST_AVL::balance(NodeAvl *node) {
  if (node == nullptr)
    return nullptr;

  updateHeight(node);

  int balance = getBalance(node);

  if (balance > 1) {
    if (getBalance(node->left) < 0)
      node->left = rotateLeft(node->left);
    return rotateRight(node);
  }

  if (balance < -1) {
    if (getBalance(node->right) > 0)
      node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

void BST_AVL::updateHeight(NodeAvl *node) {
  if (node == nullptr)
    return;
  node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}




