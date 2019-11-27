#ifndef HASHING_CPP
#define HASHING_CPP
#include <iostream>
#include <ctime>
#include "Hashing.hpp"

int Hashing::loadData(std::vector<std::string> filenames)
{
  int cnt = 0;
  for(std::string filename : filenames) {
    // std::cout << "filename:" << filename << std::endl;
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
  std::cout << std::endl;
  std::cout << "Load data to the load factor : " << loadfactor << std::endl;
  Data *data = kit.getDataSet(filename);
  //std::cout << "dataname:" << filename << std::endl;
  while(data -> id <= data -> size) {
    int num = data -> nums[data -> id ++];
    //std::cout << "num:" << num << std::endl;
    hsll_1.insert(num);
    hsbst_1.insert(num);
    if(hsll_1.getFator() >= loadfactor) {
      return 1;
    }
  }
  return 0;
}

void Hashing::getInsertPerform(std::string filename, int n)
{
  Data *data = kit.getDataSet(filename);
  int cnt, start_time, end_time;
  double exec_time;
  std::cout << "---------------------------------" << std::endl;
  std::cout << "Hash linklist execute " << n << " insetions." << std::endl;
  start_time = clock();

  cnt = 0;
  while(cnt < n) {
    int num = data -> nums[data -> id + cnt];
    hsll_1.insert(num);
    cnt ++;
  }

  end_time = clock();
  exec_time = (double) (end_time - start_time) / CLOCKS_PER_SEC;
  std::cout << "execution time: " << exec_time << std::endl;

  std::cout << "Hash BST execute " << n << " insetions." << std::endl;
  start_time = clock();

  cnt = 0;
  while(cnt < n) {
      int num = data -> nums[data -> id + cnt];
      hsbst_1.insert(num);
      cnt ++;
  }

  end_time = clock();
  exec_time = (double) (end_time - start_time) / CLOCKS_PER_SEC;
  std::cout << "execution time: " << exec_time << std::endl;
  std::cout << "---------------------------------" << std::endl;
  data -> id = data -> id + cnt;
}

void Hashing::getDelPerform(std::string filename, int n) {
  Data *data = kit.getDataSet(filename);
  int cnt, start_time, end_time;
  double exec_time;
  std::cout << "---------------------------------" << std::endl;
  std::cout << "Hash linklist execute " << n << " deletions." << std::endl;
  start_time = clock();

  cnt = 0;
  while(cnt < n) {
    int num = data -> nums[data -> id - cnt];
    hsll_1.del(num);
    cnt ++;
  }

  end_time = clock();
  exec_time = (double) (end_time - start_time) / CLOCKS_PER_SEC;
  std::cout << "execution time: " << exec_time << std::endl;

  std::cout << "Hash BST execute " << n << " deletions." << std::endl;
  start_time = clock();

  cnt = 0;
  while(cnt < n) {
      int num = data -> nums[data -> id - cnt];
      hsbst_1.del(num);
      cnt ++;
  }

  end_time = clock();
  exec_time = (double) (end_time - start_time) / CLOCKS_PER_SEC;
  std::cout << "execution time: " << exec_time << std::endl;
  std::cout << "---------------------------------" << std::endl;
}
#endif
