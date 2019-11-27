#ifndef HASHBST_CPP
#define HASHBST_CPP
#include "HashBST.hpp"
#include <iostream>

HashBST::HashBST(const int type)
{
  this -> type = type;
  for(BSTNode* n : table) {
    n = new BSTNode(NULL);
  }
  tablesize = 0;
}

int HashBST::hash(int value)
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

BSTNode* HashBST::search(int index, int value)
{
  if(table[index] == NULL){
    return NULL;
  }
  BSTNode *n = table[index] -> next;
  while(n != NULL) {
    if(n -> value == value){
      return n;
    }
    if(value < n -> value){
      n = n -> leftChild;
    } else if (value > n -> value) {
      n = n -> rightChild;
    }
  }
  return NULL;
}

int HashBST::lookup(int value)
{
  if(tablesize == 0) {
    return -1;
  }
  int index = hash(value);
  if(search(index, value) != NULL) {
    return 1;
  }
  return 0;
}

int HashBST::del(int value)
{
  if(tablesize == 0) {
    return -1;
  }
  int index = hash(value);
  BSTNode *n = search(index, value);
  if(n == NULL) {
    return 0;
  }
  BSTNode *p = n -> parent;
  BSTNode **ln = NULL;
  if(p -> next !=  NULL) {
    ln = & (p -> next);
  } else if (n -> isleftsub) {
    ln = & (p -> leftChild);
  } else if (! n -> isleftsub) {
    ln = & (p -> rightChild);
  }
  BSTNode *lst = n -> leftChild;
  BSTNode *rst = n -> rightChild;
  if(lst == NULL && rst == NULL) {
    *ln = NULL;
  } else if (lst == NULL) {
    *ln = rst;
  } else if (rst = NULL) {
    *ln = lst;
  } else {
    BSTNode *t = lst;
    while(t -> rightChild != NULL) {
      t = t -> rightChild;
    }
    t -> rightChild = rst;
    rst -> parent = t;
    rst -> isleftsub = false;
    *ln = lst;
  }
  (*ln) -> parent = p;
  (*ln) -> isleftsub = n -> isleftsub;
  delete n;
  return 1;
}

int HashBST::insert(int value)
{
  int index = hash(value);
  if(search(index, value) != NULL) {
    return -1;
  }
  BSTNode *root = table[index];
  if(root -> next == NULL) {
    BSTNode *newNode = new BSTNode(root, true, value);
    root -> next = newNode;
  } else {
    BSTNode *n = root -> next;
    while(n -> leftChild != NULL || n -> rightChild != NULL) {
      int v = n -> value;
      if(n -> leftChild != NULL && value < v) {
        n = n -> leftChild;
      } else if (n -> rightChild != NULL && value > v) {
        n = n -> rightChild;
      }
    }
    if(value < n -> value) {
      BSTNode *newNode = new BSTNode(n, true, value);
      n -> leftChild = newNode;
    } else if (value > n -> value) {
      BSTNode *newNode = new BSTNode(n, false, value);
      n -> rightChild = newNode;
    }
  }
  tablesize = tablesize + 1;
  return tablesize;
}

double HashBST::getFator()
{
  return 1.0 * TABLE_SIZE / tablesize;
}
#endif
