#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#define SIZE 100
struct Park{
    std::string parkname;
    std::string state;
    int area;
};
void addPark(Park parks[], std::string parkname, std::string state, int area, int length)
{
    parks[length].parkname = parkname;
    parks[length].state = state;
    parks[length].area = area;
}
void printList(const Park parks[], int length)
{
    std::ofstream out("outputfile.csv");
    for(int i = 0; i < length; i ++)
    {
        std::cout << parks[i].parkname << " [" << parks[i].state << "] area: " << parks[i].area << std::endl;
    }
    out.close();
}
void printToFile(std::string filename, const Park parks[], int length, int min)
{
    std::ofstream out(filename);
    for(int i = 0; i < length; i ++)
    {
        //std::cout << park.parkname << " [" << park.state << "] area: " << park.area << std::endl;
        if(parks[i].area >= min){
            out << parks[i].parkname << "," << parks[i].state << "," << parks[i].area << std::endl;
        }
    }
    out.close();
}
int main(int argc, char* argv[])
{
    std::string filename(argv[1]);
    std::ifstream file(filename);
    if(!file.is_open())
    {
        return -1;
    }
    Park parks[SIZE];
    int numparks = 0;
    std::string str, tmp;
    std::vector<std::string> v;
    while(std::getline(file, str)){
        std::istringstream sstream(str);
        while(std::getline(sstream, tmp, ',')){
            v.push_back(tmp);
            //std::cout << tmp << " ";
        }
        addPark(parks, v[0], v[1], std::stoi(v[2]), numparks);
        v.clear();
        numparks ++;
        //std::cout << std::endl;
    }
    printList(parks, numparks);
    printToFile(argv[2], parks, numparks, std::stoi(argv[3]));
    file.close();
    return 0;
}
