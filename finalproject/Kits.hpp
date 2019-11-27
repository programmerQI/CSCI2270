#ifndef KITS_H
#define KITS_H
#include <iostream>
#include <vector>
struct Data
{
  std::string name;
  int* nums;
  int size;
  int id;
  Data(std::string name) : name(name), nums(NULL), size(0), id(0) {}
};
class Kits
{
private:
  std::vector<Data*> datasets;
  bool isNum(std::string str);
public:
  Kits();
  ~Kits();
  int readDataFromFile(std::string filename);
  Data* getDataSet(int index);
  Data* getDataSet(std::string name);
  int getNumset();
};
#endif
