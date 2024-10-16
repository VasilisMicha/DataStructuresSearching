
#include "binary-search-tree.h"
#include <iostream>
#include <string>
using namespace std;

Node::Node(string value) {
  data = value;
  count = 1;
  left = nullptr;
  right = nullptr;
}

int BinarySearchTree::getCount(Node *node) { return node->count; }

Node *BinarySearchTree::insertNode(Node *node, string value) {
  if (node == nullptr) {
    return new Node(value);
  }
  if (value < node->data) {
    node->left = insertNode(node->left, value);
  } else if (value > node->data) {
    node->right = insertNode(node->right, value);
  } else { // No dublicates in bst
    node->count++; // Counting iterations from here
  }
  return node;
}

BinarySearchTree::BinarySearchTree() { rootPtr = nullptr; }

void BinarySearchTree::insert(string value) {
  rootPtr = insertNode(rootPtr, value);
}

Node *BinarySearchTree::searchNode(Node *node, string value) {
  if (node == nullptr || value == node->data) {
    return node;
  } else if (value < node->data) {
    return searchNode(node->left, value);
  } else {
    return searchNode(node->right, value);
  }
}

Node *BinarySearchTree::search(string value) {
  return searchNode(rootPtr, value);
}

