#ifndef HASHING_H
#define HASHING_H
#include <iostream>
#include <vector>
#include "Kits.hpp"
#include "HashLL.hpp"
#include "HashBST.hpp"

class Hashing
{
private:
  Kits kit;
  HashLL hsll_1;
  HashBST hsbst_1;
public:
  Hashing() : kit(), hsll_1(1), hsbst_1(1) {}
  int loadData(std::vector<std::string> filenames);
  int loadDataToTable(std::string filename, double loadfactor);
  void getInsertPerform(std::string filename, int n);
  void getUpdatePerform(std::string filename, int n);
  void getDelPerform(std::string filename, int n);
};
#endif
