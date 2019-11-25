#include "HashLL.hpp"
#include <iostream>

HashLL::HashLL()
{
  for(Node* n : table) {
    n = new Node();
  }
  tablesize = 0;
}

int HashLL::hash(int value)
{
  return value % TABLE_SIZE;
}

Node* HashLL::search(int index, int value)
{
  if(table[index] == NULL) {
    return NULL;
  }
  Node* n = table[index] -> next;
  while(n != NULL) {
    if(n -> value == value) {
      return n;
    }
    n = n -> next;
  }
  return NULL;
}

int HashLL::lookup(int value)
{
  if(tablesize == 0){
    return -1;
  }
  int index = hash(value);
  if(search(index, value) != NULL) {
    return 1;
  }
  return 0;
}

int HashLL::del(int value)
{
  if(tablesize == 0){
    return -1;
  }
  int index = hash(value);
  Node *n = search(index, value);
  if(n == NULL) {
    return 0;
  }
  Node *pre = n -> pre;
  Node *nex = n -> next;
  pre -> next = nex;
  if(nex != NULL) {
    nex -> pre = pre;
  }
  delete n;
  return 1;
}

int HashLL::insert(int value)
{
  int index = hash(value);
  if(search(index, value) != NULL) {
    return -1;
  }
  Node *n = table[index];
  while(n -> next != NULL) {
    n = n -> next;
  }
  Node *newNode = new Node(n, value);
  n -> next = newNode;
  tablesize = tablesize + 1;
  return tablesize;
}

int main()
{
    return 0;
}
