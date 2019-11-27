#include "HashBST.hpp"
#include <iostream>

HashBST::HashBST(int type)
{
  this -> type = type;
  for(BSTNode* n : table) {
    n = new BSTNode();
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

int main()
{
  return 0;
}
