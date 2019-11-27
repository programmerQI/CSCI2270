#include "HashLL.hpp"
#include <iostream>
#include <cmath>

HashLL::HashLL(int type)
{
  this -> type = type;
  for(LLNode* n : table) {
    n = new LLNode();
  }
  tablesize = 0;
}

int HashLL::hash(int value)
{
  switch(value) {
    case 1:
      return value % TABLE_SIZE;
    case 2:
      return (value / TABLE_SIZE) % TABLE_SIZE;
    default:
      return -1;
  }
}

LLNode* HashLL::search(int index, int value)
{
  if(table[index] == NULL) {
    return NULL;
  }
  LLNode* n = table[index] -> next;
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
  LLNode *n = search(index, value);
  if(n == NULL) {
    return 0;
  }
  LLNode *pre = n -> pre;
  LLNode *nex = n -> next;
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
  LLNode *n = table[index];
  while(n -> next != NULL) {
    n = n -> next;
  }
  LLNode *newLLNode = new LLNode(n, value);
  n -> next = newLLNode;
  tablesize = tablesize + 1;
  return tablesize;
}

double HashLL::getFator()
{
  return 1.0 * TABLE_SIZE / tablesize;
}

int main()
{
    return 0;
}
