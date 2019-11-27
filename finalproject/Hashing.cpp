#ifndef HASHING_CPP
#define HASHING_CPP
#include <iostream>
#include "Hashing.hpp"

int Hashing::loadData(std::vector<std::string> filenames)
{
  int cnt = 0;
  for(std::string filename : filenames) {
    if(kit.readDataFromFile(filename) >= 0) {
      std::cout << filename << " has been loaded." << std::endl;
      cnt = cnt + 1;
    } else {
      std::cout << "Cannot load " << filename << std::endl;
    }
  }
  return cnt;
}

int Hashing::loadDataToTable(std::string filename, double loadfactor)
{
  Data *data = kit.getDataSet(filename);
  while(data -> id <= data -> size) {
    int num = data -> nums[data -> id ++];
    hsll_1.insert(num);
    //hsbst_1.insert(num);
    if(hsll_1.getFator() >= loadfactor) {
      return 1;
    }
  }
  return 0;
}
#endif
