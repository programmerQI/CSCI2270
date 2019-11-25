#include <iostream>

// Define the Node struct
struct Node{
  struct Node* next;
  struct Node* pre;
  int value;
  Node() : next(NULL), pre(NULL), value(0) {}
  Node(Node* pre, int value) : next(NULL), pre(pre), value(value) {}
};

// Define Hash class
class HashLL{
private:
  const static int TABLE_SIZE = 10009;
  Node* table[TABLE_SIZE];
  int tablesize;
  int hash(int value);
  Node* search(int index, int value);
public:
  HashLL();
  int lookup(int value);
  int del(int value);
  int insert(int value);
};
