#ifndef HASHBST_H
#define HASHBST_H
#include <iostream>
struct BSTNode{
  struct BSTNode *parent;
  bool isleftsub;
  int value;
  struct BSTNode *leftChild;
  struct BSTNode *rightChild;
  struct BSTNode *next;
  BSTNode(BSTNode *n) : parent(NULL), isleftsub(true), value(0), leftChild(NULL), rightChild(NULL), next(n) {}
  BSTNode(BSTNode *p, bool l, int v) : parent(p), isleftsub(l), value(v), leftChild(NULL), rightChild(NULL), next(NULL) {}
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
  HashBST(const int type);
  int lookup(int value);
  int del(int value);
  int insert(int value);
  double getFator();
};
#endif
