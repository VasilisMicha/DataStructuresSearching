
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <string>
using namespace std;

struct Node {
  string data;
  int count;
  Node *left;
  Node *right;
  Node(string value);
};

class BinarySearchTree {
private:
  Node *rootPtr;
  Node *insertNode(Node *node, string value);
  Node *searchNode(Node *node, string value);

public:
  BinarySearchTree();
  int getCount(Node *node);
  void insert(string value);
  Node *search(string value);
};

#endif
