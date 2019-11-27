#ifndef HASHLL_CPP
#define HASHLL_CPP
#include "HashLL.hpp"
#include <iostream>
#include <cmath>

HashLL::HashLL(const int type)
{
  this -> type = type;
  for(int i = 0; i < TABLE_SIZE; i ++) {
    table[i] = new LLNode();
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
  std::cout << "911" << std::endl;
  if(table[index] == NULL) {
    return NULL;
  }
  std::cout << "941" << std::endl;
  LLNode* n = table[index] -> next;
  std::cout << "951" << std::endl;
  while(n != NULL) {
    std::cout << "961" << std::endl;
    if(n -> value == value) {
      return n;
    }
    n = n -> next;
  }
  std::cout << "999" << std::endl;
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
  std::cout << value << std::endl;
  int index = hash(value);
  if(search(index, value) != NULL) {
    return -1;
  }
  std::cout << "123" << std::endl;
  LLNode *n = table[index];
  while(n -> next != NULL) {
    n = n -> next;
  }
  std::cout << "212" << std::endl;
  LLNode *newLLNode = new LLNode(n, value);
  n -> next = newLLNode;
  tablesize = tablesize + 1;
  std::cout << "244" << std::endl;
  return tablesize;
}

double HashLL::getFator()
{
  return 1.0 * TABLE_SIZE / tablesize;
}
#endif
