#include <iostream>
#include <vector>
#include "Kits.hpp"
#include "HashLL.hpp"
#include "HashBST.hpp"
#include "Hashing.hpp"

int getFileNames(std::vector<std::string> &v, char *strs[], int s, int e)
{
  int cnt = 0;
  for(int i = s; i < e; i ++) {
    std::string name(strs[i]);
    v.push_back(name);
    cnt ++;
  }
  return cnt;
}

int main(int argc, char* args[])
{
  // get file names arguments
  std::vector<std::string> filenames;
  Hashing hash;
  getFileNames(filenames, args, 1, argc);

  // load data from files
  hash.loadData(filenames);

  // load data to the hash table. load factor limit 0.1
  hash.loadDataToTable(filenames[0], 0.1);
  // get 100 insertion performance
  hash.getInsertPerform(filenames[1], 100);
  // get 100 deletion performance
  hash.getDelPerform(filenames[1], 100);

  // load data to the hash table. load factor limit 0.2
  hash.loadDataToTable(filenames[0], 0.2);
  // get 100 insertion performance
  hash.getInsertPerform(filenames[1], 100);
  // get 100 deletion performance
  hash.getDelPerform(filenames[1], 100);

  // load data to the hash table. load factor limit 0.5
  hash.loadDataToTable(filenames[0], 0.5);
  // get 100 insertion performance
  hash.getInsertPerform(filenames[1], 100);
  // get 100 deletion performance
  hash.getDelPerform(filenames[1], 100);

  // load data to the hash table. load factor limit 0.7
  hash.loadDataToTable(filenames[0], 0.7);
  // get 100 insertion performance
  hash.getInsertPerform(filenames[1], 100);
  // get 100 deletion performance
  hash.getDelPerform(filenames[1], 100);

  // load data to the hash table. load factor limit 0.9
  hash.loadDataToTable(filenames[0], 0.9);
  // get 100 insertion performance
  hash.getInsertPerform(filenames[1], 100);
  // get 100 deletion performance
  hash.getDelPerform(filenames[1], 100);

  // load data to the hash table. load factor limit 1
  hash.loadDataToTable(filenames[0], 1);
  // get 100 insertion performance
  hash.getInsertPerform(filenames[1], 100);
  // get 100 deletion performance
  hash.getDelPerform(filenames[1], 100);
  return 0;
}
