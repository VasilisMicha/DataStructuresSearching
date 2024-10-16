
#ifndef BST_AVL_H
#define BST_AVL_H

#include <string>

using namespace std;

struct NodeAvl {
  string key;
  int count;
  NodeAvl *left;
  NodeAvl *right;
  int height;

  NodeAvl(string k);
};

class BST_AVL {
private:
  NodeAvl *root;

  NodeAvl *insertNode(NodeAvl *node, string key);
  int getHeight(NodeAvl *node);
  int getBalance(NodeAvl *node);
  NodeAvl *rotateLeft(NodeAvl *node);
  NodeAvl *rotateRight(NodeAvl *node);
  NodeAvl *balance(NodeAvl *node);
  void updateHeight(NodeAvl *node);

public:
  BST_AVL();

  void insert(string key);
  NodeAvl *search(string key);
  int getCount(NodeAvl* node);
};

#endif // BST_AVL_H
