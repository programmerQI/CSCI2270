#include <string>
#include <vector>
struct Data
{
  std::string name;
  int* nums;
  int size;
  Data(std::string name) : name(name), nums(NULL), size(0) {}
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
  int getNumset();
};
