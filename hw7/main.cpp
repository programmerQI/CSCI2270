#include "MovieTree.cpp"
#include <iostream>
using namespace std;
void printMenu()
{
    cout << "======Main Menu======" << endl;
    cout << "1. Print the inventory" << endl;
    cout << "2. Delete a movie" << endl;
    cout << "3. Quit" << endl;
}

int readFile(std::string filename, MovieTree& t)
{
    std::ifstream in(filename);
    if(!in.is_open()){
      return -1;
    }
    std::string line;
    while(getline(in, line)){
      std::string strs[5];
      split(line, ',', strs, 5);
      t.addMovie(std::stoi(strs[0]), strs[1], std::stoi(strs[2]), std::stof(strs[3]));
    }
    in.close();
    return 0;
}

int main(int argc, char *argv[])
{
    if(argc != 2){
      std::cout << "Not enough argument!" << std::endl;
      return 0;
    }
    MovieTree mt;
    std::string file(args[1]);
    readFile(file, mt);
    std::string in;
    while(true){
      showMenu();
      std::getline(std::cin, in);
      if(in == "1") {
        mt.printMovieInventory();
      } else if (in == "2") {
        std::cout << "Enter a movie title:" << std::endl;
        std::string r;
        std::getline(std::cin, r);
        mt.deleteMovie(r);
      } else if (in == "3") {
        std::cout << "Goodbye!" << std::endl;
        break;
      }
    }
    return 0;
}
