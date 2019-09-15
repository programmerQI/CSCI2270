#include<iostream>
#include<fstream>
int main(int argc, char* argv[])
{
    std::string filename(argv[1]);
    std::ifstream in(filename);
    if(! in.is_open()){
      return -1;
    }
    std::string line = "";
    std::string fixedline = "";
    while(std::getline(in, line)){
      for(int i = 0; i < line.length(); i ++)
      {
        char c = line[i];
        if('A' <= c && c <= 'Z'){
          char nc = c + 32;
          fixedline = fixedline + nc;
        } else if ('a' <= c && c <= 'z' || c == ' '){
          fixedline = fixedline + c;
        }
      }
      std::cout << fixedline << std::endl;
      fixedline = "";
    }
    in.close();
    return 0;
}
