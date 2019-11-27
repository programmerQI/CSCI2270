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
  std::vector<std::string> filenames;
  Hashing hash;
  getFileNames(filenames, args, 1, argc);
  hash.loadData(filenames);
  hash.loadDataToTable(filenames[0], 0.1);
  return 0;
}
