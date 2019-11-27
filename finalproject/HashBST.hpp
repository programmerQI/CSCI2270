#include <iostream>
struct BSTNode{
  struct BSTNode *parent;
  int value;
  struct BSTNode *leftChild;
  struct BSTNode *rightChild;
  struct BSTNode *next;
  BSTNode() : parent(NULL), value(0), next(NULL), leftChild(NULL), rightChild(NULL), next(NULL) {}
  BSTNode(BSTNode *p, int v) : parent(p), value(v), leftChild(NULL), rightChild(NULL), next(NULL) {}
};
class HashBST
{
private:
  const static int TABLE_SIZE = 10009;
  int type;
  BSTNode* table[TABLE_SIZE];
  int tablesize;
  int hash(int value);
  BSTNode* search(int index, int value);
public:
  HashBST(int type);
  int lookup(int value);
  int del(int value);
  int insert(int value);
  double getFator();
};
