#include <iostream>

// Define the LLNode struct
struct LLNode{
  struct LLNode* next;
  struct LLNode* pre;
  int value;
  LLNode() : next(NULL), pre(NULL), value(0) {}
  LLNode(LLNode* p, int v) : next(NULL), pre(p), value(v) {}
};

// Define Hash class
class HashLL{
private:
  const static int TABLE_SIZE = 10009;
  int type;
  LLNode* table[TABLE_SIZE];
  int tablesize;
  int hash(int value);
  LLNode* search(int index, int value);
public:
  HashLL(int type);
  int lookup(int value);
  int del(int value);
  int insert(int value);
  double getFator();
};
