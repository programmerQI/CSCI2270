#include<iostream>
#include<fstream>
#define SIZE 100
int insertIntoSortedArray(int *myArray, int numEntries, int newValue)
{
    int i = numEntries;
    while(i > 0 && myArray[i - 1] > newValue){
        myArray[i] = myArray[i - 1];
        i --;
    }
    myArray[i] = newValue;
    return numEntries + 1;
}
void output(int *myArray, int len)
{
    for(int i = 0; i < len; i ++)
    {
        std::cout << myArray[i] << (i == len - 1 ? "\n" : ",");
    }
}
int main(int argc, char* argv[])
{
    //std::cout << argc << std::endl;
    //std::cout << argv[1] << std::endl;
    std::string filename(argv[1]);
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "Failed to open the file." << std::endl;
        return 0;
    }
    //std::cout << "file is open" << std::endl;
    int myArray[SIZE];
    int num = 0;
    std::string str;
    while(std::getline(file, str)){
        //std::cout << std::stoi(str) << std::endl;
        num = insertIntoSortedArray(myArray, num, std::stoi(str));
        output(myArray, num);
    }
    file.close();
    return 0;
}
