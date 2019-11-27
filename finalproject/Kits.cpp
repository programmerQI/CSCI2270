#ifndef KITS_CPP
#define KITS_CPP
#include <iostream>
#include <fstream>
#include <vector>
#include "Kits.hpp"
Kits::Kits()
{

}

Kits::~Kits()
{
  for(auto d : datasets) {
    free(d -> nums);
    delete d;
  }
}

bool Kits::isNum(std::string str)
{
  if(str == "") {
    return false;
  }
  for(char i : str) {
    if(i < '0' || i > '9') {
      return false;
    }
  }
  return true;
}

int Kits::readDataFromFile(std::string filename)
{
  std::ifstream f(filename);
  if(!f.is_open()) {
    std::cout << "Cannot open " << filename << std::endl;
    return -1;
  }
  Data* data = new Data(filename);
  data -> nums = (int*)malloc(sizeof(int) * 50000);
  std::string line = "";
  while(std::getline(f, line)) {
    line = line + ',';
    std::string tmp = "";
    for(char i : line) {
      if(i == ',') {
        if(isNum(tmp)) {
          int num = std::stoi(tmp);
          (data -> nums)[data -> size ++] = num;
        }
        tmp = "";
      } else {
        tmp = tmp + i;
      }
    }
  }
  datasets.push_back(data);
  f.close();
  std::cout << data -> size << " data from " << filename << std::endl;
  return data -> size;
}

Data* Kits::getDataSet(int index)
{
  if(index < 0 || index >= datasets.size()) {
    return NULL;
  }
  return datasets[index];
}

Data* Kits::getDataSet(std::string name)
{
  for(auto d : datasets) {
    if(d -> name == name) {
      return d;
    }
  }
  return NULL;
}

int Kits::getNumset()
{
    return datasets.size();
}
#endif
