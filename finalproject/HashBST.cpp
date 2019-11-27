#ifndef HASHBST_CPP
#define HASHBST_CPP
#include "HashBST.hpp"
#include <iostream>

HashBST::HashBST(const int type)
{
  this -> type = type;
  for(int i = 0; i < TABLE_SIZE; i ++) {
    table[i] = new BSTNode(NULL);
  }
  tablesize = 0;
}

int HashBST::hash(int value)
{
  switch(type) {
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
  //std::cout << "2914" << std::endl;
  BSTNode *p = n -> parent;
  BSTNode **ln = NULL;
  if(p -> next !=  NULL) {
    ln = & (p -> next);
  } else if (n -> isleftsub) {
    ln = & (p -> leftChild);
  } else if (! n -> isleftsub) {
    ln = & (p -> rightChild);
  }
  //std::cout << "2933" << std::endl;
  BSTNode *lst = n -> leftChild;
  BSTNode *rst = n -> rightChild;
  //std::cout << "2965" << std::endl;
  if(lst == NULL && rst == NULL) {
    *ln = NULL;
  } else if (lst == NULL) {
    *ln = rst;
  } else if (rst == NULL) {
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
  //std::cout << "2988" << std::endl;
  if(*ln != NULL) {
    //std::cout << "2991" << std::endl;
    (*ln) -> parent = p;
    //std::cout << "2994" << std::endl;
    (*ln) -> isleftsub = n -> isleftsub;
  }
  delete n;
  //std::cout << "2999" << std::endl;
  return 1;
}

int HashBST::insert(int value)
{
  int index = hash(value);
  //std::cout << "value:" << value << std::endl;
  //std::cout << "index:" << index << std::endl;
  if(search(index, value) != NULL) {
    return -1;
  }
  //std::cout << "511" << std::endl;
  BSTNode *root = table[index];
  //std::cout << "512" << std::endl;
  if(root -> next == NULL) {
    //std::cout << "551" << std::endl;
    BSTNode *newNode = new BSTNode(root, true, value);
    root -> next = newNode;
    //std::cout << "515" << std::endl;
  } else {
    //std::cout << "571" << std::endl;
    BSTNode *n = root -> next;
    while(n -> leftChild != NULL || n -> rightChild != NULL) {
      //std::cout << "a-";
      int v = n -> value;
      if(n -> leftChild != NULL && value < v) {
        n = n -> leftChild;
      } else if (n -> rightChild != NULL && value > v) {
        n = n -> rightChild;
      } else {
        break;
      }
    }
    if(value < n -> value) {
      BSTNode *newNode = new BSTNode(n, true, value);
      n -> leftChild = newNode;
    } else if (value > n -> value) {
      BSTNode *newNode = new BSTNode(n, false, value);
      n -> rightChild = newNode;
    }
    //std::cout << "575" << std::endl;
  }
  //std::cout << "518" << std::endl;
  tablesize = tablesize + 1;
  return tablesize;
}

double HashBST::getFator()
{
  return 1.0 * tablesize / TABLE_SIZE;
}
#endif
